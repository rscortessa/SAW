#include <iostream>
#include <random>
#include <stdio.h>
#include <cmath>
#include "snake.h"
#include <fstream>
#include "mpi.h"

void random_step(int N,snake &f) //N stands for dimension
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
  f.chequear(available_directions, N);
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
std::vector<double> promedios(jungle & snakes, int paso, int TotS) //TotS=Total snakes
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
	  prom[0]+=1.0;
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
  
  if(prom[0]>0)
    {
      prom[2] = prom[2]/TotS; // Promedio teniendo en cuenta las muertas
      prom[1] /= prom[0]; //Promedio sin tenerlas en cuenta
      prom[0]= prom[0]/TotS;    //Proporcion vivas a total P
      //   prom[3]; //will be used for finding E[x]
      //   prom[4]; //will be used for findingE[x²]
    }
  else
    {
      prom[2] = prom[2]/TotS; // Promedio teniendo en cuenta las muertas
      prom[1]=0; //Promedio sin tenerlas en cuenta
      prom[0]= 0.0;    //Proporcion vivas a total P
      //    prom[3];
      //  prom[4];
    }
  
  return prom;
}

void snake::chequear(std::vector<std::vector<int>> & available_directions, int N)
{
  int tamanho= available_directions.size();
  int counter=tamanho;
  int square=5;//tamaño de la jaula
  std::vector<std::vector<int>> hypo(tamanho,std::vector<int>(N,0)); //hypothetic vectors
  
  for(int ii=0; ii< tamanho; ii++) // this for sums the possible directions with r to later comparisson with history
    {
      std::transform(r.begin(), r.end(), available_directions[ii].begin(), hypo[ii].begin(), std::plus<int>());
    }
  
  for (int jj=History.size()-1;jj>=0;jj--){
    for (int ii=0;ii<counter;ii++){
      for(int kk=0;kk<N;kk++){
	if (History[jj]==hypo[ii] || hypo[ii].at(kk)==square || hypo[ii].at(kk)==(-square)){
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

std::vector<double> print_promedios(int t,jungle snakes,std::string a, int pid, int np, int TotS) //TotS is snakes per process
{
  std::ofstream print;
  std::vector<double> lifetime(2,0);
  print.open(a);
  for(int i=2;i<t;i++)
    {
      std::vector<double> resultados=promedios(snakes,i,TotS); //
      std::vector<double> average=resultados;
      
      
      resultados[0] = resultados[0]*TotS; //number of alive snakes PER PROCESS
      resultados[1]=resultados[1]*resultados[0]; //esto es promedio*Num_serp_vivas, es para sacar un promedio teniendo en cuenta cuantas serp vivas hay en cada proceso, y no tomar todos como iguales
      
      MPI_Reduce(&resultados[0], &average[0], 5, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
      
      average[2] /=np;
      average[1] /= average[0]; // Now average[0] is tot_snakes alive on the program
      average[0] = 1-average[0]/(TotS*np); //now it is proportion death to all
      average[3] /= TotS*np;  // this is x*prob_death(x)
      average[4] /= TotS*np;  // this is x²*prob_deat(x)
      
      if(pid==0)
	{
	  lifetime[0]+=average[3]; //lifetime will give us at the end E[x] and E[x²]
	  lifetime[1]+=average[4];
	  if (std::abs(average[0])<0.95) 
	    {
	      print<< i <<" \t "<< average[1]<<" \t "<< average[0]<<" \t "<< average[2]<< std::endl;
	    }
	  if(average[0]>=1.0){break;}
	}
    }
  print.close();
  return lifetime;
}






