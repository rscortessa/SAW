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


  int RealSquare=2*Square+1;
  if(N==2)
  {
      std::vector<double> Grid(RealSquare*RealSquare,0.0); //GRid that represents ponts on the the square

      // grid(0) is the left lower corner //grid[2*(Square+1)*2-1] is the upper right corner
      //grid[Square*(2*Square+1)+Square-1] Represents the origin

      int origin = Square*RealSquare+Square;
      for(int ii=0; ii < PP; ii++)
      {
          Grid[origin + snakes[ii].r[1]*RealSquare + snakes[ii].r[0]] += 1.0;
      }

      std::vector<double> ReciveGrid(RealSquare*RealSquare,0.0);

      MPI_Reduce(&Grid[0], &ReciveGrid[0], RealSquare*RealSquare, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

      for(auto & x: ReciveGrid){ x /= P; };
      
      if(pid==0)
      {
          for(int ii=0; ii < RealSquare; ii++)
          {
              for(int jj=0; jj < RealSquare; jj++)
              {
                  std::cout << -Square+ii << "\t" << -Square+jj << "\t" << ReciveGrid[RealSquare*jj + ii]<<std::endl;
              }

          }
      }
  }


  MPI_Finalize();
}


//0 0 0 1 0 0 0
//0 0 0 1 0 0 0
//0 0 0 1 0 0 0
//1 1 1 1 1 1 1
//0 0 0 1 0 0 0
//0 0 0 1 0 0 0
//0 0 0 1 0 0 0
