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

plot 'time.dat' using 1:2 title 'Полный перебор' with points ps 2, 'time2.dat' using 1:2 title 'Муравьиный алгоритм' with points ps 2