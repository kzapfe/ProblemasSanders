/*
Programa que corre dos discos en una caja.
 */

/* Que saca las distribuciones importantes */

int chocador=-1; //armadillo indexes

#include "VariablesGlobales01.hpp"
#include "DosDiscosDinamica.hpp"
#include "RandomConditions01.hpp"
// math esta incluido en Disco.

using namespace std;


int main(){

  ofstream puntos1, puntos2;  
  ofstream tiemposfree, tiemposdisco1, tiemposchoques,tiemposhop;
  ofstream symbolicdyn;
  double hoptime=0.00;
    

  puntos1.open("qspace01.dat");
  puntos2.open("qspace02.dat");
  tiemposfree.open("TiemposdeVueloLibre02.dat");
  tiemposdisco1.open("TiemposDisco01.dat");
  tiemposchoques.open("TiemposentreChoques01.dat");
  tiemposhop.open("HoppingTimes.dat");

  puntos1<<uno.qx<<"\t"<<uno.qy<<endl;
  puntos2<<dos.qx<<"\t"<<dos.qy<<endl;
       
  cout<<"Energia Cinetica Total final"<<endl;   
  cout<<uno.EnergiaKinetica()+dos.EnergiaKinetica()<<endl;  

  

  for(int i=0; i<colisionesmax;i++){ 
    
    tiempodechoque=dinamicaunchoque(uno,dos);
    hoptime=hopper(uno,dos);
    
    if((hoptime<tiempodechoque)&&(hoptime>0.000)){
      tiempoentrebrincos=+hoptime;
      tiemposhop<<tiempoentrebrincos<<endl;
    }else{tiempoentrebrincos=+tiempodechoque;};


    tiempoentrecolisiones=+tiempodechoque;
    tiempoentreeventosdisco1=+tiempodechoque;
    
   

    if((chocador==0)||(chocador==1)||(chocador==4)){
      tiemposdisco1<<tiempoentreeventosdisco1<<endl;
      tiempoentreeventosdisco1=0.0;
    };
    if(chocador==4){
      tiemposchoques<<tiempoentrecolisiones<<endl;
      tiempoentrecolisiones=0.0;
    };
    
       
  
    tiemposfree<<tiempodechoque<<endl;
  
 
    puntos1<<uno.qx<<"\t"<<uno.qy<<endl;
    puntos2<<dos.qx<<"\t"<<dos.qy<<endl;
    symbolicdyn<<chocador<<endl;
 

  };
   

  cout<<"Energia Cinetica Total final"<<endl;   
  cout<<uno.EnergiaKinetica()+dos.EnergiaKinetica()<<endl;


  return 0;
 
}
