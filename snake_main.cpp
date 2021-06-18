#include <iostream>
#include "snake.cpp"
int main ()
{
  snake Caminante1;
  snake Caminante2;
  
   Caminante1.print_r();
     Caminante2.print_r();
  for(int i=0;i<1000;i++)
    {
      random_step(N,Caminante1);
      Caminante1.print_r();

    }
  return 0;
}
