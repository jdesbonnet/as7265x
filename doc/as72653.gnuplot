
set title "AS72653 sensitivity curve"

load 'black_body_radiator.gnuplot'
load 'as7265x_common.gnuplot'
 
f(Vpsu,Ipsu) = bulb_T(Vpsu,Ipsu)


sdscale = 50e-8

plot \
  datafile \
     using (f($1,$2)):33 with linespoints title 'AS72653 A 410nm' linecolor rgb '#6900d2', \
  '' using (f($1,$2)):34 with linespoints title 'AS72653 B 435nm' linecolor rgb '#1500ff', \
  '' using (f($1,$2)):35 with linespoints title 'AS72653 C 460nm' linecolor rgb '#0066ff', \
  '' using (f($1,$2)):36 with linespoints title 'AS72653 D 485nm' linecolor rgb '#00e5ff', \
  '' using (f($1,$2)):37 with linespoints title 'AS72653 E 510nm' linecolor rgb '#00ff00', \
  '' using (f($1,$2)):38 with linespoints title 'AS72653 F 535nm' linecolor rgb '#5bff00', \
  'plank_theory_410nm.dat' using 1:($2*sdscale) with lines title '410nm (theory)' linecolor rgb '#6900d2' dt 2, \
  'plank_theory_435nm.dat' using 1:($2*sdscale) with lines title '435nm (theory)' linecolor rgb '#1500ff' dt 2, \
  'plank_theory_460nm.dat' using 1:($2*sdscale) with lines title '460nm (theory)' linecolor rgb '#0066ff' dt 2, \
  'plank_theory_485nm.dat' using 1:($2*sdscale) with lines title '485nm (theory)' linecolor rgb '#00e5ff' dt 2, \
  'plank_theory_510nm.dat' using 1:($2*sdscale) with lines title '510nm (theory)' linecolor rgb '#00ff00' dt 2, \
  'plank_theory_535nm.dat' using 1:($2*sdscale) with lines title '535nm (theory)' linecolor rgb '#5bff00' dt 2


pause -1

