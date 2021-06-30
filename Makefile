np=1
NP= {1..16}
S=2
P=1000
T=100
linearsnake.pdf: lreg.py metrica$(S).txt
	python3 $< $(S)

metrica$(S).txt: snake.x
	for i in $(NP) ; do mpirun -np $$i --oversubscribe ./$< $(S) $(P) ; done > $@

snake.x: snake_main.cpp snake.h snake.cpp
	mpic++ $^ -o $@
snake$S.txt: snake.x
	mpirun -np $(np) ./$< $(S) $(P) $(T) > estadística.txt
lifetime.txt: snake.x
	mpirun -np $(np) ./$< $(S) $(P) $(T) >> lifetime.txt
	touch snake.x
lifetime.pdf:
	./lifetime.sh $(T)	
	python3 dimension.py
	mv exponente.png $(T).png

clean:
	rm *.x *.out *.txt
