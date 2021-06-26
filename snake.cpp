#include <iostream>
#include <random>
#include <stdio.h>
#include <cmath>
#include "snake.h"
#include <fstream>
#include "mpi.h"

void random_step(int dimension,snake &f)
{
      std::vector<std::vector<int>> available_directions(2*N,std::vector<int>(N,0)); 
      for(int ii=0; ii< 2*N; ii++) //for 2 dim available directions would initialy be {{-1,0},{+1,0},{0,-1},{0,+1}}
      {
	if(ii<N)
	  {
	available_directions[ii][ii%N]+=-1;
          }
      else
	{
	available_directions[ii][ii%N]+=+1;
	}
      }
      f.chequear(available_directions);
      if(f.Life==true)
      {
        std::random_device r;
        std::mt19937 gen(r());
        std::uniform_int_distribution<> distrib(0, available_directions.size()-1);
        int rando = distrib(gen);
        std::transform (f.r.begin(), f.r.end(), available_directions[rando].begin(), f.r.begin(), std::plus<int>());
        f.History.push_back(f.r);
      }
     
}
std::vector<double> promedios(jungle & snakes, int paso)
{
  std::vector<double> prom(5,0);
  for(auto x : snakes)
    {
      if(x.DeathDate==paso)
	{
	  prom[3]+=paso;
	  prom[4]+=paso*paso;
	}
      if( x.DeathDate > paso)
      {
          prom[0]+=1;
          for(auto y : x.History[paso-1])
          {
            prom[1]+=y*y;
	    prom[2]+=y*y;
          }
      }
      else {
	int aux=x.DeathDate-1;
         for(auto y : x.History[aux])
         {
           prom[2]+=y*y;
         }
      }
    }
    
  if(prom[0]>0.001)
  {
    prom[2] = prom[2]/P; // Promedio teniendo en cuenta las muertas
    prom[1] /= prom[0]; //Promedio sin tenerlas en cuenta
    prom[0]= 1-prom[0]/P;    //Proporcion muertas a total P
    prom[3]/=P;
    prom[4]/=P;
  }
  else
    {
    prom[2] = prom[2]/P; // Promedio teniendo en cuenta las muertas
    prom[1]=0; //Promedio sin tenerlas en cuenta
    prom[0]= 1;    //Proporcion muertas a total P
    prom[3]/=P;
    prom[4]/=P;
    }
 
  return prom;
}

void snake::chequear(std::vector<std::vector<int>> & available_directions)   
{
  int tamanho= available_directions.size();
  int counter=tamanho;
  std::vector<std::vector<int>> hypo(tamanho,std::vector<int>(N,0)); //hypothetic vectors
  
  for(int ii=0; ii< tamanho; ii++) // this for sums the possible directions with r to later comparisson with history
  {
    std::transform(r.begin(), r.end(), available_directions[ii].begin(), hypo[ii].begin(), std::plus<int>());
  }
  
  for (int jj=History.size()-1;jj>=0;jj--){
		for (int ii=0;ii<counter;ii++){
			if (History[jj]==hypo[ii])
			{
			  
				available_directions.erase(available_directions.begin()+ii);
				hypo.erase(hypo.begin()+ii);
				counter--;
				if (counter<=0){
				  DeathDate=History.size();
				  Life=false;
				  break;
				  } //suave
				
			}
		}	
}
}


void snake::print_r(void)
{
  for(auto x : r)
    {
    std::cout<<x<<"\t";
    }
  std::cout<<std::endl;
}
void snake::print_History(void)
{
  for(auto x : History)
    {
      for(auto y : x)
	{
      std::cout<<y<<"\t";
        }
      std::cout<<std::endl;
    }
  std::cout<<std::endl;
 }

std::vector<double> print_promedios(int t,jungle snakes,std::string a, int pid, int np)
 {
   std::ofstream print;
   std::vector<double> lifetime(2,0);
   print.open(a);
   for(int i=2;i<t;i++)
  {
    std::vector<double> resultados=promedios(snakes,i);
    std::vector<double> average=resultados;
    MPI_Reduce(&resultados[0], &average[0], 5, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    int stop=0;
    int max=0;
    if(resultados[1]==0)
      {
	stop+=1;
      }
     MPI_Reduce(&stop, &max, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
     if(pid==0){ if (max>0 || std::abs(average[0]-np)<0.01) break;}
     if(pid==0)
      {
	 lifetime[0]+=average[3]/np;
	 lifetime[1]+=average[4]/np;
	 print<<i<<" \t "<<average[1]/np<<" \t "<<average[0]/np<<" \t "<< average[2]/np<< std::endl;
      }
  }
   print.close();
   return lifetime;
 }
