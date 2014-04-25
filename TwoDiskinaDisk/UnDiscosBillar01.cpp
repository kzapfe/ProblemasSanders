/*
Programa que corre dos discos en un circulo al modo
billar. Cada disco es un objeto de la clase Disco.
 */

#include <iostream>
#include <fstream>
#include <math.h>
#include "Disco01.hpp"
#include "tiemposchoque01.hpp"

using namespace std;

int main(){
  /*Programa que juega al billar con dos discos rigidos
    adentro de un circulo */

  Disco uno(0.1,0.0,0.2,0.4);
  Disco dos(0.6,0.6,0.3,0.0);
  Disco tres(-0.6,0.2,-0.3,0.4);
  const int colisionesmax=30;
  double tau1=0.00;
  double tau2=0.00;
  double tau3=0.00;
  ofstream puntos1, puntos2, puntos3;
  
  puntos1.open("Qspace01.dat");
  puntos2.open("Qspace02.dat");
  puntos3.open("Qspace03.dat");

  puntos1<<uno.qx<<"\t"<<uno.qy<<endl;
  puntos2<<dos.qx<<"\t"<<dos.qy<<endl;
  puntos3<<tres.qx<<"\t"<<tres.qy<<endl;
 
  cout<<"Momento angular inicial"<<endl;
  cout<<dos.MomentoAngular()<<endl;
  

  for(int i=0; i<colisionesmax;i++){
    
    tau1=TiempoChoqueDiscoConcavo(uno);
    tau2=TiempoChoqueDiscoConcavo(dos);
    tau3=TiempoChoqueDiscoConcavo(tres);


    /*   if(t<0.0){
      cout<<"Cortinas purpuras"<<endl;
      i=colisionesmax-1;
    }; 
    */
    
    uno.avanzarvacio(tau1);
    dos.avanzarvacio(tau2);
    tres.avanzarvacio(tau3);
    
    //Cuando nos estrellamos contra una pared circular
    //Y somos un circulo, el vector normal en el punto
    // de contacto es el vector radio del circulo en el punto
    // de contacto. 
    double contactox, contactoy;
    //dado que el radio es 1, es trivial.
    double normaux=0.0;
   


    //Rebote disco 1
    normaux=sqrt(uno.qx*uno.qx+uno.qy*uno.qy);
    contactox=uno.qx/normaux;
    contactoy=uno.qy/normaux;
    puntos1<<uno.qx<<"\t"<<uno.qy<<endl;     
    uno.rebotecontrapared(contactox,contactoy);
    

    //Rebote disco 2
    normaux=sqrt(dos.qx*dos.qx+dos.qy*dos.qy);
    contactox=dos.qx/normaux;
    contactoy=dos.qy/normaux;
    puntos2<<dos.qx<<"\t"<<dos.qy<<endl;     
    dos.rebotecontrapared(contactox,contactoy);
    

    //Rebote disco 3
    normaux=sqrt(tres.qx*tres.qx+tres.qy*tres.qy);
    contactox=tres.qx/normaux;
    contactoy=tres.qy/normaux;
    puntos3<<tres.qx<<"\t"<<tres.qy<<endl;     
    tres.rebotecontrapared(contactox,contactoy);
    


  };
    
  cout<<"Momento angular final"<<endl;
  cout<<dos.MomentoAngular()<<endl;

  return 0;
 
}
