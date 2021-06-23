S=2

linearsnake.pdf: lreg.py snake.txt
	python3 lreg.py &
	sleep 8
	xpdf $@ &

snake.x: snake_main.cpp snake.h snake.cpp
	g++ -g $^ -o $@

snake.txt: snake.x
	./$< $(S) > $@

clean:
	rm *.x *.out *.txt
