set style data linespoints
set xlabel "x"; set ylabel "y"; set zlabel "z"
set key left top
set term pdf
show style data
set out "3Drandom_path.pdf"
set title "Random Path"
splot "3Drandom_path.txt" u 1:2:3 linecolor "black" pt 7 ps 0.4 notitle,\
"3Drandom_path.txt" u 1:2:3 w lines title "camino" lt rgb "navy"
unset output
set output "2Drandom_path.pdf"
set xlabel "x"; set ylabel "y"
set title "Random Path"
splot "2Drandom_path.txt" u 1:2 linecolor "black" pt 7 ps 0.4 notitle,\
"2Drandom_path.txt" u 1:2 w lines title "camino" lt rgb "navy"
unset output
unset terminal
