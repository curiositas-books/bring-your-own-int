#!/usr/bin/env gnuplot

set terminal pdf color
set output "benchmark_eratosthenes.pdf"
set title "Sieve of Eratosthenes Scaling" noenhanced
set ytics
set xtics

set xrange [50:20000000]
set logscale x 10
set format x "10^%T";
set yrange [2:1000000]
set logscale y 10
set format y "10^%T";

set xlabel "Maximal Prime"
set ylabel "Time in microseconds"

# Plot a line in black and the circles in green.
set style line 1 lc rgb 'black' pt 7 lw 2
set style line 2 lc rgb '#007021' pt 7 

set grid ytics back ls 0, ls 0
set grid xtics back ls 0, ls 0

plot "sieve_eratosthenes.dat" with lines ls 1 notitle,\
     "sieve_eratosthenes.dat" with points ls 2 notitle
