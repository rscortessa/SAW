S=2

linearsnake.pdf: lreg.py snake$S$.txt
	python3 lreg.py $S$ &
	xpdf $@ &

snake.x: snake_main.cpp snake.h snake.cpp
	g++ -g $^ -o $@

snake$S$.txt: snake.x
	./$< $(S) >> lifetime.txt

clean:
	rm *.x *.out *.txt
