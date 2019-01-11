#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "i2c.h"
#include "as7265x.h"



/**
 * Read a I2C (real) register from AS7265x
 */
int i2cm_read(int i2c_fd, int addr) {
	uint8_t result;
	i2c_register_read(i2c_fd, 0x49, addr, &result);
	return result;
} 

/**
 * Write a I2C (real) register to AS7265x.
 */
int i2cm_write(int i2c_fd, int addr, int value) {
	i2c_register_write(i2c_fd, 0x49, addr, value);
}

/**
 * Write to AS7265x virtual register
 */
void as7265x_vreg_write(int i2c_fd, uint8_t virtualReg, uint8_t d)
{
	volatile uint8_t status;
	while (1)
	{
		// Read slave I²C status to see if the write buffer is ready.
		status = i2cm_read(i2c_fd,I2C_AS72XX_SLAVE_STATUS_REG);
		if ((status & I2C_AS72XX_SLAVE_TX_VALID) == 0) 
			// No inbound TX pending at slave. Okay to write now.
			break ;
	}
	// Send the virtual register address (enabling bit 7 to indicate a write).
	i2cm_write(i2c_fd, I2C_AS72XX_SLAVE_WRITE_REG, (virtualReg | 0x80)) ;
	while (1)
	{
		// Read the slave I²C status to see if the write buffer is ready.
		status = i2cm_read(i2c_fd, I2C_AS72XX_SLAVE_STATUS_REG) ;
		if ((status & I2C_AS72XX_SLAVE_TX_VALID) == 0)
		// No inbound TX pending at slave. Okay to write data now.
		break ;
	}
	// Send the data to complete the operation.
	i2cm_write(i2c_fd,I2C_AS72XX_SLAVE_WRITE_REG, d) ;
}

/**
 * Read from AS7265x virtual register 
 */
uint8_t as7265x_vreg_read(int i2c_fd, uint8_t virtualReg)
{
	volatile uint8_t status, d;

	status = i2cm_read(i2c_fd, I2C_AS72XX_SLAVE_STATUS_REG);
	if ( (status & I2C_AS72XX_SLAVE_RX_VALID) != 0)  {
		// data to be read
		d = i2cm_read(i2c_fd, I2C_AS72XX_SLAVE_READ_REG);
	}

	// Wait for WRITE flag to clear
	while (1)
	{
		// Read slave I²C status to see if the read buffer is ready.
		status = i2cm_read(i2c_fd, I2C_AS72XX_SLAVE_STATUS_REG) ;
		if ((status & I2C_AS72XX_SLAVE_TX_VALID) == 0)
		// No inbound TX pending at slave. Okay to write now.
		break;
	}


	// Send the virtual register address (disabling bit 7 to indicate a read).
	i2cm_write(i2c_fd, I2C_AS72XX_SLAVE_WRITE_REG, virtualReg);


	while (1)
	{
		// Read the slave I²C status to see if our read data is available.
		status = i2cm_read(i2c_fd, I2C_AS72XX_SLAVE_STATUS_REG);
		if ((status & I2C_AS72XX_SLAVE_RX_VALID)!= 0)
		// Read data is ready.
		break;
	}

	// Read the data to complete the operation.
	d = i2cm_read(i2c_fd, I2C_AS72XX_SLAVE_READ_REG) ;
	return d;
}

int as7265x_is_data_available (int i2c_fd)
{
	int status = as7265x_vreg_read(i2c_fd, AS7265X_CONFIG);
	return (status & (1<<1) );
}

/**
 * Select device
 *
 * @param device 0=master; 1=first slave; 2=second slave
 */
void as7265x_device_select(int i2c_fd, uint8_t device) {
	as7265x_vreg_write(i2c_fd, AS7265X_DEV_SELECT_CONTROL, device);
}


/**
 * Set amplifier gain

 * @param gain 0= 1x (default), 1=3.7x, 2=16x, 3=64x
 */
void as7265x_set_gain (int i2c_fd, int gain) 
{

	int value = as7265x_vreg_read(i2c_fd, AS7265X_CONFIG);
	value &= 0b11001111; // clear gain bits
	value |= (gain&0b11) << 4;
	as7265x_vreg_write(i2c_fd, AS7265X_CONFIG,value);
}

/**
 * Set bulb current.
 *
 * @param device 0, 1, or 2
 * @param current 
 */
void as7265x_set_bulb_current(int i2c_fd, uint8_t device, uint8_t current)
{
	as7265x_device_select(i2c_fd,device);

	current &= 0b11;

	uint8_t value = as7265x_vreg_read(i2c_fd,AS7265X_LED_CONFIG);
	value &= 0b11001111; //Clear ICL_DRV bits
	value |= (current << 4); //Set ICL_DRV bits with user's choice
	as7265x_vreg_write(i2c_fd,AS7265X_LED_CONFIG, value);
}

/**
 * Bulb enable / disable
 */
void as7265x_bulb_enable (int i2c_fd, uint8_t device) 
{
	as7265x_device_select(i2c_fd, device);

	uint8_t value = as7265x_vreg_read(i2c_fd, AS7265X_LED_CONFIG);
	// bit 3: bulb en/disable
	value |= (1 << 3);
	as7265x_vreg_write(i2c_fd, AS7265X_LED_CONFIG, value);
}

void as7265x_bulb_disable (int i2c_fd, uint8_t device)
{
        as7265x_device_select(i2c_fd, device);
	uint8_t value = as7265x_vreg_read(i2c_fd, AS7265X_LED_CONFIG);
	// bit 3: bulb en/disable
	value &= ~(1 << 3);
	as7265x_vreg_write(i2c_fd, AS7265X_LED_CONFIG, value);
}

/**
 * Set measurement mode.
 * 
 * @param mode 2 = all 6 channels continuous; 3 = one shot all channels
 */
void as7265x_set_measurement_mode(int i2c_fd, uint8_t mode) 
{
	uint8_t value = as7265x_vreg_read(i2c_fd, AS7265X_CONFIG);
	value &= 0b11110011;
	value |= (mode&0b11) << 2;
	as7265x_vreg_write(i2c_fd, AS7265X_CONFIG, value);
}

/**
 * Read calibrated value (IEEE 754 float)
 */
float as7265x_get_calibrated_value (int i2c_fd, uint8_t device, uint8_t base_addr)
{
	int i;
	uint8_t value;
	uint32_t shift_reg = 0;

	as7265x_device_select(i2c_fd, device);

	for (i = base_addr; i < base_addr+4; i++) {
		shift_reg <<= 8;
		value = as7265x_vreg_read(i2c_fd, i);
		shift_reg |= value;
	}
	// convert content of shift_reg to floating point
	float ret;
	memcpy (&ret, &shift_reg, sizeof(float));
	return ret;
}

/**
 * Read raw value (16 bit unsigned integer)
 */
int as7265x_get_raw_value (int i2c_fd, uint8_t device, uint8_t base_addr)
{
	as7265x_device_select(i2c_fd, device);
        uint32_t value = (as7265x_vreg_read(i2c_fd, base_addr)<<8);
	value |= as7265x_vreg_read(i2c_fd,base_addr+1);
//fprintf(stderr,"raw device %d @ %x = %d\n", device, base_addr, value);
	return value;
}


/**
 * Read all 18 channels
 */
void as7265x_get_all_calibrated_values (int i2c_fd, as7265x_channels_t *channels)
{

	uint8_t base_addr;
	int channel_index = 0;
	int i;
	uint8_t device;
	float v;

	const uint8_t device_order[] = { 2, 0 , 1};

	// Interrogate in this order:
	// AS72643 (UV)
	// AS72642 (vis+IR)
	// AS72841 (vis+IR)
	for (i = 0; i < 3; i++) {
		device = device_order[i];
		for (base_addr = 0x14; base_addr < 0x2c; base_addr += 4) {	
			v = as7265x_get_calibrated_value (i2c_fd, device, base_addr);
			channels->channel[channel_index] = v;
			channel_index++;
		}
	}

}
/**
 * Read all 18 channels raw ADC
 */

void as7265x_get_all_raw_values (int i2c_fd, as7265x_raw_channels_t *channels) 
{
	int i;
	int base_addr;
	int device;
	int channel_index = 0;
	const uint8_t device_order[] = { 2, 0 , 1};
	for (i = 0; i < 3; i++) {
		device = device_order[i];
		for (base_addr = 0x8; base_addr < 0x14; base_addr += 2) {
			channels->channel[channel_index] = (uint16_t)as7265x_get_raw_value(i2c_fd, device, base_addr);	
			channel_index++;
		}
	}

}


/**
 * Order channels in ascending wavelength.
 */
void as7265x_order_channels(int i2c_fd, as7265x_channels_t *channels) 
{
	float buf[18];
	int i;
	for (i = 0; i < 18; i++) {
		buf[as7265x_channel_order_table[i]] = channels->channel[i];
	}
	for (i = 0; i < 18; i++) {
		channels->channel[i] = buf[i];
	}
}

void as7265x_order_raw_channels(int i2c_fd, as7265x_raw_channels_t *channels) 
{

	uint16_t buf[18];
	int i;
	for (i = 0; i < 18; i++) {
		buf[as7265x_channel_order_table[i]] = channels->channel[i];
	}
	for (i = 0; i < 18; i++) {
		channels->channel[i] = buf[i];
	}
}


void as7265x_measure(int i2c_fd)
{
	int i;
	as7265x_set_measurement_mode(i2c_fd, AS7265X_MEASUREMENT_MODE_6CHAN_ONE_SHOT);
	for (i = 0; i < 100; i++) {
		if ( as7265x_is_data_available(i2c_fd) ) 
		{
			break;
		}
	}


	as7265x_get_calibrated_value (i2c_fd, AS7265X_R_G_A_CAL, AS72653_UV);

}

void as7265x_soft_reset (int i2c_fd) 
{
	as7265x_vreg_write(i2c_fd, AS7265X_CONFIG, (1<<7));
}

