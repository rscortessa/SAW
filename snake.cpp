#include <iostream>
#include <random>
#include <stdio.h>
#include <cmath>
#include "snake.h"


void random_step(int dimension,snake &f)
{
      std::vector<std::vector<int>> available_directions(2*N,std::vector<int>(N,0)); 
      for(int ii=0; ii< 2*N; ii++) //for 2 dim available directions would initialy be {{-1,0},{+1,0},{0,-1},{0,+1}}
      {available_directions[ii][(int)(ii/2+0.001)]+= -1+2*(ii%2);}
  
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
  std::vector<double> prom(3,0);
  for(auto x : snakes)
    {
      if( x.DeathDate > paso)
      {
          prom[0]+=1;
          for(auto y : x.History[paso-1])
          {
            prom[1]+=y*y;
          }
          prom[2]=prom[1];
      }
      else { 
         for(auto y : x.r)
         {
           prom[2]+=y*y;
         }
      }
    }
    
  if(prom[0] != 0)
  {
    prom[2] = prom[2]/P; // Promedio teniendo en cuenta las muertas
    prom[1] /= prom[0]; //Promedio sin tenerlas en cuenta
    prom[0] /= P;    //Proporcion vivas a total P
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
