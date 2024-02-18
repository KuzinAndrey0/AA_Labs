#!/usr/bin/gnuplot

reset

# png
set terminal svg size 640,360 enhanced font 'Verdana,8'
set output 'plotting_data1.svg'
# show output

set border linewidth 1
# Set first linestyle to blue (#0060ad)

set xlabel "Размер массива, шт" font 'Verdana,12'
set ylabel "Время, мс" font 'Verdana,12'
set key left top
set logscale y

plot 'difsize.csv' using 1:2 title 'Линейная очередь' with lines, \
        'difsize.csv' using 1:3 title 'Конвеерная очередь' with lines
unset logscale y
set output 'plotting_data2.svg'
plot 'samesize.csv' using 1:2 title 'Линейная очередь' with lines, \
        'samesize.csv' using 1:3 title 'Конвеерная очередь' with lines
