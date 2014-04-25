/*
Programa que corre dos discos en un circulo al modo
billar. Cada disco es un objeto de la clase Disco.
 */

/* Version Mas parecida a la version animada */

int chocador=0; //3 quiere decir los dos discos se estrellan

#include "DosDiscosDinamica.hpp"
// math esta incluido en Disco.

using namespace std;

//ULTRA GLOBAL OBJECTS

double radio=0.1;
Disco uno(0.65,0.0,-0.40,0.190,radio);
Disco dos(0.0,-0.00,0.0,0.0,radio);
const int colisionesmax=10;
//Variable auxiliar para las animaciones
// es el tiempo de choque cast en float. 
float tiempodechoque=0;

//necesitamos una variable logica
//para saber con quien chocamos



int main(){
  /*Programa que juega al billar con dos discos rigidos
    adentro de un circulo */

  ofstream puntos1, puntos2;
  
  ofstream symbolicdyn;
    
  puntos1.open("Qspace01.dat");
  puntos2.open("Qspace02.dat");
  
  symbolicdyn.open("Symbolsecuence01.dat");
  
  //Informacion de charolazo
  cout<<"Momento angular inicial"<<endl;
  cout<<uno.MomentoAngular()+dos.MomentoAngular()<<endl;
  cout<<"Energia Cinetica Total Inicial"<<endl;   
  cout<<uno.EnergiaKinetica()+dos.EnergiaKinetica()<<endl;

  puntos1<<uno.qx<<"\t"<<uno.qy<<endl;
  puntos2<<dos.qx<<"\t"<<dos.qy<<endl;
       

  for(int i=0; i<colisionesmax;i++){ 

  tiempodechoque=dinamicaunchoque(uno,dos);

  puntos1<<uno.qx<<"\t"<<uno.qy<<endl;
  puntos2<<dos.qx<<"\t"<<dos.qy<<endl;
  symbolicdyn<<chocador<<endl;
  };
    
  cout<<"Momento angular final"<<endl;
  cout<<uno.MomentoAngular()+dos.MomentoAngular()<<endl;

  cout<<"Energia Cinetica Total final"<<endl;   
  cout<<uno.EnergiaKinetica()+dos.EnergiaKinetica()<<endl;


  return 0;
 
}
