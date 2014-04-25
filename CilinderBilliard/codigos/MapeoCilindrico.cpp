/*Este programa mapea el disco en el disco de la siguiente forma.
Hace de cuenta que el disco es la tapa inferior de un cilindro
 y queremos ver en donde  mapea las particulas la dinamica 
en la tapa superior. Parametro global es la altura del billar,
h */
#include <math.h>
#include "simplectic01.hpp"
#include "ReglasDinamicas01.hpp"
#include <fstream>
#include <iostream>


using namespace std;

int main(){
  
  const int muestreo=50;
  const double h=0.200;
  const double l=0.2;
  const int choquesmax=10;
  double rhomin=l; // en realidad es l/|y.p|, pero aqui eso es lo mismo que 1. 

  ofstream mapeoint, mapeoext;

  mapeoint.open("mapeointerior.dat");
  mapeoext.open("mapeoexterior.dat");

  //masa igual a 1, coordenadas cartesianas.
  simplectic  *x,*y;
  
  //Sea la velocidad al cuadrado = 2.
  //y asignamos z.p^2=1.
  //simplectic z(0.0, 1.0);
  
  //Simpler math, please.
  x=new simplectic[muestreo];
  y=new simplectic[muestreo];
  
  cout<<rhomin<<endl;

  //populate line
  for(int i=0; i<muestreo;i++){
    x[i+1].q=rhomin+(1.0-rhomin)*(double)i/(double)muestreo;
    y[i+1].p=l/x[i+1].q;
    x[i+1].p=sqrt(1.0-y[i+1].p);
    mapeoext<<x[i+1].q<<"\t"<<y[i+1].q<<"\t"
	    <<x[i+1].p<<"\t"<<y[i+1].p<<"\t"
	    <<i+1<<"\t"<<0<<"\n";
  };
      
  mapeoext<<endl;
  
  double taux=0.00;
  //dado que pz es 1, h=tiempo de subir.

  for(int t=0; t<choquesmax;t++){

  for(int i=1; i<=muestreo; i++){

    taux=TiempoChoqueDiscoConcavo(x[i],y[i]);
        
    if(h<taux){
      x[i].avanzarvacio(h);
      y[i].avanzarvacio(h);
    }else{
      //avanzamos hasta el punto de choque
      x[i].avanzarvacio(taux);
      y[i].avanzarvacio(taux);
      //calculamos la normal y la tangente ahi.
      rebotecontrapared(x[i],y[i]);
      /*    mapeoext<<x[i].q<<"\t"<<y[i].q<<"\t"
	      <<x[i].p<<"\t"<<y[i].p<<"\t"
	      <<i<<"\t"<<0.5<<"\n";
      */
      x[i].avanzarvacio(h-taux);
      y[i].avanzarvacio(h-taux);
    };

      mapeoext<<x[i].q<<"\t"<<y[i].q<<"\t"
	      <<x[i].p<<"\t"<<y[i].p<<"\t"
	      <<i<<"\t"<<1<<"\n";
      
  };
  
  mapeoext<<endl;
  

  };
 


  return 0;

}


