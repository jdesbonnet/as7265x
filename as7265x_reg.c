#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "i2c.h"
#include "as7265x.h"


static void usage () {
	fprintf (stderr,"as7265x register [value]\n");
	fprintf (stderr,"read or write a AS7265X virtual register.\n");
}

void main (int argc, char **argv) {

	int i2c_fd;
	
	if (argc < 2) {
		usage();
		exit(0);
	}

	i2c_fd = i2c_init("/dev/i2c-1");

	int reg = atoi(argv[1]);

	if (argc >= 3) {
		int val = atoi(argv[2]);
		fprintf (stderr,"writing register %x with %x\n",reg,val);
		as7265x_vreg_write(i2c_fd,reg,val);
	} else {
		fprintf (stderr,"reading as7265x virtual register 0x%x, value=0x%x\n", reg, as7265x_vreg_read(i2c_fd,reg));
	}

}
