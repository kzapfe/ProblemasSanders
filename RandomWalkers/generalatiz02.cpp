/*programa que genera los datos para dibujar una latiz
  3D dibujable en gnuplot */


#include <iostream>  
#include <fstream>  

using namespace std;

int main ()
{
  const int celdasmax=20;
  ofstream Celdas;
  ofstream Ocupadas;

  Celdas.open("Celdas_20.dat");
  Ocupadas.open("Ocupadas_20.dat");
  

  for(int i=0; i<celdasmax; i++){
    for(int j=0; j<celdasmax; j++){
      for(int k=0; k<celdasmax; k++){
	
	Celdas<<i<<"\t"<<j<<"\t"<<k<<"\t"<<endl;
	
      };
      Celdas<<endl;
      Celdas<<endl;
    };
  };

  int dumyx;
  int dumyy;
  int dumyz;

  for(int i=0; i<celdasmax/2; i++){
    
    dumyx=i+10;
    dumyy=i;
    dumyz=10;

    Ocupadas<<dumyx+1<<"\t"<<dumyy+1<<"\t"<<dumyz<<endl;
    Ocupadas<<dumyx<<"\t"<<dumyy+1<<"\t"<<dumyz<<endl;
    Ocupadas<<dumyx<<"\t"<<dumyy<<"\t"<<dumyz<<endl;
    Ocupadas<<dumyx+1<<"\t"<<dumyy<<"\t"<<dumyz<<endl;
    Ocupadas<<dumyx+1<<"\t"<<dumyy+1<<"\t"<<dumyz<<endl;
    
    Ocupadas<<endl;
    Ocupadas<<endl;

  };
    

  return 0;

}
