#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <iostream>
#include <time.h>
#include <stdio.h>
#include <cmath>
#include<tuple>
#include<vector>
#include<iostream>
#include<climits>
#include<algorithm>

typedef std::vector<int> data_r;
typedef std::vector<data_r> walkers;

class snake
{
  public:
  //No olvidar definir N
  data_r r;
  walkers History;
  bool Life=true;
  int DeathDate=INT_MAX;//se inicializa en el paso máximo posible para no echar la sal a la serpiente
    
  void enclosed_chequear(std::vector<std::vector<int>> & available_directions, int square, int N);
  void chequear(std::vector<std::vector<int>> & available_directions, int N);
  void colocar_r (data_r &dr, bool accion);
  inline data_r obtener_r(void) {return r;};
  inline std::vector<data_r> obtener_History(void) {return History;};
  void print_r(void);
  void print_History(void);
  
    snake(int dimen)
    {
      r=data_r(dimen,0);
      History=walkers(1,data_r(dimen,0));
    }

    snake(int dimen, std::vector<int> init_position)
    {
      r=data_r(dimen,0);
      std::transform(r.begin(),r.end(),init_position.begin(), r.begin(), std::plus<int>());
      History=walkers(1,data_r(dimen,0));
      
    }
  
};

typedef std::vector<snake> jungle;
void random_step(int dimension,snake &f, bool enclosed);
std::vector<double> promedios(jungle & snakes, int paso, int TotS);
std::vector<double> print_promedios(int t,jungle snakes,std::string a, int pid, int np, int P);

#endif
