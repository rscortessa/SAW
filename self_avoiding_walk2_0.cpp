 #include "funciones.h"
#include<iostream>
int main(int argc, char **argv)
{
  /*MPI_Init(&argc, &argv);

  int pid;
  int np;

  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);*/

  std::cout.precision(14); std::cout.setf(std::ios::scientific);
  int dimension=2;
  int total_steps=std::atoi(argv[1]);
  //int history [total_steps][dimension]={};
  //int aux_position [dimension]={};
  //int position [dimension]={};
  int proof=0;
  int walks=std::atoi(argv[2]);

  // for(int ii=1; ii<total_steps; ii++){
  // std::cout<<ii<<"\t"<<average(dimension, ii, walks)<<std::endl;
}//
  std::cout<<final_position(dimension, total_steps)<<std::endl;
  //MPI_Finalize();
  return 0;
}
