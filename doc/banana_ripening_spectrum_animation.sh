#!/bin/bash

CHANNEL_ORDER="12 13 14 15 16 17 6 7 0 8 1 9 2 3 4 5 10 11"
order=($CHANNEL_ORDER)
ORDERED_WAVELENGTHS="410 435 460 485 510 535 560 585 610 645 680 705 730 760 810 860 900 940"
wavelength=($ORDERED_WAVELENGTHS)
frame=1000
while IFS='' read -r line || [[ -n "$line" ]]; do

	gnuplot_file=frame-${frame}.gnuplot
	columns=($line)

	# Order channels in ascending wavelength
	for i in $(seq 0 1 17); do
		col_index=$((order[i]+20)) 
		spectrum[$i]=${columns[$col_index]}
	done

	echo $line
	(
	cat <<EOF
set terminal pngcairo size 640,480
set output 'frame-${frame}.png'
set title 'Banan ripening (reflection from combination of UV, white, NIR LEDs on skin) ${columns[1]}'
set xlabel "wavelegth (nm)"
set yrange [0:4500]
EOF
	) > $gnuplot_file

	echo "\$data << EOD" >> $gnuplot_file

	for i in $(seq 0 1 17); do
		echo "${wavelength[$i]} ${spectrum[$i]}" >> $gnuplot_file
	done

	(
	cat <<EOF
EOD
set samples 600
set table \$interpolated
plot \$data using 1:2 with table smooth acspline
unset table
plot \$data using 1:2 title 'data points', \$interpolated using 1:2 with lines title 'interpolated spectrum'
EOF
	) >> $gnuplot_file

	gnuplot frame-${frame}.gnuplot
	#rm frame-${frame}.gnuplot

	frame=$((frame+1))
	
done

rm banana.mp4
ffmpeg -start_number 1000 -i frame-%d.png -c:v libx264 -r 30 banana.mp4

