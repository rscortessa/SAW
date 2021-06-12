set style data linespoints
set xlabel "x"; set ylabel "y"
set key left top
set term pdf
show style data
set out "random_path.pdf"
set title "Random Path"
show bars
plot "datos.txt" u 1:2 w yerrorbars linecolor "black" pt 7 ps 0.4 notitle,\
"datos.txt" u 1:2 w lines title "camino" lt rgb "navy"
unset output
unset terminal
