#!/bin/bash

DP832=/dev/usbtmc1

for v in $(seq 0 0.2 8); do
	echo -n ":SOUR1:VOLT:IMM ${v}" > ${DP832}
	sleep 0.1
	#echo -n ":SOUR1:CURR?" > ${DP832}
	#exec {FD}<${DP832}
	#read -u ${FD} CURRENT
	echo ${CURRENT}
	ADC=`ssh pi@10.7.0.42 ./as7265x/src/as7265x_oneshot 0 18`
	echo -n "$v -1 $ADC"
done

echo -n ":SOUR1:VOLT:IMM 0" > ${DP832}


