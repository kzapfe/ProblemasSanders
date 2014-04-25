/*
Programa que corre dos discos en un circulo al modo
billar. Cada disco es un objeto de la clase Disco.
 */

/* version hpp: convertimos todo en un metodo
   que se encarga de toda la dinamica.
   La idea es poder usar esto como input para
   una animacion. 
*/

#include <iostream>
#include <fstream>
#include <math.h>
#include "Disco01.hpp"
#include "interaccion01.hpp"
#include "tiemposchoque01.hpp"


using namespace std;

/*
void condicionesiniciales(Disco uno, Disco dos){

  uno=new Disco(Disco uno(0.51,0.51,0.0,-0.04,0.1);
  dos=new Disco(0.5,-0.30,0.0,0.04,0.1);
  //Set up initial conditions

};
*/

float dinamicaunchoque(Disco &uno, Disco &dos){
  /*Programa que juega al billar con dos discos rigidos
    adentro de un circulo 
    version animada
    Da el tiempo de choque.
  */
    

  double tau1=0.00;
  double tau2=0.00;
  double tauchoque=0.000;
  double t; 
 
  
  if(uno.EnergiaKinetica() > 0.0){
    tau1=TiempoChoqueDiscoConcavo(uno);}
  else{tau1=7777;};

  if(dos.EnergiaKinetica() >0.0){
    tau2=TiempoChoqueDiscoConcavo(dos);}
  else{tau2=88888;};



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

      };
    
    float result=(float)t;
    
    uno.avanzarvacio(t);
    dos.avanzarvacio(t);
    
  
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
      reboteentrediscos(uno, dos);
      
    };
    
   
    return result;
};
