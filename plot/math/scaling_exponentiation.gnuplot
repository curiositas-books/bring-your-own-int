#!/usr/bin/env gnuplot

set terminal pdf color
set output "scaling_exponentiation.pdf"
set title "Scaling of Exponentiation compared to Python" noenhanced
set ytics
set xtics

set xrange [1:25]
set yrange [0:10000000000]
set logscale y

set xlabel "Exponent Length [bits]"
set ylabel "Time in nanoseconds [ns]"

# set y2label "Time for Exponentiation in nanoseconds"

# Plot a line in black and the circles in green.
set style line 1 lc rgb 'black' pt 7 lw 2
set style line 2 lc rgb '#007021' pt 7 
set style line 3 lc rgb '#61a1b0' pt 7 
set style line 4 lc rgb '#932909' pt 7 
set style line 5 lc rgb '#839432' pt 7 
set style line 6 lc rgb '#c5891d' pt 7 

set grid ytics back ls 0, ls 0
set grid xtics back ls 0, ls 0

# set key top left reverse Left
set key off
set label "Exponentiation BigUInt" at 4,80000 rotate by 25
set label "Exponentiation Python" at 8,4000 rotate by 23

plot "biguint_efficient_exponentiation.dat" with lines ls 1 notitle,\
     "biguint_efficient_exponentiation.dat" with points ls 5 title "BigUInt", \
     "python_exponentiation.dat" with lines ls 1 notitle,\
     "python_exponentiation.dat" with points ls 6 title "Python", \
