/* 
 Mapeo de los hoyos sobre la esfera de condiciones iniciales. 
 Veamos que pasa.
en la tapa superior. Parametro global es la altura del billar,
h */


#include <fstream>
#include <iostream>
#include <math.h>
#include "simplectic01.hpp"
#include "ReglasDinamicas01.hpp"



using namespace std;

int main(){
  
  const int Resolucion=2048;
  
  /*Tu sistema de Coordenadas esta centrado a la altura de un hoyo.
  Podemos pensar en que el hoyo esta rotado respecto a al eje x
  o no. Empecemos facilito.
  
  */
  
  const double pi=3.14159265359;
  const double h=3.2;
  const double qx=-0.2;
  const double qz=1.5;
  const int choquesmax=500;
  const int nivelmax=5;
  
  ofstream mapeo, histograma;

  mapeo.open("MapadeSalidas.dat");
  histograma.open("Histograma.dat");

  //masa 1, velocidades iniciales en la esfera
  double  *theta,*phi;
  
  theta=new double[Resolucion];
  phi=new double[Resolucion];
 
  //La trayectoria balistica de los polos No nos interesa
  for(int i=1; i<Resolucion;i++){
    theta[i]=-pi/2.0+(double)i/(double)Resolucion*pi;    
  };   
    
  for(int j=0; j<Resolucion;j++){
      phi[j]=-pi+((double)j/(double)Resolucion)*2.0*pi;
    };

  
  for(int i=1; i<Resolucion; i++){
    for(int j=0; j<Resolucion; j++){
	
      //Condiciones iniciales Cartesianas.
      simplectic x,y,z;	
      x.q=qx;
      y.q=0.0;
      z.q=qz;
      //Velocidad elemento de la esfera
      x.p=cos(theta[i])*cos(phi[j]);
      y.p=cos(theta[i])*sin(phi[j]);
      z.p=sin(theta[i]);

      /*  mapeo<<x.q<<"\t"<<y.q<<"\t"
	   <<z.q<<"\t"<<i<<"\t"<<j<<"\t"		
	   <<0<<endl;
      */


      for(int t=0; t<choquesmax;t++){
	double taux=0.00;
	
	taux=TiempoChoqueDiscoConcavo(x,y);        
	
	//	cout<<"Esto es tau " << taux<<endl;
	// cout<<"Esto es z.p " << z.p<<endl;

	x.avanzarvacio(taux);
	y.avanzarvacio(taux);
	z.avanzarvacio(taux);
	
	double magpos=sqrt(x.q*x.q+y.q*y.q);
	
	for (int nivel=-nivelmax; nivel< nivelmax; nivel++){
	  
	  if(((z.q> nivel*2.0*(h+1)-x.q)&&(z.q<nivel*2.0*(h+1)+x.q))|| //x.q positivo
	     ((z.q> nivel*2.0*(h+1)+x.q)&&(z.q<nivel*2.0*(h+1)-x.q))) //x.q negativo
	    {
	      mapeo<<theta[i]<<"\t"<<phi[j]<<"\t"
		<<z.q<<"\t"<<i<<"\t"<<j<<"\t"		
		  <<t<<endl;
	      t=choquesmax;
	    }
	}
		 
		 
	rebotecontrapared(x,y);	
	
       };
	
	
    };
      
    mapeo<<endl;


  };
 


    return 0;

}


