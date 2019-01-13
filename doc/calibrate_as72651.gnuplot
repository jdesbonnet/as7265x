set log y
set xrange [3:*]
plot \
  'halogen_calibration2.dat' using 1:21 with linespoints title '610nm' linecolor rgb "#ff08900", \
  '' using 1:22 with linespoints title '680nm' linecolor rgb '#ff0000', \
  '' using 1:23 with linespoints title '730nm' linecolor rgb '#bc0000', \
  '' using 1:24 with linespoints title '760nm' linecolor rgb '#790000', \
  '' using 1:25 with linespoints title '810nm' linecolor rgb '#000000', \
  '' using 1:26 with linespoints title '860nm' linecolor rgb '#000000', \
  '' using 1:27 with linespoints title '560nm' linecolor rgb '#bcff00', \
  '' using 1:28 with linespoints title '585nm' linecolor rgb '#ffeb00', \
  '' using 1:29 with linespoints title '645nm' linecolor rgb '#ff0000', \
  '' using 1:30 with linespoints title '705nm' linecolor rgb '#f30000', \
  '' using 1:31 with linespoints title '900nm' linecolor rgb '#000000', \
  '' using 1:32 with linespoints title '940nm' linecolor rgb '#000000', \
  '' using 1:33 with linespoints title '410nm' linecolor rgb '#6900d2', \
  '' using 1:34 with linespoints title '435nm' linecolor rgb '#1500ff', \
  '' using 1:35 with linespoints title '460nm' linecolor rgb '#0066ff', \
  '' using 1:36 with linespoints title '485nm' linecolor rgb '#00e5ff', \
  '' using 1:37 with linespoints title '510nm' linecolor rgb '#00ff00', \
  '' using 1:38 with linespoints title '535nm' linecolor rgb '#5bff00', \

pause -1

