/*programa que genera los datos para dibujar una latiz
  3D dibujable en gnuplot */


#include <iostream>  
#include <fstream>  

using namespace std;

int main ()
{
  const int celdasmax=8;
  ofstream Celdas;

  Celdas.open("Celdas_4.dat");

  for(int i=0; i<celdasmax; i++){
    for(int j=0; j<celdasmax; j++){
      for(int k=0; k<celdasmax; k++){
	
	Celdas<<i<<"\t"<<j<<"\t"<<k<<"\t"<<endl;
	
      };
      Celdas<<endl;
      Celdas<<endl;
    };
  };

 
  return 0;

}
