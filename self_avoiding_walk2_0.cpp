#include <iostream>
#include <time.h>
#include <stdio.h>
#include <cmath>


int* random_step(int dimension, int *r);
double final_position(int dimension, int total_steps);
double average(int dimension, int total_steps, int walks);

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

  for(int ii=1; ii<total_steps; ii++){
    std::cout<<ii<<"\t"<<average(dimension, ii, walks)<<std::endl;
  }
  //std::cout<<final_position(dimension, total_steps, aux_position, position)<<std::endl;
  //MPI_Finalize();
  return 0;
}

int* random_step(int dimension, int *r)
{
  
  double step_value = 0;
  int random_number;
  int number;
  random_number = rand() % dimension;
  number=rand() % 2;
  if (number == 1)
    {
      step_value = -1;
      r[random_number]+=step_value;
    }
  else
    {
      step_value = 1;
      r[random_number]+=step_value;
    }
  
  return 0;
}

double final_position(int dimension, int total_steps)
{
  double proof=0;
  double R;
  int history [total_steps][dimension]={};
  int aux_position [dimension]={};
  int position [dimension]={};
  srand((unsigned) time(NULL));

  for(int ii=0; ii<total_steps; ++ii)
    {
      random_step(dimension,aux_position);

      for(int jj=0; jj<ii; ++jj)
	{
	  if(aux_position[0]==history[jj][0] && aux_position[1]==history[jj][1])
	    {
	      proof=1;
	      break;
	    }
	  else
	    {
	      proof=0;
	    }
	}
      //std::cout<<"proof"<<"\t"<<proof<<std::endl;//esto cout se puso con proposito de visualizar que el sistema funcionaba
      if(proof==1)//si proof=1 (es decir, se dió una posición repetida)
	{
	  proof=0;//se inicializa proof=0

	  history[ii+1][0] = aux_position[0];
	  history[ii+1][1] = aux_position[1];
	  // std::cout<<"aux position"<<"\t"<<aux_position[0]<<"\t"<<aux_position[1]<<std::endl;
	  //std::cout<<"position"<<"\t"<<position[0]<<"\t"<<position[1]<<std::endl;
	  aux_position[0]=position[0];
	  aux_position[1]=position[1];
	  continue;
	}
      else
	{

	  position[0]=aux_position[0];
	  position[1]=aux_position[1];

	  history[ii+1][0] = position[0];
	  history[ii+1][1] = position[1];

    //std::cout<<position[0]<<"\t"<<position[1]<<std::endl;
	}
    }

  R=position[0]*position[0]+position[1]*position[1];
  return R;
}

double average(int dimension, int total_steps, int walks)
{
  double prom [walks]={};
  double sum=0;
  for(int ii=0; ii<walks; ii++)
  {
    prom [ii]=final_position(dimension, total_steps);
    sum+=prom[ii];
    //std::cout<<prom[ww]<<std::endl;
  }

  double ave=sum/walks;
  return ave;
}
