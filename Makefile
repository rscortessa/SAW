random_pah.pdf: plot.gp datos.txt
	gnuplot $<
	xpdf $@ &

%.x: %.cpp
	g++ $< -o $@

datos.txt: prueba-2D.x
	./$< > $@

clean:
	rm *.x *.out *.txt *.pdf
