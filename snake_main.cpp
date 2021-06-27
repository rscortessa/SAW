#include <iostream>
#include <vector>
#include <fstream>
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
  t=1000;
  int pid;
  int np;
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  int PP = P/np;
  jungle snakes(PP, snake(N));
  double muertes=0;

  double t0 = MPI_Wtime();
  for(int i=0;i<t;i++)
  {
   
    for(int ii=0;ii<PP;ii++)
      {
	if (snakes[ii].Life==true) random_step(N,snakes[ii]);
      }
  }
  double t1 = MPI_Wtime();
  double time1 = t1-t0;
  std::vector<double> lifetime=print_promedios(t,snakes,"snake"+std::to_string(N)+".txt",pid,np,PP);
	
  /*if(pid==0)
    {
      std::cout<<N<<"\t"<<lifetime[0]<<"\t"<<lifetime[1]<<std::endl;
    }*/
  double t2 = MPI_Wtime();
  double time2 = t2-t0;

  if(pid == 0){
    std::cout << np << "\t"  << time2 << std::endl;
    }



  MPI_Finalize();
  return 0;
}
