#!/usr/bin/env gnuplot

set terminal pdf color
set output "scaling_multiplication_division.pdf"
set title "Scaling of Multiplication and Division" noenhanced
set ytics
set xtics

set xrange [1:1050]
set yrange [0:5000000]

set xlabel "Number Length [bits]"
set ylabel "Time in nanoseconds [ns]"

# Plot a line in black and the circles in green.
set style line 1 lc rgb 'black' pt 7 lw 2
set style line 2 lc rgb '#007021' pt 7 
set style line 3 lc rgb '#61a1b0' pt 7 
set style line 4 lc rgb '#932909' pt 7 
set style line 5 lc rgb '#839432' pt 7 
set style line 6 lc rgb '#c5891d' pt 7 

set grid ytics back ls 0, ls 0
set grid xtics back ls 0, ls 0

set key off
set label "Multiplication" at 800,2950000 rotate by 30
set label "Division" at 800,1600000 rotate by 16
set label "Addition" at 830,200000

plot "biguint_efficient_multiplication.dat" with lines ls 1 notitle,\
     "biguint_efficient_multiplication.dat" with points ls 4 title "Multiplication", \
     "biguint_efficient_division.dat" with lines ls 1 notitle,\
     "biguint_efficient_division.dat" with points ls 5 title "Division", \
     "biguint_efficient_addition.dat" with lines ls 1 notitle,\
     "biguint_efficient_addition.dat" with points ls 3 title "Addition", \
