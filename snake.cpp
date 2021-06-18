#include <iostream>
#include <time.h>
#include <stdio.h>
#include <cmath>
#ifndef _RANDOM_H_
#define _RANDOM_H_
#include "snake.h"
#endif
void random_step(int dimension,snake &f)
{
  
  data_r dr(dimension,0);
  double step_value = 0;
  int random_number;
  int number;
  random_number = rand() % dimension;
  number=rand() % 2;
  if (number == 1)
    {
     
      step_value = -1;
      dr[random_number]+=step_value;
      f.sumar_r(dr);
    }
  else
    {
      step_value = 1;
      dr[random_number]+=step_value;
      f.sumar_r(dr);
    }
 
}
double promedio_r(jungle & snakes, int paso)
{
  double prom;
  double count;
  for(auto x : snakes)
    {
      walkers aux=x.obtener_History();
      if(aux.size()<paso)
	{
	}
      else
	{
	  count+=1;
	  for(auto y : aux[paso-1])
	    {
	      prom+=y*y;
	    }
	}
    }
  return prom/count;
}

