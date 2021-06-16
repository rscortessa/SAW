set style data linespoints
set xlabel "n steps"; set ylabel "<R²>"
set logscale x 5; set logscale y 10
set key left top
set term pdf
show style data
set out "self_avoiding_walk2_0log.pdf"
set title "Random Path"
plot "datos.txt" u 1:2 linecolor "black" pt 7 ps 0.4 notitle,\
"datos.txt" u 1:2 w lines title "camino" lt rgb "navy"
unset logscale x; unset logscale y
unset output
set xlabel "n steps"; set ylabel "<R²>"
set key left top
set term pdf
show style data
set out "self_avoiding_walk2_0.pdf"
set title "Random Path"
plot "datos.txt" u 1:2 linecolor "black" pt 7 ps 0.4 notitle,\
"datos.txt" u 1:2 w lines title "camino" lt rgb "navy"
unset terminal
