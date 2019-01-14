#!/bin/bash
for T in $(seq 1000 50 2500); do
	./planks_curve  ${T}  610 680 730 760 810 860 > plank_theory_${T}K.dat
done

WAVELENGTHS="610 680 730 760 810 860    560 585 645 705 900 940   410 435 460 485 510 535"
for wavelength in ${WAVELENGTHS}; do
	./plank_variable_T $wavelength 1000 3500 50 > plank_theory_${wavelength}nm.dat
done


