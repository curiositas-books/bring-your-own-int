#!/usr/bin/env gnuplot

set terminal pdf color
set output "efficient_operations.pdf"
set title "Scaling of Efficient Base Operations" noenhanced
set ytics
set xtics

set xrange [1:1050]
set yrange [0:1100000000]
set logscale y
set format y "10^{%T}";
set y2range [0:1100000000]
set logscale y2

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
set label "Exponentiation" at 40,100000 rotate by 88
set label "Multiplication" at 800,6000000 rotate by 3
set label "Division" at 800,500000 rotate by 3
set label "Addition" at 800,5000 rotate by 2
set label "Comparison" at 800,150 rotate by 2

plot "biguint_efficient_comparison.dat" with lines ls 1 notitle,\
     "biguint_efficient_comparison.dat" with points ls 2 title "Comparison", \
     "biguint_efficient_addition.dat" with lines ls 1 notitle,\
     "biguint_efficient_addition.dat" with points ls 3 title "Addition", \
     "biguint_efficient_multiplication.dat" with lines ls 1 notitle,\
     "biguint_efficient_multiplication.dat" with points ls 4 title "Multiplication", \
     "biguint_efficient_division.dat" with lines ls 1 notitle,\
     "biguint_efficient_division.dat" with points ls 5 title "Division", \
     "biguint_efficient_exponentiation.dat" with lines ls 1 notitle axis x1y1,\
     "biguint_efficient_exponentiation.dat" with points ls 6 title  "Exponentiation" axis x1y1, \
