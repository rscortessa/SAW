set style data linespoints
set xlabel "x"; set ylabel "y"
set key left top
set term pdf
show style data
set out "random_path.pdf"
set title "Ramdom Path"
show bars
plot "datos.txt" u 1:2 w yerrorbars linecolor "black" pt 7 ps 0.4 notitle,\
"datos.txt" u 1:2 w lines title "O0" lt rgb "navy", \
"datos.txt" u 1:2 with yerrorbars linecolor "black" pt 7 ps 0.4 notitle, \
"datos.txt" u 1:2 with lines title "O3" lt rgb "red"
unset output
unset terminal
