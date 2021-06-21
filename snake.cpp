_#include <iostream>
//#include <time.h>
#include <random>
#include <stdio.h>
#include <cmath>
#include "snake.h"

void random_step(int dimension,snake &f)
{

  data_r dr(dimension,0);
  double step_value = 0;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(1,12);
  int random_number;
  int number;
  random_number = distrib(gen) % dimension;
  number= distrib(gen) % 2;
  step_value = -1+2*number;
  dr[random_number]+=step_value;
  f.sumar_r(dr);
}


std::vector<double> promedios(jungle & snakes, int paso)
{
  std::vector<double> prom(3,0);
  for(auto x : snakes)
    {
      walkers aux=x.obtener_History();
      if(aux.size()<paso)
      {
      }
      else
      {
        prom[0]+=1;
        for(auto y : aux[paso-1])
        {
          prom[1]+=y*y;
        }
      }
    }
  if(prom[0]!=0)
  {
    prom[2] = prom[1]/P; // Promedio teniendo en cuenta las muertas
    prom[1] /= prom[0]; //Promedio sin tenerlas en cuenta
    prom[0] /= P;    //Proporcion vivas a totalp
  }
  
  
  return prom;
}

void snake::sumar_r(data_r &dr)
{
  data_r aux =obtener_r();
  std::transform (aux.begin(), aux.end(), dr.begin(), aux.begin(), std::plus<double>());
  
  if(Chequear(aux)==true)
    {
  std::transform (r.begin(), r.end(), dr.begin(), r.begin(), std::plus<double>());
    }
  
}
bool snake::Chequear(data_r &r0)
{
  bool conocer=true;
  for(int ii=History.size()-1; ii >= 0 ; ii--)
    {
      if(History[ii]==r0)
	{
	  conocer=false;
	  break;
	}
    }
  if(conocer==true)
    {
      History.push_back(r0);
    }
  return conocer;
}

void snake::colocar_r(data_r &r0, bool accion)
{
  if(accion==true)
    {
  for(int i=0;i<N;i++)
    {
      r[i]=r0[i];
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
