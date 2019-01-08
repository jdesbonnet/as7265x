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

}
