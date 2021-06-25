#include <iostream>
#include <vector>
#include "mpi.h"
#include "snake.h"
int N=2;//dimension
int P=2000; // Tamaño de la muestra
int t=1000; //pasos
int main (int argc, char** argv)
{
  MPI_Init(&argc, &argv);
  std::cout.precision(7);
  std::cout.setf(std::ios::scientific);

  int pid;
  int np;
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  int N=std::atoi(argv[1]);

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
    std::vector<double> average = resultados;

    MPI_Reduce(&resultados[0], &average[0], 3, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if(pid == 0){
    if(average[0] != 0){
      std::cout<<i<<" \t "<<average[1]/np<<" \t "<<average[0]/np<<" \t "<< average[2]/np << std::endl;
    }}
  }

  MPI_Finalize();

  return 0;
}
