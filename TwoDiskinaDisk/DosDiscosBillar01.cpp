/*
Programa que corre dos discos en un circulo al modo
billar. Cada disco es un objeto de la clase Disco.
 */

#include <iostream>
#include <fstream>
#include <math.h>
#include "Disco01.hpp"
#include "interaccion01.hpp"
#include "tiemposchoque01.hpp"


using namespace std;

int main(){
  /*Programa que juega al billar con dos discos rigidos
    adentro de un circulo */

  Disco uno(0.51,0.51,0.0,-0.4,0.1);
  Disco dos(0.5,-0.30,0.0,0.4,0.1);

  const int colisionesmax=30;
  double tau1=0.00;
  double tau2=0.00;
  double tauchoque=0.000;
  double t;
  double energia;
  //necesitamos una variable logica
  //para saber con quien chocamos
  int chocador=0; //3 quiere decir los dos discos se estrellan
  

  ofstream puntos1, puntos2;
  
  puntos1.open("Qspace01.dat");
  puntos2.open("Qspace02.dat");
  

  puntos1<<uno.qx<<"\t"<<uno.qy<<endl;
  puntos2<<dos.qx<<"\t"<<dos.qy<<endl;
  
 
  cout<<"Momento angular inicial"<<endl;

  cout<<uno.MomentoAngular()+dos.MomentoAngular()<<endl;

  cout<<"Energia Cinetica Total Inicial"<<endl;
   
  cout<<uno.EnergiaKinetica()+dos.EnergiaKinetica()<<endl;
  

  for(int i=0; i<colisionesmax;i++){

    
  
    tau1=TiempoChoqueDiscoConcavo(uno);     
    tau2=TiempoChoqueDiscoConcavo(dos);

    if(chocador==3){tauchoque=7755;}else{
      tauchoque=TiempoChoqueDosDiscos(uno, dos);
      };
    


    if(tauchoque<0)tauchoque=99991;
    
    if((tauchoque>0.0)&&(tauchoque<tau1)&&(tauchoque<tau2))
      {t=tauchoque;
	chocador=3;}
    else if((tau1>0.0)&&(tau1<tauchoque)&&(tau1<tau2))
      {t=tau1;
	chocador=1;}
    else
      {t=tau2;
	chocador=2;
	//	cout<<"puuum"<<endl;
	//cout<<"chocador="<<chocador<<endl;
      };
    
	//  cout<<"Tiempo de choque"<<endl;
	//1 cout<<t<<endl;
    
    
    uno.avanzarvacio(t);
    dos.avanzarvacio(t);
    
    puntos1<<uno.qx<<"\t"<<uno.qy<<endl;     
    puntos2<<dos.qx<<"\t"<<dos.qy<<endl;     


    //Cuando nos estrellamos contra una pared circular
    //Y somos un circulo, el vector normal en el punto
    // de contacto es el vector radio del circulo en el punto
    // de contacto. 
    double contactox, contactoy;
    //dado que el radio es 1, es trivial.
    double normaux=0.0;
    
    if(chocador==1){
    //Rebote disco 1
      normaux=sqrt(uno.qx*uno.qx+uno.qy*uno.qy);
      contactox=uno.qx/normaux;
      contactoy=uno.qy/normaux;
      uno.rebotecontrapared(contactox,contactoy);
    }else if(chocador==2){
      //Rebote disco 2
      normaux=sqrt(dos.qx*dos.qx+dos.qy*dos.qy);
      contactox=dos.qx/normaux;
      contactoy=dos.qy/normaux;
      dos.rebotecontrapared(contactox,contactoy);
    }else{
      //Si lo haces directo, uno de los dos discos choca 
      //Contra el estado FUTURO del otro.
      //Asi que necesitamos una rutina simetrica.
      // o hacer trampas.
      reboteentrediscos(uno, dos);
      
    };
    /*cout<<"ouuum"<<endl;
    
    cout<<"Momento angular en i"<<endl;
    cout<<uno.MomentoAngular()+dos.MomentoAngular()<<
      "\t"<<i<<endl;
    cout<<"Energia Cinetica Total paso i"<<endl;
    cout<<uno.EnergiaKinetica()+dos.EnergiaKinetica()<<endl;
    cout<<"chocador="<<chocador<<endl;
    */

  };
    
  cout<<"Momento angular final"<<endl;
  cout<<uno.MomentoAngular()+dos.MomentoAngular()<<endl;

  cout<<"Energia Cinetica Total final"<<endl;   
  cout<<uno.EnergiaKinetica()+dos.EnergiaKinetica()<<endl;

  return 0;
 
}
