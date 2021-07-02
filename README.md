# README PLEASE
## Self avoiding random walk
> El repositorio fue creado con el objetivo de resolver el problema del Self avoiding random walk en el marco de las actividades hechas en la clase de Herramientas computacionales.
> En matemáticas el self avoiding random walk (SAW) es una secuencia de movimientos aleatorios sobre una cuadricula (o lattice path) que no visita el misma punto más de una vez.
> En física computacional el SAW es un camino tipo cadena en 2 o 3 dimensiones (R^2 ó R^3) con una cierta cantidad de nodos, con la propiedad de tener la misma longitud en cada paso y que por supuesto el camino no se interseque a sí mismo.
## Repositorio
 #### ¿Como ejecutar el Makefile?
> El makefile tiene la opción de generar distintos archivos:
> * **linearsnake.pdf** archivo concerniente a la gráfica de las métricas
> * **metrica$(S).txt** Conjunto de datos relacionados con las métricas, se debe especificar la dimensión asignandole un valor a la variable S, (make S=...)
> * **snake.x** Es el ejecutable del código principal, necesario para generar los datos y las gráficas.
> * **snake$S.txt** Archivo de datos referentes a las gráficas principales, los datos se orga nizan de la forma:
> * * **paso** **r^2_{vivas}** **P_{death}**(Función de distribución)  **r_{muestra}^2** **p_{death}** (Función de densidad)
> * * **aux** Es un target auxiliar utilizado para crear **dimension.gif**
> * * **GIF_dimension** Regla para  construir dimension.gif, no hay que pasar ningún argumento por consola.
