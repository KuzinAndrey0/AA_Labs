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

plot 'the_data.csv' using 1:2 title 'Плавная сортировка' with lines, \
        'the_data.csv' using 1:3 title 'Сортировка перемешиванием' with lines, \
        'the_data.csv' using 1:4 title 'Сортировка Шелла' with lines

