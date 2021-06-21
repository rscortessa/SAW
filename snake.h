#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <iostream>
#include <time.h>
#include <stdio.h>
#include <cmath>
#include<tuple>
#include<vector>
#include<iostream>
#include<algorithm>

typedef std::vector<int> data_r;
typedef std::vector<data_r> walkers;

extern int N,P,t;

class snake
{
  public:
  //No olvidar definir N
  data_r r=data_r(N,0);
  walkers History=walkers(1,data_r(N,0));
  bool Life=true;
  int DeathStep=t; //se inicializa en el paso máximo para no echar la sal a la serpiente
  
  bool chequear (data_r &r0);
  void colocar_r (data_r &dr, bool accion);
  inline data_r obtener_r(void) {return r;};
  inline std::vector<data_r> obtener_History(void) {return History;};
  void  sumar_r(data_r &dr);
  void print_r(void);
  void print_History(void);  
};

typedef std::vector<snake> jungle;
void random_step(int dimension,snake &f);
std::vector<double> promedios(jungle & snakes, int paso);



#endif
