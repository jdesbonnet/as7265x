/**
 * For a given frequency calculate the power at that frequency for a range
 * of temperatures.
 * 
 * See https://en.wikipedia.org/wiki/Planck's_law
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "plank.h"

int main (int argc, char **argv) 
{

	double wavelength = (double) atoi(argv[1]) * 1e-9;
	double Tbegin = (double) atoi(argv[2]);
	double Tend = (double) atoi(argv[3]);
	double Tinc = (double) atoi(argv[4]);

	double T;

	for (T = Tbegin; T < Tend; T += Tinc) {
		printf ("%f %f\n", T, phy_planks_function(T,wavelength));
	}
	
}

