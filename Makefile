S=30
W=101

self_avoiding_walk2_0log.pdf: plot.gp datos.txt
	gnuplot $<
	xpdf $@ &

self_avoiding_walk2_0.x: self_avoiding_walk2_0.cpp
	g++ $< -o $@

datos.txt: self_avoiding_walk2_0.x
	./$< $(S) $(W) > $@

clean:
	rm *.x *.out *.txt *.pdf
