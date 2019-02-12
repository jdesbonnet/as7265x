
/**
 * Create blank body ration curve for a blackbody of a given temperature (K)
 * 
 * See https://en.wikipedia.org/wiki/Planck's_law
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// speed of light
static const double c = 2.99792458e8;

// Plank's constant
static const double h = 6.626070150e-34;

// Boltzmann constant
static const double k = 1.38064852e-23;

/**
 * Get black body radiation (W m^-2 steradian^-2 Hz^-1) for a given temperature (T)
 * and wavelength (m)
 *
 * @param T temperature on kelvin scale
 * @param wavelength wavelength of light / EM radiation
 */
double phy_planks_function (double T, double wavelength) {
	return ( (2 * h * c * c) / pow(wavelength,5)) / (exp((h*c)/(wavelength*k*T)) - 1);
}


