#include <iostream>
#include<vector>
#include "snake.h"
int N=3; //dimensio
int P=12; // Tamaño de la muestra
int t=1000; //pasos
int main (int argc, char** argv)
{
  N=std::atoi(argv[1]);
  jungle snakes(P);
  for(int i=0;i<t;i++)
  {
    for(int ii=0;ii<P;ii++)
    {
      random_step(N,snakes[ii]);
    }
  }
  for(int i=2;i<t;i++)
  {
    std::vector<double> resultados=promedios(snakes,i);
    if(resultados[0]!=0)
    {
      std::cout<<i<<"\t"<<resultados[1]<<"\t"<<resultados[0]<<"\t"<< resultados[2] << std::endl;
    }
	}
  return 0;
}

