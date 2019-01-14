set log y
#set xrange [0.2:*]
set key at graph 0.3, 0.9

Rleads = 0.135
Ksb = 3.477E-13

load 'black_body_radiator.gnuplot'

#set y2tics
#set link y2 via bulb_temperature(y) inverse bulb_power(y)
 
f(Vpsu,Ipsu) = bulb_T(Vpsu,Ipsu)

plot \
  datafile using (f($1,$2)):21 with linespoints title 'AS72651 R 610nm' linecolor rgb "#ff08900", \
  '' using (f($1,$2)):22 with linespoints title 'AS72651 S 680nm' linecolor rgb '#ff0000', \
  '' using (f($1,$2)):23 with linespoints title 'AS72651 T 730nm' linecolor rgb '#bc0000', \
  '' using (f($1,$2)):24 with linespoints title 'AS72651 U 760nm' linecolor rgb '#790000', \
  '' using (f($1,$2)):25 with linespoints title 'AS72651 V 810nm' linecolor rgb '#000000', \
  '' using (f($1,$2)):26 with linespoints title 'AS72651 W 860nm' linecolor rgb '#000000', \
  '' using (f($1,$2)):27 with linespoints title 'AS72652 G 560nm' linecolor rgb '#bcff00', \
  '' using (f($1,$2)):28 with linespoints title 'AS72652 H 585nm' linecolor rgb '#ffeb00', \
  '' using (f($1,$2)):29 with linespoints title 'AS72652 I 645nm' linecolor rgb '#ff0000', \
  '' using (f($1,$2)):30 with linespoints title 'AS72652 J 705nm' linecolor rgb '#f30000', \
  '' using (f($1,$2)):31 with linespoints title 'AS72652 K 900nm' linecolor rgb '#000000', \
  '' using (f($1,$2)):32 with linespoints title 'AS72652 L 940nm' linecolor rgb '#000000', \
  '' using (f($1,$2)):33 with linespoints title 'AS72653 A 410nm' linecolor rgb '#6900d2', \
  '' using (f($1,$2)):34 with linespoints title 'AS72653 B 435nm' linecolor rgb '#1500ff', \
  '' using (f($1,$2)):35 with linespoints title 'AS72653 C 460nm' linecolor rgb '#0066ff', \
  '' using (f($1,$2)):36 with linespoints title 'AS72653 D 485nm' linecolor rgb '#00e5ff', \
  '' using (f($1,$2)):37 with linespoints title 'AS72653 E 510nm' linecolor rgb '#00ff00', \
  '' using (f($1,$2)):38 with linespoints title 'AS72653 F 535nm' linecolor rgb '#5bff00'

pause -1

