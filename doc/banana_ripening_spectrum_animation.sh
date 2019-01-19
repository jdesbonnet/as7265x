#!/bin/bash

CHANNEL_ORDER="12 13 14 15 16 17 6 7 0 8 1 9 2 3 4 5 10 11"
order=($CHANNEL_ORDER)
ORDERED_WAVELENGTHS="410 435 460 485 510 535 560 585 610 645 680 705 730 760 810 860 900 940"
wavelength=($ORDERED_WAVELENGTHS)
frame=1000
while IFS='' read -r line || [[ -n "$line" ]]; do
	columns=($line)

	# Order channels in ascending wavelength
	for i in $(seq 0 1 17); do
		col_index=$((order[i]+20)) 
		spectrum[$i]=${columns[$col_index]}
		echo "col_index=$col_index ${spectrum[$i]}"
	done

	echo $line
	(
	cat <<EOF
set terminal pngcairo size 640,480
set output 'frame-${frame}.png'
set title '${columns[1]}'
set xlabel "wavelegth (nm)"
set yrange [0:4000]
plot '-' using 1:2 with linespoints
EOF
	) > frame-${frame}.gnuplot

	#for i in $(seq 20 1 37); do
	#	echo ${columns[i]} >> frame-${frame}.gnuplot
	#done
	for i in $(seq 0 1 17); do
		echo "${wavelength[$i]} ${spectrum[$i]}" >> frame-${frame}.gnuplot
	done

	gnuplot frame-${frame}.gnuplot
	#rm frame-${frame}.gnuplot

	frame=$((frame+1))
	
done

ffmpeg -start_number 1000 -i frame-%d.png -c:v libx264 -r 30 banana.mp4

