/*Programa que corre el programa de los dos discos animados
  y casi hace animaciones, pero no las hace. */

//Igual metes esto en un puto archivo con todas las variables iniciales

#include <vector>
#include "VariablesGlobales01.hpp"
#include "DosDiscosDinamica.hpp"



int main(int argc, char* args[]){

  /*por el momento sin datos en el disco duro
    Bueno, no si.*/  
  ofstream EspacioQ, EspacioRotado, VeloAngul;
  const int choquesmax=5;
  const double timestep=1.0/60.0;
  double tau, tiempo;
  double angulototal;
  double omegaefectiva;
  double angulototalmedio=0.000;
  int integrator;

  EspacioQ.open("EspacioQ.dat");
  EspacioRotado.open("EspacioRotado.dat");
  VeloAngul.open("AnguloyOmega.dat");

  //ambos discos estan inicializados en VariablesGlobales01.hpp
  
  MomAngular=uno.MomentoAngular()+dos.MomentoAngular();

  cout<<"# El momento Angular total es "<<MomAngular<<endl;

  //Primeros puntos centro discos
  EspacioQ<<uno.qx<<"\t"<<uno.qy<<"\t"
	  <<dos.qx<<"\t"<<dos.qy<<endl;
  
  EspacioRotado<<uno.qx<<"\t"<<uno.qy<<"\t"
	       <<dos.qx<<"\t"<<dos.qy<<endl;


  for(int i=0; i<choquesmax;i++){
    
    Disco falsouno, falsodos;
    double xrotado1,yrotado1;
    double xrotado2,yrotado2;
    
    //las copias empiezan en el choque anterior
    // y de ahi se mueven adelante.
    falsouno=uno;
    falsodos=dos;
    
    tiempo=dinamicaunchoque(uno,dos);
    tau=0.00;
    
    cout<<tiempo<<endl;
    
    while(tau<tiempo){
      
      tau+=timestep;
      double sinrot,cosrot;
      
      falsouno.avanzarvacio(timestep);
      falsodos.avanzarvacio(timestep);   
      angulototalmedio=(falsouno.angulo()+falsodos.angulo())/1.0;
      omegaefectiva=(falsouno.OmegaInstantanea()+falsodos.OmegaInstantanea())/1.0;
      VeloAngul<<angulototalmedio<<"\t"<<omegaefectiva<<"\t"
	       <<falsouno.angulo()<<"\t"<<falsouno.OmegaInstantanea()<<"\t"
	       <<falsodos.angulo()<<"\t"<<falsodos.OmegaInstantanea()<<endl;      
      
      sinrot=sin(angulototalmedio);
      cosrot=cos(angulototalmedio);     
      
      xrotado1=falsouno.qx*cosrot+falsouno.qy*sinrot;
      yrotado1=-falsouno.qx*sinrot+falsouno.qy*cosrot;

      xrotado2=falsodos.qx*cosrot+falsodos.qy*sinrot;
      yrotado2=-falsodos.qx*sinrot+falsodos.qy*cosrot;

      
      EspacioRotado<<xrotado1<<"\t"<<yrotado1<<"\t"
		   <<xrotado2<<"\t"<<yrotado2<<endl;

      
      
      }; 

  }; 
    
  
   
  return 0;
  
};



