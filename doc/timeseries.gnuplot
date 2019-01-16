set grid
set log y

datafile="banana_timeseries.dat"

plot \
  datafile \
     using 1:21 with linespoints title 'AS72651 R 610nm' linecolor rgb "#ff08900", \
  '' using 1:22 with linespoints title 'AS72651 S 680nm' linecolor rgb '#ff0000', \
  '' using 1:23 with linespoints title 'AS72651 T 730nm' linecolor rgb '#bc0000', \
  '' using 1:24 with linespoints title 'AS72651 U 760nm' linecolor rgb '#790000', \
  '' using 1:25 with linespoints title 'AS72651 V 810nm' linecolor rgb '#000000', \
  '' using 1:26 with linespoints title 'AS72651 W 860nm' linecolor rgb '#000000', \
  '' using 1:27 with linespoints title 'AS72652 G 560nm' linecolor rgb '#bcff00', \
  '' using 1:28 with linespoints title 'AS72652 H 585nm' linecolor rgb '#ffeb00', \
  '' using 1:29 with linespoints title 'AS72652 I 645nm' linecolor rgb '#ff0000', \
  '' using 1:30 with linespoints title 'AS72652 J 705nm' linecolor rgb '#f30000', \
  '' using 1:31 with linespoints title 'AS72652 K 900nm' linecolor rgb '#000000', \
  '' using 1:32 with linespoints title 'AS72652 L 940nm' linecolor rgb '#000000', \
  '' using 1:33 with linespoints title 'AS72653 A 410nm' linecolor rgb '#6900d2', \
  '' using 1:34 with linespoints title 'AS72653 B 435nm' linecolor rgb '#1500ff', \
  '' using 1:35 with linespoints title 'AS72653 C 460nm' linecolor rgb '#0066ff', \
  '' using 1:36 with linespoints title 'AS72653 D 485nm' linecolor rgb '#00e5ff', \
  '' using 1:37 with linespoints title 'AS72653 E 510nm' linecolor rgb '#00ff00', \
  '' using 1:38 with linespoints title 'AS72653 F 535nm' linecolor rgb '#5bff00'

pause -1
