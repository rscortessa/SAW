set style data linespoints
set xlabel "n steps"; set ylabel "<R²>"
set logscale x 5; set logscale y 10
set key left top
set term pdf
show style data
set out "snakelog.pdf"
set title "Random Path"
plot "snake.txt" u 1:2 linecolor "black" pt 7 ps 0.4 notitle,\
"snake.txt" u 1:2 w lines title "camino" lt rgb "navy"
unset logscale x; unset logscale y
unset output
set xlabel "n steps"; set ylabel "<R²>"
set key left top
set term pdf
show style data
set out "snake.pdf"
set title "Random Path"
plot "snake.txt" u 1:2 linecolor "black" pt 7 ps 0.4 notitle,\
"snake.txt" u 1:2 w lines title "camino" lt rgb "navy"
set xlabel "n steps"; set ylabel "<t>"
set logscale x 5; set logscale y 10
set key left top
set term pdf
show style data
set out "snakelogtime.pdf"
set title "Random Path"
plot "snake.txt" u 1:3 linecolor "black" pt 7 ps 0.4 notitle,\
"snake.txt" u 1:3 w lines title "camino" lt rgb "navy"
unset logscale x; unset logscale y
unset output
set xlabel "n steps"; set ylabel "<t>"
set key left top
set term pdf
show style data
set out "snaketime.pdf"
set title "Random Path"
plot "snake.txt" u 1:3 linecolor "black" pt 7 ps 0.4 notitle,\
"snake.txt" u 1:3 w lines title "camino" lt rgb "navy"
unset terminal
