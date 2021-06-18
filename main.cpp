#include <iostream>
#include "clase.h"
int main ()
{
  cuerpo caminante;
  std::vector<double> a(N);
  for(int i=0;i<N;i++)
    {
      a[i]=5;
      std::cout<<a[i]<<"\t"<<std::endl;
      
    }
  caminante.posicion_inicial(a);
  caminante.print();

  return 0;
}
