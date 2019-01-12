
set xrange [-.5:17.5]
set yrange [4000:10000]
set ylabel "time (arbitary)"
set cblabel "ADC counts (arbitary)"
set xlabel "AS7265x channels A (410nm), B, C, D, E, F, G, H, R (610nm), I, S, J, T, U, V, W, K, L (940nm)"
set title "AS7265x first results: several hours diffuse cloudy daylight (dawn to early morning)"

set palette model RGB defined
#set palette model HSV defined ( 0 0 1 1, 1 1 1 1 )


set terminal pngcairo size 1200,800
set output "first_results.png"
plot '<gunzip -c spectrum.dat.gz' matrix with image

