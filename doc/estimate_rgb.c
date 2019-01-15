#include <stdio.h>
#include "as7265x.h"
#include "stockman_sharpe.h"
int main (int argc, char **argv) {

	int i;
	double v[18];
	as7265x_wavelengths_t channel_wavelengths = as7265x_get_unordered_channel_wavelengths();

	double sum_v = 0;
	double wavelength;
	double red, green, blue;
	double sum_r=0, sum_g=0, sum_b=0;

	for (i = 0; i < 18; i++) {
		wavelength = channel_wavelengths.channel[i];
		scanf ("%lf", &v[i]);
		sum_v += v[i];
		stockman_sharpe(wavelength, &red, &green, &blue);

		sum_r += v[i] * red;
		sum_g += v[i] * green;
		sum_b += v[i] * blue;

		printf ("%.0f %f %f %f %f\n", wavelength, v[i], red, green, blue);
	}
	printf ("\n");

	printf ("%f %f %f\n", sum_r/sum_v, sum_g/sum_v, sum_b/sum_v);
	printf ("#%02x%02x%02x\n",  (int)(sum_r*255/sum_v), (int)(sum_g*255/sum_v), (int)(sum_b*255/sum_v));
}


