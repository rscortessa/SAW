S=625
W=100

snakelog.pdf: plot.gp snake.txt
	gnuplot $<
	xpdf $@ &

snake.x: snake_main.cpp
	g++ -g $< -o $@

snake.txt: snake.x
	./$< > $@

clean:
	rm *.x *.out *.txt
