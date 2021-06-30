np=1 #variable inicial para controlar el número de procesos en lifetime.txt &.pdf
NP= {1..16} #rango donde varía el número de procesos usados
S=2 #dimensión
P=1000 #muestra, número de serpientes

#aquí se usa el script lreg.py que genera todas la gráficas, regresión, lifetime y métricas
linearsnake.pdf: lreg.py metrica$(S).txt 
	python3 $< $(S)

#el archivo métricas se genera con los datos de tiempo que tarda en ejecutarse con np procesos
#además al ejecutar ./snake.x se generan de forma automática archivos tales como snake$(S).txt y estadistica.txt
#snake$(S).txt contiene los datos para realizar la regresión, expected value & expected radius
#estadistica.txt contiene los datos de la vida media
metrica$(S).txt: snake.x
	for i in $(NP) ; do mpirun -np $$i --oversubscribe ./$< $(S) $(P) ; done > $@

snake.x: snake_main.cpp snake.h snake.cpp
	mpic++ $^ -o $@

snake$S.txt: snake.x
	mpirun -np $(np) ./$< $(S) $(P) > estadística.txt

#Se genera la grafica y regresión no lineal de la vida media died/totalsnakes
lifetime.txt: snake.x
	mpirun -np $(np) ./$< $(S) $(P) >> lifetime.txt
	touch snake.x
lifetime.pdf:
	./lifetime.sh	
	python3 dimension.py

clean:
	rm *.x *.out *.txt
