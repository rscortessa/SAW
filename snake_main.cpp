#include <iostream>
#include<vector>
#include<cmath>
#include "snake.h"
int N=3; //dimensio
int P=1000; // Tamaño de la muestra
int t=150; //pasos
int main (int argc, char** argv)
{
  std::cout.precision(7);
  std::cout.setf(std::ios::scientific);
  N=std::atoi(argv[1]);
  if(N==2)
    {
      t=150;
    }
  else if(N==3)
    {
      t=5250;
    }
  else if(N==4)
    {
      t=500000;
    }
  jungle snakes(P);
  for(int i=0;i<t;i++)
  {
    for(int ii=0;ii<P;ii++)
    {
      random_step(N,snakes[ii]);
    }
  }
  std::cout<<N<<"\t"<<print_promedios(t,snakes,"snake"+std::to_string(N)+".txt")<<std::endl;
  
  return 0;
}

