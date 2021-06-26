np=1
S=2


linearsnake.pdf: lreg.py snake$S$.txt
	python3 lreg.py $S$ &
	xpdf $@ &


snake.x: snake_main.cpp snake.h snake.cpp
	mpic++ $^ -o $@
snake$S$.txt: snake.x
	mpirun -np $(np) ./$< $(S) >> lifetime.txt


clean:
	rm *.x *.out *.txt
