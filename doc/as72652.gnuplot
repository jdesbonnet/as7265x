
set title "AS72652 sensitivity curve"

load 'black_body_radiator.gnuplot'
load 'as7265x_common.gnuplot'
 
f(Vpsu,Ipsu) = bulb_T(Vpsu,Ipsu)

plot \
  datafile \
     using (f($1,$2)):27 with linespoints title 'AS72652 G 560nm' linecolor rgb '#bcff00', \
  '' using (f($1,$2)):28 with linespoints title 'AS72652 H 585nm' linecolor rgb '#ffeb00', \
  '' using (f($1,$2)):29 with linespoints title 'AS72652 I 645nm' linecolor rgb '#ff0000', \
  '' using (f($1,$2)):30 with linespoints title 'AS72652 J 705nm' linecolor rgb '#f30000', \
  '' using (f($1,$2)):31 with linespoints title 'AS72652 K 900nm' linecolor rgb '#000000', \
  '' using (f($1,$2)):32 with linespoints title 'AS72652 L 940nm' linecolor rgb '#000000', \
  'plank_theory_560nm.dat' using 1:($2*15e-9) with lines title '610nm (theory)' linecolor rgb '#bcff00' dt 2, \
  'plank_theory_585nm.dat' using 1:($2*15e-9) with lines title '680nm (theory)' linecolor rgb '#ffeb00' dt 2, \
  'plank_theory_645nm.dat' using 1:($2*15e-9) with lines title '730nm (theory)' linecolor rgb '#ff0000' dt 2, \
  'plank_theory_705nm.dat' using 1:($2*15e-9) with lines title '760nm (theory)' linecolor rgb '#f30000' dt 2, \
  'plank_theory_900nm.dat' using 1:($2*15e-9) with lines title '810nm (theory)' linecolor rgb '#000000' dt 2, \
  'plank_theory_940nm.dat' using 1:($2*15e-9) with lines title '860nm (theory)' linecolor rgb '#000000' dt 2


pause -1

