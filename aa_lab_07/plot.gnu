#!/usr/bin/gnuplot

reset

# png
set terminal svg size 640,500 enhanced font 'Verdana,8'
set output 'plotting_data1.svg'
# show output

set border linewidth 1
# Set first linestyle to blue (#0060ad)

set ylabel "Время, мс" font 'Verdana,12'
set xtics rotate by -45
unset key

set boxwidth 0.5
set style fill solid
plot "average.csv" using 1:3:4:xtic(2) with boxes lc variable
