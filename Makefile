np=1
S=2

linearsnake.pdf: lreg.py snake.txt
	python3 lreg.py

snake.x: snake_main.cpp snake.h snake.cpp
	mpic++ $^ -o $@

snake.txt: snake.x
	mpirun -np $(np) ./$< $(S) > $@

clean:
	rm *.x *.out *.txt
