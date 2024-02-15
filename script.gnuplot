set xlabel "Number of instructions in basic block"
set ylabel "Frequency"
set title "Distribution of number of instructions per basic block"

stats 'tmp.dat' name 'data' nooutput
scaled_max_y = data_max_y * 1.25
set yrange[0 : scaled_max_y]

set boxwidth 0.5
set style fill solid

set terminal pdf

plot 'tmp.dat' using 2:xtic(1) with boxes notitle