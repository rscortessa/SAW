#include <iostream>
#include <vector>
#include "mpi.h"
#include "snake.h"

int main (int argc, char** argv)
{
  MPI_Init(&argc, &argv);
  std::cout.precision(7);
  std::cout.setf(std::ios::scientific);

  int t=0;
  int N=std::atoi(argv[1]);
  int P=std::atoi(argv[2]);
  if(N==2)
    {
      t=400;
    }
  else if(N==3)
    {
      t=8250;
    }
  else
    {
      t=10000;
    }
  int pid;
  int np;
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    int PP=P/np;
  jungle snakes(PP, snake(N));
  double muertes=0;

  double t0 = MPI_Wtime();//time strats to run
  for(int i=0;i<t;i++)
  {
   
    for(int ii=0;ii<PP;ii++)
      {
	if (snakes[ii].Life==true) random_step(N,snakes[ii]);
      }
  }
  std::vector<double> lifetime=print_promedios(t,snakes,"snake"+std::to_string(N)+".txt",pid,np,PP);
  double t1 = MPI_Wtime();//time sleeps
  double time = t1 - t0;
  if(pid==0){
    //std::cout << np << "\t" << time << std::endl;
    std::cout<<N<<"\t"<<lifetime[0]<<"\t"<<lifetime[1]<<std::endl;
    }
  MPI_Finalize();
  return 0;
}
