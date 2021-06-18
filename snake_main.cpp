#include <iostream>
#include "snake.cpp"
int main ()
{
  jungle snakes(P);
  for(int i=0;i<t;i++)
    {
      for(int i=0;i<P;i++)
	{
      random_step(N,snakes[i]);
        }
    }
  for(int i=2;i<t;i++)
    {
      std::cout<<i<<"\t"<<promedio_r(snakes,i)<<std::endl;
    }
  return 0;
}
