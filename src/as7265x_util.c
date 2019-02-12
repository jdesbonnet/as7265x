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

#define FORMAT_COLUMN 1
#define FORMAT_ROW 2

void usage () {
	fprintf (stderr,"as7265x_util -d <device> [options]\n");
	fprintf (stderr," -a bulb0 current 0 - 4\n");
	fprintf (stderr," -b bulb1 current 0 - 4\n");
	fprintf (stderr," -c bulb2 current 0 - 4\n");
	fprintf (stderr," -f format: c=column, r=row\n");
	fprintf (stderr," -g gain 0 - 3\n");
	fprintf (stderr," -i integration_time: 1 - 255 in 2.8ms units\n");
	fprintf (stderr," -p sampling period ms\n");
}

void main (int argc, char **argv) {

	int i2c_fd;
	int i;
	
	int bulb_current[3];
	int gain;
	int integ_time;
	int output_format;
	int sort_flag = 0;

	// Sampling period (ms)
	int period = -1;

	char *device = "/dev/i2c-1";


	// Parse command line arguments. See usage() for details.
	int c;
	while ((c = getopt(argc, argv, "a:b:c:d:f:g:hi:o:p:qstv")) != -1) {
		switch(c) {

			case 'a':
				bulb_current[0] = atoi (optarg);
				break;
			case 'b':
				bulb_current[1] = atoi (optarg);
				break;
			case 'c':
				bulb_current[2] = atoi (optarg);
				break;


			case 'd':
				device = optarg;
				break;

			case 'f':
				if (optarg[0] == 'c') {
					output_format = FORMAT_COLUMN;
				} else if (optarg[0] == 'r') {
					output_format = FORMAT_ROW;
				}
				break;
			
			case 'g':
				gain = atoi(optarg);
				break;

			case 'i':
				integ_time = atoi(optarg);
				break;

			case 'h':
				//version();
				usage(argv[0]);
				exit(EXIT_SUCCESS);

			case 'p':
				period = atoi(optarg);
				break;

			case 's':
				sort_flag = 1;
				break;



		} // end switch
	} // end while


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


	while (1) {

		// trigger one-shot conversion
		as7265x_set_measurement_mode(i2c_fd, AS7265X_MEASUREMENT_MODE_6CHAN_ONE_SHOT);

		// wait for data available : TODO: should delay in loop to reduce I2C bus traffic
		while ( ! as7265x_is_data_available(i2c_fd) ) {
			usleep(1000);
		}

		as7265x_get_all_calibrated_values(i2c_fd, &calibrated_channels);
		as7265x_get_all_raw_values(i2c_fd, &raw_channels);

		// If sort_flag set, reorder channels in ascending wavelengths
		if (sort_flag) {
			as7265x_order_raw_channels(i2c_fd, &raw_channels);
			as7265x_order_calibrated_channels(i2c_fd, &calibrated_channels);
		}

		
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

		if (period == -1) {
			break;
		} else {
			usleep(period*1000);
		}
	}

	close(i2c_fd);
}
