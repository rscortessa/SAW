#include <iostream>
#include "snake.cpp"
int main ()
{
  jungle snakes(P);
  for(int i=0;i<t;i++)
    {
      for(int ii=0;ii<P;ii++)
	{
      random_step(N,snakes[ii]);
        }
    }
  for(int i=2;i<t;i++)
    {
      std::cout<<i<<"\t"<<promedio_r(snakes,i)<<std::endl;
    }
  return 0;
}
