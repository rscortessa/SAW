np=1
S=2
P=1000

linearsnake.pdf: lreg.py snake$S$.txt
	python3 lreg.py $S$ &
	xpdf $@ &


snake.x: snake_main.cpp snake.h snake.cpp
	mpic++ $^ -o $@
snake$S$.txt: snake.x
	mpirun -np $(np) ./$< $(S) $(P) > estadística.txt
lifetime.txt: snake.x
	mpirun -np $(np) ./$< $(S) $(P) >> lifetime.txt
	python3 lifetime.py

clean:
	rm *.x *.out *.txt
