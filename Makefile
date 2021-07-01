np=1 #variable inicial para controlar el número de procesos en lifetime.txt &.pdf
NP={1..16}
PASOS= 30 50 70 100 150
S=2 #dimensión
P=1000 #muestra, número de serpientes
T=100
#aquí se usa el script lreg.py que genera todas la gráficas, regresión, lifetime y métricas
linearsnake.pdf: lreg.py metrica$(S).txt 
	python3 $< $(S)

metrica$(S).txt: snake.x
	for i in $(NP) ; do mpirun -np $$i --oversubscribe ./$< $(S) $(P) $(T) ; done > $@

snake.x: snake_main.cpp snake.h snake.cpp
	mpic++ $^ -o $@

snake$S.txt: snake.x
	mpirun -np $(np) ./$< $(S) $(P) $(T) > estadística.txt
#Se genera la grafica y regresión no lineal de la vida media died/totalsnakes

lifetime.txt: snake.x
	mpirun -np $(np) ./$< $(S) $(P) $(T) >> lifetime.txt
	touch snake.x
lifetime.pdf:
	./lifetime.sh $(T)	
	python3 dimension.py $(T)
	mv exponente.png $(T)
	rm *.txt
GIF_dimension:
	echo This is just a test > f.txt
	rm *.txt
	for i in $(PASOS) ; do make lifetime.pdf T=$$i ; done
	python3 GIF.py
	mv png_to_gif.gif dimension.gif

clean:
	rm *.x *.out *.txt
