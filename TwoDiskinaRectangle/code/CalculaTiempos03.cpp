/*
Programa que corre dos discos en una caja.
 */

/* Que saca las distribuciones importantes */
/* Dado que es muy idiota tratar de esperar a que se "ergodice todo"
   vamos a usar un ensemble de condiciones iniciales */
// estos dos son los de gsl

// Version 03, lee argumentos del command line
#include <iostream> 
#include <cstdlib> 
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

int chocador=-1; //armadillo indexes


#include "VariablesGlobales01.hpp"
#include "DosDiscosDinamica.hpp"
#include "RandomConditions01.hpp"
// math esta incluido en Disco.

using namespace std;


int main(int argc, char* argv[]){
  //En esta version la posicion de los puntos nos vale comino
  //El programa lee argv[1] y lo interpeta como int. Luego
  // lo dividimos entre 1000 y nos da la expansion del radio,
  // los valores aceptados son entre 1 y 2499.

  gsl_rng *r = gsl_rng_alloc(gsl_rng_mt19937);

  ofstream tiemposfree,tiemposhop;
  double hoptime=0.00;
  int ensemble=1000;
  double Energia=1.00;
  
  char* FullNameTiemposLibres, FullNameTiemposHopp
  
  tiemposfree.open(FullNameTiemposLibres);
  tiemposhop.open(FullNameTiemposHopp);


  //Si el ensamble es muy grande, no escribimos mas que las 
  //condini al disco duro. 

  for(int j=0; j<ensemble; j++){
    //Random initial conditions.

    RandomizaDiscos(uno,dos,Energia,r);
  
    puntos1<<" "<<endl;
    puntos2<<" "<<endl;
    
    puntos1<<uno.qx<<"\t"<<uno.qy<<endl;
    puntos2<<dos.qx<<"\t"<<dos.qy<<endl;

    tiempodechoque=0;
    tiempoentrecolisiones=0.0;
    tiempoentreeventosdisco1=0.0;
    tiempoentrebrincos=0.0;
    
    //Line Breaker
    
    

    for(int i=0; i<colisionesmax;i++){ 
      
      tiempodechoque=dinamicaunchoque(uno,dos);
      hoptime=hopper(uno,dos);
      
      if((hoptime<tiempodechoque)&&(hoptime>0.000)){
	
	tiempoentrebrincos+=hoptime;
	tiemposhop<<tiempoentrebrincos<<endl;

	tiempoentrebrincos=0.00;

      }else{
	tiempoentrebrincos+=tiempodechoque;

      }

      

      tiempoentrecolisiones+=tiempodechoque;
      tiempoentreeventosdisco1+=tiempodechoque;
       
      
      if((chocador==0)||(chocador==1)||(chocador==4)){
	tiemposdisco1<<tiempoentreeventosdisco1<<endl;
	tiempoentreeventosdisco1=0.0;
      };
      if(chocador==4){
	tiemposchoques<<tiempoentrecolisiones<<endl;
	tiempoentrecolisiones=0.0;
      };
      
       
      tiemposfree<<tiempodechoque<<endl;
            
      //   symbolicdyn<<chocador<<endl;
      
      
    };
    
    
    // cout<<"Energia Cinetica Total final del par numero "<< j <<endl;   
    // cout<<uno.EnergiaKinetica()+dos.EnergiaKinetica()<<endl;
    cout<<j<<endl;


  };
  
  return 0;
  
}
