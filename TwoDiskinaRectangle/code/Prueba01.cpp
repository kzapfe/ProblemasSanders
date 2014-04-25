/*
Programa que corre dos discos en una caja.
 */

/* Version de prueba */

int chocador=-1; //armadillo indexes

#include "VariablesGlobales01.hpp"
#include "DosDiscosDinamica.hpp"
// math esta incluido en Disco.

using namespace std;


int main(){

  ofstream puntos1, puntos2, tiempos;  
  ofstream symbolicdyn;
    
  puntos1.open("qspace01.dat");
  puntos2.open("qspace02.dat");
  tiemposfree.open("TiemposdeVueloLibre01.dat");
  tiemposdisco1.open("TiemposDisco01.dat");
  tiemposchoques.open("TiemposentreChoques01.dat");

  puntos1<<uno.qx<<"\t"<<uno.qy<<endl;
  puntos2<<dos.qx<<"\t"<<dos.qy<<endl;
       
  cout<<"Energia Cinetica Total final"<<endl;   
  cout<<uno.EnergiaKinetica()+dos.EnergiaKinetica()<<endl;  


  for(int i=0; i<colisionesmax;i++){ 
 
    tiempodechoque=dinamicaunchoque(uno,dos);
    tiemposfree<<tiempodechoque<<endl;
  
 
    puntos1<<uno.qx<<"\t"<<uno.qy<<endl;
    puntos2<<dos.qx<<"\t"<<dos.qy<<endl;
    symbolicdyn<<chocador<<endl;
 

  };
   

  cout<<"Energia Cinetica Total final"<<endl;   
  cout<<uno.EnergiaKinetica()+dos.EnergiaKinetica()<<endl;


  return 0;
 
}
