#!/bin/bash
while true; do
	TS=`date +%s`
	TS_ISO=`date --iso-8601=minutes`
	ssh pi@10.7.0.42 ./as7265x/src/t 4 4 3 3 200  > banana_${TS}.dat
	spectrum=`ssh pi@10.7.0.42 ./as7265x/src/as7265x_oneshot 4 4 4 3 200`
	echo "$TS $TS_ISO $spectrum" >> banana_timeseries.dat
	ssh pi@10.7.0.42 ./as7265x/src/t 0 0 0 3 200  > /dev/null
	sleep 900
done


