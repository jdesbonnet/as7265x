/**
 * Read all 18 channels and ouput in ascending wavelength order
 * (channels A, B, C, D, E, F, G, H, R, I, S, J, T, U, V, W, K, L)
 */

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
	int i;
	
	i2c_fd = i2c_init("/dev/i2c-1");

	as7265x_set_bulb_current (i2c_fd, 2, 1);
	as7265x_bulb_enable (i2c_fd, 2);

	as7265x_channels_t channels;
	as7265x_raw_channels_t raw_channels;


	// disable all light sources
	for (i = 0; i < 3; i++) {
		//as7265x_set_bulb_current(i2c_fd, 0, 0);
		as7265x_bulb_disable(i2c_fd,i);
	}


	// set one-shot measurement mode
	//as7265x_set_measurement_mode(i2c_fd, AS7265X_MEASUREMENT_MODE_6CHAN_ONE_SHOT);


	as7265x_set_gain (i2c_fd, AS7265X_GAIN_64X);

	while (1) {
		as7265x_set_measurement_mode(i2c_fd, AS7265X_MEASUREMENT_MODE_6CHAN_ONE_SHOT);

		while ( ! as7265x_is_data_available(i2c_fd) ) {
			usleep(1000);
		}

		//as7265x_get_all_calibrated_values(i2c_fd, &channels);
		//as7265x_order_channels(i2c_fd, &channels);
		as7265x_get_all_raw_values(i2c_fd, &raw_channels);
		as7265x_order_raw_channels(i2c_fd, &raw_channels);
		
		for (i = 0; i < 18; i++) {
			//fprintf (stdout,"%f ", channels.channel[i]);
			fprintf (stdout, "%d ", (int)raw_channels.channel[i]);
		}
		fprintf(stdout, "\n");	
		fflush(stdout);

		sleep(1);
	}

	as7265x_soft_reset(i2c_fd);

}
