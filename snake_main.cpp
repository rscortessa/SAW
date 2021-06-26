#include <iostream>
#include <vector>
#include "mpi.h"
#include "snake.h"
int N=2;//dimension
int P=1000; // Tamaño de la muestra
int t=5000; //pasos
int main (int argc, char** argv)
{
  MPI_Init(&argc, &argv);
  std::cout.precision(7);
  std::cout.setf(std::ios::scientific);

  N=std::atoi(argv[1]);
  if(N==2)
    {
      t=400;
    }
  else if(N==3)
    {
      t=5250;
    }
  else if(N==4)
    {
      t=500000;
    }
  int pid;
  int np;
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  int N=std::atoi(argv[1]);
  jungle snakes(P);
   double muertes=0;
  for(int i=0;i<t;i++)
  {
   
    for(int ii=0;ii<P;ii++)
      {
	if (snakes[ii].Life==true) random_step(N,snakes[ii]);
      }
  }
  double lifetime=print_promedios(t,snakes,"snake"+std::to_string(N)+".txt",pid,np);
  if(pid==0)
    {
  std::cout<<N<<"\t"<<lifetime<<std::endl;
    }
  MPI_Finalize();
  return 0;
}
