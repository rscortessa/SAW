S=200000

random_path2D.pdf: plot.gp datos.txt
	gnuplot $<
	xpdf $@ &

path3D.x: path3D.cpp
	g++ $< -o $@

datos.txt: path3D.x
	./$< $(S) > $@

clean:
	rm *.x *.out *.txt *.pdf
