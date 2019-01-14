/**
 * Create blank body ration curve for a blackbody of a given temperature (K)
 * 
 * See https://en.wikipedia.org/wiki/Planck's_law
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "plank.h"

int main (int argc, char **argv) 
{

	double T = (double) atoi(argv[1]);

	int i;
	double wavelength;


	if (argc>2) {

		for (i = 2; i < argc; i++) {
			wavelength = (double)atoi(argv[i]) * 1e-9;
                        printf ("%f %f\n", (wavelength*1e9), phy_planks_function(T,wavelength));
		}
	
	} else {
		for (wavelength = 300e-9; wavelength < 2000e-9; wavelength += 5e-9) {
			printf ("%f %f\n", (wavelength*1e9), phy_planks_function(T,wavelength));
		}
	}

}

