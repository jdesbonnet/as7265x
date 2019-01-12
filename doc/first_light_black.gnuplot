set title "AS7265x first light: several hours diffuse cloudy daylight (dawn to early morning, 2019-01-11)\nhttps://github.com/jdesbonnet/as7265x" textcolor rgb 'white' font ",24"

set ylabel "time (arbitary)" textcolor rgb 'white' font ",18"
set cblabel "ADC counts (arbitary)" textcolor rgb 'white' font ",18"
set xlabel "AS7265x channels A (410nm), B, C, D, E, F, G, H, R (610nm), I, S, J, T, U, V, W, K, L (940nm)" textcolor rgb 'white' font ",18"

set xrange [-.5:17.5]
set yrange [0:*]

set palette model RGB defined
#set palette model HSV defined ( 0 0 1 1, 1 1 1 1 )


set border linecolor rgb 'white'
set key textcolor rgb 'white'

unset xtics
unset ytics

set terminal pngcairo size 1920,1080 background rgb 'black' 
set output "as7265x_first_light.png"
plot '<gunzip -c as7265x-20190111A.dat.gz' matrix with image
#plot 't.t' matrix with image
