np=1
NP= {1..16}
S=2
P=1000

linearsnake.pdf: lreg.py metrica$(S).txt
	python3 $< $(S)

metrica$(S).txt: snake.x
	for i in $(NP) ; do mpirun -np $$i --oversubscribe ./$< $(S) $(P) ; done > $@

snake.x: snake_main.cpp snake.h snake.cpp
	mpic++ $^ -o $@

lifetime.txt: snake.x
	mpirun -np $(np) ./$< $(S) $(P) >> lifetime.txt
	touch snake.x

lifetime.pdf:
	python3 lifetime.py

clean:
	rm *.x *.out *.txt
