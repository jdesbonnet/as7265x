#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "i2c.h"
#include "as7265x.h"


void usage () {
	fprintf (stderr,"as7265x_reading \n");
	fprintf (stderr,"read all 18 channels of AS7265x triad sensor.\n");
}

void main (int argc, char **argv) {

	int i2c_fd;
	
	if (argc < 2) {
		usage();
		//exit(0);
	}

	i2c_fd = i2c_init("/dev/i2c-1");

	as7265x_set_bulb_current (i2c_fd, 2, 1);
	as7265x_bulb_enable (i2c_fd, 2);

	float f = as7265x_get_calibrated_value(i2c_fd, AS72653_UV, AS7265X_R_G_A_CAL);

	fprintf (stdout, "f=%f\n", f);

	sleep(2);
	as7265x_soft_reset(i2c_fd);

}
