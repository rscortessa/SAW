set style data linespoints
set xlabel "Número de procesos"; set ylabel "Eficiencia & Speedup"
set key left top
set term pdf
show style data
set out "Montecarlo.pdf"
set title "Eficiencia y Speed up"
show bars
plot "metrica.txt" u 1:(437.979/$2) w yerrorbars linecolor "black" pt 7 ps 0.4 notitle,\
"metrica.txt" u 1:(437.979/$2) w lines title "Speed up" lt rgb "navy",\
"metrica.txt" u 1:(437.979/($2*$1)) with yerrorbars linecolor "black" pt 7 ps 0.4 notitle,\
"metrica.txt" u 1:(437.979/($2*$1)) with lines title "Eficiencia" lt rgb "red"
unset output
unset terminal
