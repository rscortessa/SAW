#include <iostream>
#include <random>
#include <stdio.h>
#include <cmath>
#include "snake.h"

void random_step(int dimension,snake &f)
{
  if(f.Life==true)
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
  
    std::vector<int> aux(3,0);
    std::transform(f.r.begin(), f.r.end(),dr.begin() , aux.begin(), std::plus<int>());
    bool check = f.chequear(aux);
    if(check==true)
    {
      f.sumar_r(dr);
    }
  else{
    random_step(dimension, f);
  }
  }
    if(f.Life==false)
    {
      f.History.push_back(f.r);
    }
}


std::vector<double> promedios(jungle & snakes, int paso)
{
  std::vector<double> prom(3,0);
  for(auto x : snakes)
    {

      if(x.History.size()>=paso)
      {
         prom[0]+=1;
        for(auto y : x.History[paso-1])
        {
          prom[1]+=y*y;
        }
      }
    }
  if(prom[0]!=0)
  {
    prom[2] = prom[2]/P; // Promedio teniendo en cuenta las muertas
    prom[1] /= prom[0]; //Promedio sin tenerlas en cuenta
    prom[0] /= P;    //Proporcion vivas a total P
  }
  
  
  return prom;
}

void snake::sumar_r(data_r &dr)
{
  std::transform (r.begin(), r.end(), dr.begin(), r.begin(), std::plus<int>());
}


bool snake::chequear(data_r &r0)
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
