#!/usr/bin/gnuplot

reset

# png
set terminal svg size 640,360 enhanced font 'Verdana,8'
set output 'plotting_data1.svg'
# show output

set border linewidth 1
# Set first linestyle to blue (#0060ad)

set xlabel "Кол-во символов, шт" font 'Verdana,12'
set ylabel "Время, мс" font 'Verdana,12'
set key left top

plot 'the_data.csv' using 1:2 title 'Виноград без оптимизаций' with lines, \
        'the_data.csv' using 1:3 title 'Оптимизированный виноград' with lines, \
        'the_data.csv' using 1:4 title 'Классический алгоритм' with lines, \
        'the_data.csv' using 1:3 title 'Алгоритм Штрассена' with lines


