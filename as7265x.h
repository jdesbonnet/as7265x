
// Code partually copied from Sparkfun Arduino library


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


int     as7265x_is_data_available(int i2c_fd);
void    as7265x_set_bulb_current(int i2c_fd, uint8_t current, uint8_t device);
void    as7265x_vreg_write(int i2c_fd, uint8_t vreg, uint8_t value);
uint8_t as7265x_vreg_read(int i2c_fd, uint8_t vreg);
void    as7265x_set_measurement_mode(int i2c_fd, uint8_t mode);


