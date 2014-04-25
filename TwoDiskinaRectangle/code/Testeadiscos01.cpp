/*
Programa que corre dos discos en un circulo al modo
billar. Cada disco es un objeto de la clase Disco.
 */

#include <iostream>
#include "Disco01.hpp"


using namespace std;

int main(){
  /*Programa que juega al billar con dos discos rigidos
    adentro de un circulo */

  Disco uno;
  Disco dos(0.1,0.1,0.3,0.4);
  Disco tres(0.0,0.1,0.3,0.4,0.3);
  Disco cuatro(0.0,0.1,0.3,0.4,0.3,2.0);

 
  cout<<uno.radio<<endl;
  cout<<dos.qx<<endl;
  cout<<tres.masa<<endl;
  cout<<cuatro.masa<<endl;
  
  double angmom;
  angmom=tres.MomentoAngular();

  cout<<angmom<<endl;


  double angmomrespectoaotro;
  
  angmomrespectoaotro=tres.MomentoAngular(dos.qx,dos.qy);

  cout<<angmomrespectoaotro<<endl;
 
}
