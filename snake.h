#include <iostream>
#include <time.h>
#include <stdio.h>
#include <cmath>
#include<tuple>
#include<vector>
#include<iostream>
#include<algorithm>
int N=4;
int P=100;
int t=1000;
typedef std::vector<int> data_r;
typedef std::vector<data_r> walkers;

class snake
{
 private:
  //No olvidar definir N
  data_r r=data_r(N,0);
  walkers History=walkers(1,data_r(N,0));
 public:
  bool Chequear (data_r &r0);
  void colocar_r (data_r &dr, bool accion);
  inline data_r obtener_r(void) {return r;};
  inline walkers obtener_History(void) {return History;};
  void  sumar_r(data_r &dr);
  void print_r(void);
  void print_History(void);  
};
typedef std::vector<snake> jungle;
void random_stepe(int dimension,snake &f);
double promedio_r(jungle & snakes, int paso);
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
  for(int ii=0;ii<History.size();ii++)
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


