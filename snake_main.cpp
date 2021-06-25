#include <iostream>
#include <vector>
#include "mpi.h"
#include "snake.h"
int N=2; //dimension
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
  int p = P/np; //np preferiblemente ha de ser par

  jungle snakes(p);
  for(int i=0;i<t;i++)
  {
    for(int ii=0;ii<p;ii++)
    {
      random_step(N,snakes[ii]);
    }
  }

  for(int i=2;i<t;i++)
  {
    std::vector<double> resultados=promedios(snakes,i);

  int tag0 = 0, tag1=0, tag2=0;
  if (pid != 0) {
    // enviar time & val a pid 0
    int dest = 0;
    MPI_Send(&resultados[0], 1, MPI_DOUBLE, dest, tag0, MPI_COMM_WORLD);
    MPI_Send(&resultados[1], 1, MPI_DOUBLE, dest, tag1, MPI_COMM_WORLD);
    MPI_Send(&resultados[2], 1, MPI_DOUBLE, dest, tag2, MPI_COMM_WORLD);
  } else { // pid ==0
    // recibir de pid 1, 2, 3, 4, 5, ... , np-1
    std::vector<double> average = resultados;
    for (int ipid = 1; ipid < np; ++ipid) {
      MPI_Recv(&resultados[0], 1, MPI_DOUBLE, ipid, tag0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      average[0] += resultados[0];
    }
    for (int ipid = 1; ipid < np; ++ipid) {
      MPI_Recv(&resultados[1], 1, MPI_DOUBLE, ipid, tag1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      average[1] += resultados[1];
    }
    for (int ipid = 1; ipid < np; ++ipid) {
      MPI_Recv(&resultados[2], 1, MPI_DOUBLE, ipid, tag2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      average[2] += resultados[2];
    }

    if(average[0] != 0){
      std::cout<<i<<" \t "<<average[1]/np<<" \t "<<average[0]/np<<" \t "<< average[2]/np << std::endl;
    }
  }
  }

  MPI_Finalize();

  return 0;
}
