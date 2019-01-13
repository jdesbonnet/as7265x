
/**
 * Convert a wavelength of light into an equivalant red, green, blue value. There
 * is no one-to-one mapping for this. 

 * Based on code here:  http://www.efg2.com/Lab/ScienceAndEngineering/Spectra.htm
 */

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) 
{


	float wavelength = (float) atoi(argv[1]);

	float red, green, blue, adjust;


	if (wavelength >= 380 && wavelength < 440) {
		red =  - (wavelength - 440) / (440 - 380);
		green = 0;
		blue = 1;
	} else if (wavelength >= 440 && wavelength < 490) {
		red = 0;
		green = (wavelength - 440) / (490 - 440);
		blue = 1;
	} else if (wavelength >= 490 && wavelength < 510) {
		red = 0;
		green = 1;
		blue = - (wavelength - 510) / (510 - 490);
	} else if (wavelength >= 510 && wavelength < 580) {
		red = (wavelength - 510) / (580 - 510);
		green = 1;
		blue = 0;
	} else if (wavelength >= 580 && wavelength < 645) {
		red = 1;
		green = - (wavelength - 645) / (645 - 580);
		blue = 0;
	} else if (wavelength >= 645 && wavelength < 780) {
		red = 1;
		green = 0;
		blue = 0;
	} 


	if (wavelength >= 380 && wavelength < 420) {
		adjust = 0.3 + 0.7 * (wavelength - 380) / (420 - 380);
	} else if (wavelength >= 420 && wavelength < 700) {
		adjust = 1.0;
	} else if (wavelength >= 700 && wavelength < 780) {
		adjust = 0.3 + 0.7 * (780 - wavelength) / (780 - 700);
	}


	red *= adjust;
	green *= adjust;
	blue *= adjust;

	printf ("%f %f %f\n", red, green, blue);

}

