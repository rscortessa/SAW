#include <iostream>
#include <vector>
#include <fstream>
#include "mpi.h"
#include "snake.h"

std::vector<double> dist_deaths (jungle & snakes, int PP); //generates and prints the probability density function of the probability of death in a given step
void fun_square (jungle & snakes, int Square, int N, int pid, int PP, int P); //generates and prints the probability density function
                                                                                             //of the probability of death in a given location

int main (int argc, char** argv)
{
  MPI_Init(&argc, &argv);
  std::cout.precision(7);
  std::cout.setf(std::ios::scientific);
  int Square = std::atoi(argv[1]); //Square determinates the size of the borders that the walker cannot cross
  int N = std::atoi(argv[2]); //Dimension
  int P = std::atoi(argv[3]); //Number of snakes
  int William = std::atoi(argv[4]); // William selects wich type of data we want to get
  int pid; //Process id
  int np; //Number of process
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  int PP=P/np; //Snakes per process
  std::vector<int> initial_position { 0,0,0 }; //Initial position if we want to changed it
  jungle snakes(PP, snake(N, initial_position));
  for(int ii=0; ii< PP; ii++)
  {
      while(snakes[ii].Life==true)
      {
          random_step(N,snakes[ii],true,Square);
      } // each snake is stepped until it dies
  }

  if (William == 1){
    std::vector<double> auxv = dist_deaths(snakes, PP); //auxv saves all the deaths per steps
    if (pid==0){
      for (int ii=0; ii<auxv.size(); ii++){
        std::cout << ii << "\t" << auxv[ii] << "\n";
      }
    }
  }
  else {
    fun_square (snakes, Square, N, pid, PP, P);
  }
  MPI_Finalize();
}

void fun_square(jungle & snakes, int Square, int N, int pid, int PP, int P){
  int RealSquare=2*Square+1;
  if(N==2)
  {
    std::vector<double> Grid(RealSquare*RealSquare,0.0); //Grid that represents points on the the square
    int origin = Square*RealSquare+Square;  //Origin of grid is set
    for(int ii=0; ii < PP; ii++)
    {
      Grid[origin + snakes[ii].r[1]*RealSquare + snakes[ii].r[0]] += 1.0; // 1 is added to Grid each time that an snake dies in that point
    }

    std::vector<double> ReciveGrid(RealSquare*RealSquare,0.0); //ReciveGrid will contain the Density of snakes that died on each point

    MPI_Reduce(&Grid[0], &ReciveGrid[0], RealSquare*RealSquare, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD); //Parallelization

    for(auto & x: ReciveGrid){ x /= P; }; //ReciveGrid is filled
    if(pid==0){ //For the master we print the cordinate and the density of snakes that died in that point
      for(int ii=0; ii < RealSquare; ii++)
      {
        for(int jj=0; jj < RealSquare; jj++)
        {
          std::cout << -Square+ii << "\t" << -Square+jj << "\t" << ReciveGrid[RealSquare*jj + ii]<<std::endl;
        }

      }
    }
  }
}

std::vector<double> dist_deaths (jungle & snakes, int PP){ 
  int Total_deaths = 0; //Total of Deaths
  double Dps = 0; //Deaths per step
  std::vector<double> All_deaths; //All_deaths is a vector that contains the number of deaths snakes in each step
  for (int paso = 0;; paso++){
    All_deaths.push_back(0); 
    for (auto x:snakes){
        if (x.DeathDate==paso){
          Dps = Dps + 1.0;
        }
    }
    Total_deaths += Dps; //Total of Deaths is filled
    All_deaths[paso]=Dps/PP;  //All_deaths is filled with the density of deaths on each step
    Dps = 0; //Dps is restarted for another iteration
    if (Total_deaths==PP){break;} //breaks to the for cicle doesn't run forever
      }
  return All_deaths;
}
