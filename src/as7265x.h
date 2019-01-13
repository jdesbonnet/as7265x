
// Code partually copied from Sparkfun Arduino library

#ifndef _AS7265X_H
#define _AS7265X_H

#define I2C_AS72XX_SLAVE_STATUS_REG 0x00
#define I2C_AS72XX_SLAVE_WRITE_REG 0x01
#define I2C_AS72XX_SLAVE_READ_REG 0x02
#define I2C_AS72XX_SLAVE_TX_VALID 0x02
#define I2C_AS72XX_SLAVE_RX_VALID 0x01


// Virtual Register addresses

#define AS7265X_HW_VERSION_HIGH   0x00
#define AS7265X_HW_VERSION_LOW    0x01

#define AS7265X_FW_VERSION_HIGH  0x02
#define AS7265X_FW_VERSION_LOW  0x03

#define AS7265X_CONFIG      0x04
#define AS7265X_INTERGRATION_TIME 0x05
#define AS7265X_DEVICE_TEMP     0x06
#define AS7265X_LED_CONFIG    0x07

//Raw channel registers
#define AS7265X_R_G_A     0x08
#define AS7265X_S_H_B     0x0A
#define AS7265X_T_I_C     0x0C
#define AS7265X_U_J_D     0x0E
#define AS7265X_V_K_E     0x10
#define AS7265X_W_L_F     0x12

//Calibrated channel registers
#define AS7265X_R_G_A_CAL   0x14
#define AS7265X_S_H_B_CAL   0x18
#define AS7265X_T_I_C_CAL   0x1C
#define AS7265X_U_J_D_CAL   0x20
#define AS7265X_V_K_E_CAL   0x24
#define AS7265X_W_L_F_CAL   0x28

#define AS7265X_DEV_SELECT_CONTROL  0x4F

#define AS7265X_COEF_DATA_0   0x50
#define AS7265X_COEF_DATA_1   0x51
#define AS7265X_COEF_DATA_2   0x52
#define AS7265X_COEF_DATA_3   0x53
#define AS7265X_COEF_DATA_READ    0x54
#define AS7265X_COEF_DATA_WRITE   0x55


//Settings 

#define AS7265X_POLLING_DELAY 5 //Amount of ms to wait between checking for virtual register changes

#define AS72651_NIR     0x00
#define AS72652_VISIBLE     0x01
#define AS72653_UV      0x02

#define AS7265x_LED_WHITE	0x00 //White LED is connected to x51
#define AS7265x_LED_IR	0x01 //IR LED is connected to x52
#define AS7265x_LED_UV	0x02 //UV LED is connected to x53

#define AS7265X_LED_CURRENT_LIMIT_12_5MA  0b00
#define AS7265X_LED_CURRENT_LIMIT_25MA    0b01
#define AS7265X_LED_CURRENT_LIMIT_50MA    0b10
#define AS7265X_LED_CURRENT_LIMIT_100MA   0b11

#define AS7265X_INDICATOR_CURRENT_LIMIT_1MA   0b00
#define AS7265X_INDICATOR_CURRENT_LIMIT_2MA   0b01
#define AS7265X_INDICATOR_CURRENT_LIMIT_4MA   0b10
#define AS7265X_INDICATOR_CURRENT_LIMIT_8MA   0b11

#define AS7265X_GAIN_1X   0b00
#define AS7265X_GAIN_37X   0b01
#define AS7265X_GAIN_16X   0b10
#define AS7265X_GAIN_64X   0b11

#define AS7265X_MEASUREMENT_MODE_4CHAN   0b00
#define AS7265X_MEASUREMENT_MODE_4CHAN_2   0b01
#define AS7265X_MEASUREMENT_MODE_6CHAN_CONTINUOUS   0b10
#define AS7265X_MEASUREMENT_MODE_6CHAN_ONE_SHOT   0b11


typedef struct as7265x_named_channels {
	// AS72651
	float A;
	float B;
	float C;
	float D;
	float E;
	float F;

	// AS72652
	float G;
	float H;
	float I;
	float J;
	float K;
	float L;

	// AS72651
	float R;
	float S;
	float T;
	float U;
	float V;
	float W;
} as7265x_named_channels_t;

typedef struct as7265x_channels {
	float channel[18];
} as7265x_channels_t;

typedef struct as7265x_raw_channels {
	uint16_t channel[18];
} as7265x_raw_channels_t;

struct {
	union {
		struct as7265x_named_channels named_channels;
		struct as7265x_channels channels;
	} data;
} as7265x_channel_union_t;


/**
 * How to reorder channels so that channels are ordered by ascending wavelength.
 */
static const uint8_t as7265x_channel_order_table[] =  {
	12,13,14,15,16,17,    6,7,0,8,1,9,2,3,4,5,10,11
};

/**
 * Peak sensitivity frequency of the unordered channels (unit nm).
 */
static const int ordered_channel_wavelenth[] = {
	410, 435, 460, 485, 510, 535, 560, 585, 610, 645, 680, 705, 730, 760, 810, 860, 900, 940
};

int     as7265x_is_data_available(int i2c_fd);
void    as7265x_set_gain(int i2c_fd, int gain);
void    as7265x_set_bulb_current(int i2c_fd, uint8_t device, uint8_t current);
void    as7265x_bulb_enable(int i2c_fd, uint8_t device);
void    as7265x_bulb_disable(int i2c_fd, uint8_t device);
void    as7265x_vreg_write(int i2c_fd, uint8_t vreg, uint8_t value);
uint8_t as7265x_vreg_read(int i2c_fd, uint8_t vreg);
void    as7265x_set_measurement_mode(int i2c_fd, uint8_t mode);
void    as7265x_device_select(int i2c_fd, uint8_t device);
void    as7265x_soft_reset(int i2c_fd);
float   as7265x_get_calibrated_value (int i2c_fd, uint8_t device, uint8_t base_addr);
void    as7265x_get_all_calibrated_values (int i2c_fd, as7265x_channels_t *channels);
void    as7265x_get_all_raw_values (int i2c_fd, as7265x_raw_channels_t *channels);
void    as7265x_order_channels(int i2c_fd, as7265x_channels_t *channels);
void    as7265x_order_raw_channels(int i2c_fd, as7265x_raw_channels_t *channels);

#endif

