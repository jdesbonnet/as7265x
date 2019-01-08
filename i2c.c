/**
 * Low level I2C interface library to read and write 8 bit I2C
 * device registers using standard I2C bus protocol.
 *
 * Based on some example code from here:
 * https://gist.github.com/JamesDunne/9b7fbedb74c22ccc833059623f47beb7
 *
 * Reference: https://en.wikipedia.org/wiki/I%C2%B2C
 */



#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>


// Terrible portability hack between arm-linux-gnueabihf-gcc on Mac OS X and native gcc on raspbian.
#ifndef I2C_M_RD
#include <linux/i2c.h>
#endif

#include "i2c.h"


/**
 * Open and return I2C bus file descriptor. Bus opened in RDRW mode.
 */
int i2c_init(const char *i2c_fname) {
	int i2c_fd;
	if ((i2c_fd = open(i2c_fname, O_RDWR)) < 0) {
		char err[200];
		sprintf(err, "open('%s') in i2c_init", i2c_fname);
		perror(err);
		return -1;
	}
	return i2c_fd;
}


/**
 * Close I2C bus file.
 */
void i2c_close(int i2c_fd) {
	close(i2c_fd);
}

/**
 * Write to I2C device register.
 *
 * @return 0 if successful, else -1.
 */
int i2c_register_write(int i2c_fd, uint8_t slave_addr, uint8_t reg, uint8_t data) {
    int retval;
    uint8_t outbuf[2];

    struct i2c_msg msgs[1];
    struct i2c_rdwr_ioctl_data msgset[1];

    outbuf[0] = reg;
    outbuf[1] = data;

    msgs[0].addr = slave_addr;
    msgs[0].flags = 0;
    msgs[0].len = 2;
    msgs[0].buf = outbuf;

    msgset[0].msgs = msgs;
    msgset[0].nmsgs = 1;

    if (ioctl(i2c_fd, I2C_RDWR, &msgset) < 0) {
        perror("ioctl(I2C_RDWR) in i2c_write");
        return -1;
    }

    return 0;
}


/**
 * Read I2C device register, returing result in 'result'.
 *
 * @return 0 if successful, else -1
 */
int i2c_register_read(int i2c_fd, uint8_t slave_addr, uint8_t reg, uint8_t *result) {
    int retval;
    uint8_t outbuf[1], inbuf[1];
    struct i2c_msg msgs[2];
    struct i2c_rdwr_ioctl_data msgset[1];

    msgs[0].addr = slave_addr;
    msgs[0].flags = 0;
    msgs[0].len = 1;
    msgs[0].buf = outbuf;

    msgs[1].addr = slave_addr;
    msgs[1].flags = I2C_M_RD | I2C_M_NOSTART;
    msgs[1].len = 1;
    msgs[1].buf = inbuf;

    msgset[0].msgs = msgs;
    msgset[0].nmsgs = 2;

    outbuf[0] = reg;

    inbuf[0] = 0;

    *result = 0;
    if (ioctl(i2c_fd, I2C_RDWR, &msgset) < 0) {
        perror("ioctl(I2C_RDWR) in i2c_read");
        return -1;
    }

    *result = inbuf[0];
    return 0;
}


