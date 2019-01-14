

set title "AS72651 sensitivity curve"
load 'black_body_radiator.gnuplot'
load 'as7265x_common.gnuplot'
 
f(Vpsu,Ipsu) = bulb_T(Vpsu,Ipsu)

plot \
  datafile using (f($1,$2)):21 with linespoints title 'AS72651 R 610nm' linecolor rgb "#ff8900", \
  '' using (f($1,$2)):22 with linespoints title 'AS72651 S 680nm' linecolor rgb '#ff0000', \
  '' using (f($1,$2)):23 with linespoints title 'AS72651 T 730nm' linecolor rgb '#bc0000', \
  '' using (f($1,$2)):24 with linespoints title 'AS72651 U 760nm' linecolor rgb '#790000', \
  '' using (f($1,$2)):25 with linespoints title 'AS72651 V 810nm' linecolor rgb '#000000', \
  '' using (f($1,$2)):26 with linespoints title 'AS72651 W 860nm' linecolor rgb '#000000', \
  'plank_theory_610nm.dat' using 1:($2*15e-9) with lines title '610nm (theory)' linecolor rgb '#ff8900' dt 2, \
  'plank_theory_680nm.dat' using 1:($2*15e-9) with lines title '680nm (theory)' linecolor rgb '#ff0000' dt 2, \
  'plank_theory_730nm.dat' using 1:($2*15e-9) with lines title '730nm (theory)' linecolor rgb '#bc0000' dt 2, \
  'plank_theory_760nm.dat' using 1:($2*15e-9) with lines title '760nm (theory)' linecolor rgb '#790000' dt 2, \
  'plank_theory_810nm.dat' using 1:($2*15e-9) with lines title '810nm (theory)' linecolor rgb '#000000' dt 2, \
  'plank_theory_860nm.dat' using 1:($2*15e-9) with lines title '860nm (theory)' linecolor rgb '#000000' dt 2


pause -1

