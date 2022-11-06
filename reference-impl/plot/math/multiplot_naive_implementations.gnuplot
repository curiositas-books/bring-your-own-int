#!/usr/bin/env gnuplot

set terminal pdf color
set output "naive_operations.pdf"
set title "Scaling of Naive Base Operations" noenhanced
set ytics
set xtics

set xrange [1:100000]
set logscale x 10
set format x "10^%T";
set yrange [0:1000000000]
set logscale y 10
set format y "10^%T";

set xlabel "Decimal Number"
set ylabel "Time in microseconds"

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
set label "Exponentiation" at 20,18000 rotate by 33
set label "Multiplication" at 7000,180000 rotate by 13
set label "Division" at 8000,50
set label "Addition" at 10000,5
set label "Comparison" at 8000,0.5

plot "biguint_comparison.dat" with lines ls 1 notitle,\
     "biguint_comparison.dat" with points ls 2 title "Comparison", \
     "biguint_addition.dat" with lines ls 1 notitle,\
     "biguint_addition.dat" with points ls 3 title "Addition", \
     "biguint_multiplication.dat" with lines ls 1 notitle,\
     "biguint_multiplication.dat" with points ls 4 title "Multiplication", \
     "biguint_division.dat" with lines ls 1 notitle,\
     "biguint_division.dat" with points ls 5 title "Division", \
     "biguint_exponentiation.dat" with lines ls 1 notitle,\
     "biguint_exponentiation.dat" with points ls 6 title "Exponentiation", \
