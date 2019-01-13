#!/bin/bash

DP832=/dev/usbtmc1

for v in $(seq 0 1.0 12); do
	echo -n ":SOUR1:VOLT:IMM ${v}" > ${DP832}
	sleep 1
	echo -n ":MEAS:CURR? CH1" > ${DP832}
	read i < ${DP832}
	ADC=`ssh pi@10.7.0.42 ./as7265x/src/as7265x_oneshot 0 18`
	echo "$v $i $ADC"
done

echo -n ":SOUR1:VOLT:IMM 0" > ${DP832}


