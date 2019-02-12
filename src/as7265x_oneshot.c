/**
 * Read all 18 channels and ouput in ascending wavelength order
 * (channels A, B, C, D, E, F, G, H, R, I, S, J, T, U, V, W, K, L)
 * 
 * Intention is to move this to a fully fledged command line utility
 * to read from the sensor.
 *
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "i2c.h"
#include "as7265x.h"


void usage () {
	fprintf (stderr,"as7265x_reading bulb0_current bulb1_current bulb2_current gain integration_time\n");
	fprintf (stderr,"bulbn_current: 0 - 4\n"); 
	fprintf (stderr,"gain: 0 - 3\n");
	fprintf (stderr,"integration_time: 1 - 255 in 2.8ms units\n");
}

void main (int argc, char **argv) {

	int i2c_fd;
	int i;
	
	int bulb_current[3];

	if (argc < 6) {
		usage();
		exit(-1);
	}

	bulb_current[0] = atoi(argv[1]);
	bulb_current[1] = atoi(argv[2]);
	bulb_current[2] = atoi(argv[3]);

	int gain = atoi(argv[4]);
	int integ_time = atoi(argv[5]);

	i2c_fd = i2c_init("/dev/i2c-1");


	as7265x_channels_t calibrated_channels;
	as7265x_raw_channels_t raw_channels;

	// Disable indicator
	as7265x_indicator_disable(i2c_fd);

	for (i = 0; i < 3; i++) {
		if (bulb_current[i] == 0) {
			as7265x_bulb_disable(i2c_fd, i);
		} else {
			as7265x_bulb_enable(i2c_fd, i);
			as7265x_set_bulb_current(i2c_fd, i, bulb_current[i]+1);
		}
	}

	as7265x_set_gain (i2c_fd, AS7265X_GAIN_16X);
	as7265x_set_integration_time (i2c_fd, integ_time);


	// trigger one-shot conversion
	as7265x_set_measurement_mode(i2c_fd, AS7265X_MEASUREMENT_MODE_6CHAN_ONE_SHOT);

	// wait for data available : TODO: should delay in loop to reduce I2C bus traffic
	while ( ! as7265x_is_data_available(i2c_fd) ) {
		usleep(1000);
	}

	as7265x_get_all_calibrated_values(i2c_fd, &calibrated_channels);
	as7265x_get_all_raw_values(i2c_fd, &raw_channels);
		
	// raw ADC
	for (i = 0; i < 18; i++) {
		fprintf (stdout, "%d ", (int)raw_channels.channel[i]);
	}

	fprintf (stdout,"    ");

	// calibrated
	for (i = 0; i < 18; i++) {
		fprintf (stdout, "%.3f ", calibrated_channels.channel[i]);
	}
	fprintf(stdout, "\n");	
	fflush(stdout);

	close(i2c_fd);
}
