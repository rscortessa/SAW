#include <iostream>
#include <time.h>

int random_step();

int main(int argc, char **argv)
{
  int dimension=4;
  int total_steps=10;
  int history [total_steps][dimension]={};
  int aux_position [dimension]={};
  int position [dimension]={};
  int proof=0;
  
  srand((unsigned) time(NULL));
  for(int ii=0; ii<total_steps; ++ii)
    {
      aux_position[0] = aux_position[0]+random_step();
      aux_position[1] = aux_position[1]+random_step();
      
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
      std::cout<<"proof"<<"\t"<<proof<<std::endl;
      if(proof==1)
	{
	  proof=0;
	  
	  history[ii+1][0] = position[0];
	  history[ii+1][1] = position[1];
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
	  //position[2] = position[2]+random_step();

	  //std::cout<<"aux position"<<"\t"<<aux_position[0]<<"\t"<<aux_position[1]<<std::endl;
	  std::cout<<"position"<<"\t"<<position[0]<<"\t"<<position[1]<<std::endl;
	}
    }

  std::cout<<"--------------------------------------"<<std::endl;
  
  for(int ii=0; ii<total_steps+1; ++ii)
    {
      for(int jj=0; jj<dimension; ++jj)
	{
	  std::cout<<history[ii][jj]<<"\t";
	}
      std::cout<<std::endl;
    }
  return 0;
}

int random_step()
{
  double step_value = 0;
  int ii;
  double random_number;
  random_number = rand() % 2;
  if (random_number == 1)
    {
      step_value = -1;
    }
  else
    {
      step_value = 1;
    }
  
  return step_value;
}
