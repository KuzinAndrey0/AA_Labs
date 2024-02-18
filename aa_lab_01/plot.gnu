#!/usr/bin/gnuplot

reset

# png
set terminal svg size 640,360 enhanced font 'Verdana,16'
set output 'plotting_data1.svg'
# show output

set border linewidth 1
# Set first linestyle to blue (#0060ad)

set xlabel "Кол-во символов, шт" font 'Verdana,12'
set ylabel "Время, мс" font 'Verdana,12'

plot 'the_data.csv' using 1:2 title 'Дамерау Левенштейн с использованием хэш таблицы' with lines, \
        'the_data.csv' using 1:3 title 'Рекурсивный Дамерау Левенштейн' with lines
#plot 'the_data.csv' using 1:3 title 'matrix dam lev' with lines, \
#     'the_data.csv' using 1:4 title 'matrix lev' with lines

#plot 'the_data.csv' using 1:2 title 'Дамерау Левенштейн с использованием матрицы' with lines, \
#     'the_data.csv' using 1:3 title 'Левенштейн с использованием матрицы' with lines
