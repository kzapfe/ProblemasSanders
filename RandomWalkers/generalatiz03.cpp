/*programa que genera los datos para dibujar una latiz
  3D dibujable en gnuplot */


#include <iostream>  
#include <fstream>  

using namespace std;

int main ()
{
  const int celdasmax=15;
  ofstream Celdas;
  ofstream Ocupadas;

  Celdas.open("Celdas_15.dat");
  Ocupadas.open("Ocupadas_15.dat");
  

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
    
    dumyx=i+8;
    dumyy=i;
    dumyz=8;

    //Okey, esto se va a ver horrible pero no se te ocurre otra forma.
    //parte de abajo
    Ocupadas<<dumyx+1<<"\t"<<dumyy+1<<"\t"<<dumyz<<endl;
    Ocupadas<<dumyx<<"\t"<<dumyy+1<<"\t"<<dumyz<<endl;
    Ocupadas<<dumyx<<"\t"<<dumyy<<"\t"<<dumyz<<endl;
    Ocupadas<<dumyx+1<<"\t"<<dumyy<<"\t"<<dumyz<<endl;
    Ocupadas<<dumyx+1<<"\t"<<dumyy+1<<"\t"<<dumyz<<endl;
    //subimos
    Ocupadas<<dumyx+1<<"\t"<<dumyy+1<<"\t"<<dumyz+1<<endl;
    Ocupadas<<dumyx<<"\t"<<dumyy+1<<"\t"<<dumyz+1<<endl;
    //bajamos y volemos a subir
    Ocupadas<<dumyx<<"\t"<<dumyy+1<<"\t"<<dumyz<<endl; 
    Ocupadas<<dumyx<<"\t"<<dumyy+1<<"\t"<<dumyz+1<<endl; 
    Ocupadas<<dumyx<<"\t"<<dumyy<<"\t"<<dumyz+1<<endl;
    Ocupadas<<dumyx<<"\t"<<dumyy<<"\t"<<dumyz<<endl;
    Ocupadas<<dumyx<<"\t"<<dumyy<<"\t"<<dumyz+1<<endl;
    Ocupadas<<dumyx+1<<"\t"<<dumyy<<"\t"<<dumyz+1<<endl;
    Ocupadas<<dumyx+1<<"\t"<<dumyy<<"\t"<<dumyz<<endl;
    Ocupadas<<dumyx+1<<"\t"<<dumyy<<"\t"<<dumyz+1<<endl;
    Ocupadas<<dumyx+1<<"\t"<<dumyy+1<<"\t"<<dumyz+1<<endl; 

    Ocupadas<<endl;
    Ocupadas<<endl;

  };
    

  return 0;

}
