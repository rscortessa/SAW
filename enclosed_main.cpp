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
  int Square = std::atoi(argv[1]);
  int N = std::atoi(argv[2]);
  int P = std::atoi(argv[3]);
  int pid;
  int np;
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  
  int PP=P/np;
  std::vector<int> initial_position { 0,0,0 };
  jungle snakes(PP, snake(N, initial_position));

  for(int ii=0; ii< PP; ii++)
  {
      while(snakes[ii].Life==true)
      {
          random_step(N,snakes[ii],true,Square);
      } // each snake is stepped until it dies
  }

  std::vector<std::vector<int>> graves(PP); //Death possition of our snakes
  for(int ii=0; ii < PP ; ii++)
  {graves.push_back(snakes[ii].r);} //as all snakes are dead, r is our death possition

  
  
  MPI_Finalize();
    
}

