#include <iostream>
#include <time.h>
#include <stdio.h>
// Este codigo genera un caminante en diagonal, es decir que su velocidad no es 1/iteración sino sqrt(2)/iteración, esto se debe tener en cuenta para el analisis de resultados pero no interfiere propiamente con lo que se quiere simular.


int* random_step(int dimension, int *r);//función que determina el avance del caminante en cada paso

int main(int argc, char **argv)
{
  int dimension=2; //dimensiones a utilizar
  int total_steps=20; //cantidad de pasos a llevar a cabo, en un futuro se podría implementar un while y que se desarrolle hasta que el caminante quede encerrado, además de que aún no se ha implementado un "marco" dónde encerrar al caminante
  int history [total_steps][dimension]={};//este es el array que guarda los puntos para que no se repitan
  int aux_position [dimension]={};//este array es un auxiliar que almacena el nuevo paso antes de enviarlo a position, la motivación detrás de esto se explicará más adelante
  int position [dimension]={};//este array es la posicion del caminante en un momento dado
  int proof=0;//es un valor que asiste en el proceso de determinar si ya se pisó un punto o no
  
  srand((unsigned) time(NULL));//inicializa semilla del randomizador según el tiempo de la maquina, para que siempre sea distinto.
  for(int ii=0; ii<total_steps; ++ii)
    {
      random_step(dimension,aux_position); //se determina el punto al que se debe caminar
      
      for(int jj=0; jj<ii; ++jj)
	{
	  if(aux_position[0]==history[jj][0] && aux_position[1]==history[jj][1])//este ciclo revisa las entradas del array history y las compara con el valor actual del array aux_position.
	    {
	      proof=1;//si hay una coincidencia en las coordenadas, proof toma el valor de 1 y el ciclo se rompe
	      break;
	    }
	  else
	    {
	      proof=0;//si no hay coincidencia proof sigue siendo 0
	    }
	}
      std::cout<<"proof"<<"\t"<<proof<<std::endl;//esto cout se puso con proposito de visualizar que el sistema funcionaba
      if(proof==1)//si proof=1 (es decir, se dió una posición repetida)
	{
	  proof=0;//se inicializa proof=0 
	  
	  history[ii+1][0] = aux_position[0];//se escribe en el historial la posición repetida (no es necesario para que funcione pero ayuda a evidenciar cuando hay una posición repetida y saber que el codigo funciona
	  history[ii+1][1] = aux_position[1];
	  // std::cout<<"aux position"<<"\t"<<aux_position[0]<<"\t"<<aux_position[1]<<std::endl;
	  //std::cout<<"position"<<"\t"<<position[0]<<"\t"<<position[1]<<std::endl;
	  aux_position[0]=position[0];//se remplaza aux_position por la posición del paso anterior (position) para poder empezar el ciclo otra vez y que el caminante pueda moverse a una casilla que no sea repetida.
	  aux_position[1]=position[1];
	  continue;
	}
      else//si proof=0 (No hay posición repetida), se puede dar al array position los valores del nuevo paso (array aux_position) y se procede a imprimirlos y a registrarlos en el historial
	{
	  
	  position[0]=aux_position[0];
	  position[1]=aux_position[1];
	    
	  history[ii+1][0] = position[0];
	  history[ii+1][1] = position[1];
        

	  //std::cout<<"aux position"<<"\t"<<aux_position[0]<<"\t"<<aux_position[1]<<std::endl;
	  std::cout<<"position"<<"\t"<<position[0]<<"\t"<<position[1]<<std::endl;
	}
    }

  std::cout<<"--------------------------------------"<<std::endl; //acá se imprime el historial por propositos de prueba, ya que en el historial si quedan registradas las repeticiones, entonces así se puede saber si las posiciones repetidas si fueron descartadas en el ciclo anterior.
  
  for(int ii=0; ii<total_steps+1; ++ii)
    {
      for(int jj=0; jj<dimension; ++jj)
	{
	  std::cout<<history[ii][jj]<<"\t";
	}
      std::cout<<std::endl;
    }
  return 0;
}

int* random_step(int dimension, int *r)//esta funcion da un numero aleatorio que puede ser 1 o 0 con igual probabilidad, si es 1 retorna -1 y si es 0 retorna 1.
{
  
  double step_value = 0;
  int random_number;
  int number;
  random_number = rand() % dimension;
  number=rand() % 2;
  if (number == 1)
    {
      step_value = -1;
      r[random_number]+=step_value;
    }
  else
    {
      step_value = 1;
      r[random_number]+=step_value;
    }
  
  return 0;
}
