set log y
#set xrange [0.2:*]
set key at graph 0.3, 0.9

Rleads = 0.135
Ksb = 3.477E-13

bulb_T(Vpsu,Ipsu) = ((Vpsu*Ipsu - Ipsu*Ipsu*Rleads) / Ksb) ** 0.25 

bulb_power(T) = Ksb * T**4

#set y2tics
#set link y2 via bulb_temperature(y) inverse bulb_power(y)
 
f(Vpsu,Ipsu) = bulb_T(Vpsu,Ipsu)

plot \
  datafile using (f($1,$2)):21 with linespoints title 'AS72651 610nm' linecolor rgb "#ff08900", \
  '' using (f($1,$2)):22 with linespoints title 'AS72651 680nm' linecolor rgb '#ff0000', \
  '' using (f($1,$2)):23 with linespoints title 'AS72651 730nm' linecolor rgb '#bc0000', \
  '' using (f($1,$2)):24 with linespoints title 'AS72651 760nm' linecolor rgb '#790000', \
  '' using (f($1,$2)):25 with linespoints title 'AS72651 810nm' linecolor rgb '#000000', \
  '' using (f($1,$2)):26 with linespoints title 'AS72651 860nm' linecolor rgb '#000000', \
  '' using (f($1,$2)):27 with linespoints title 'AS72652 560nm' linecolor rgb '#bcff00', \
  '' using (f($1,$2)):28 with linespoints title 'AS72652 585nm' linecolor rgb '#ffeb00', \
  '' using (f($1,$2)):29 with linespoints title 'AS72652 645nm' linecolor rgb '#ff0000', \
  '' using (f($1,$2)):30 with linespoints title 'AS72652 705nm' linecolor rgb '#f30000', \
  '' using (f($1,$2)):31 with linespoints title 'AS72652 900nm' linecolor rgb '#000000', \
  '' using (f($1,$2)):32 with linespoints title 'AS72652 940nm' linecolor rgb '#000000', \
  '' using (f($1,$2)):33 with linespoints title '410nm' linecolor rgb '#6900d2', \
  '' using (f($1,$2)):34 with linespoints title '435nm' linecolor rgb '#1500ff', \
  '' using (f($1,$2)):35 with linespoints title '460nm' linecolor rgb '#0066ff', \
  '' using (f($1,$2)):36 with linespoints title '485nm' linecolor rgb '#00e5ff', \
  '' using (f($1,$2)):37 with linespoints title '510nm' linecolor rgb '#00ff00', \
  '' using (f($1,$2)):38 with linespoints title '535nm' linecolor rgb '#5bff00'

pause -1

