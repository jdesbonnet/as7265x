#!/bin/bash

DP832=/dev/usbtmc1

# Use built in light sources
ssh pi@10.7.0.42 ./as7265x/src/t 0 0 0 3 200 > dark.dat
ssh pi@10.7.0.42 ./as7265x/src/t 4 0 0 3 200 > white_led.dat
ssh pi@10.7.0.42 ./as7265x/src/t 0 4 0 3 200 > nir_led.dat
ssh pi@10.7.0.42 ./as7265x/src/t 0 0 4 3 200 > uv_led.dat

for v in $(seq 0 0.5 12); do
	echo -n ":SOUR1:VOLT:IMM ${v}" > ${DP832}
	sleep 1
	echo -n ":MEAS:CURR? CH1" > ${DP832}
	read i < ${DP832}
	ADC=`ssh pi@10.7.0.42 ./as7265x/src/as7265x_oneshot 0 0 0 3 200`
	echo "$v $i $ADC"
done

echo -n ":SOUR1:VOLT:IMM 0" > ${DP832}


