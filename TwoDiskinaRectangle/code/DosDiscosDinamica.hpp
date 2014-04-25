/*
Programa que corre dos discos en un circulo al modo
billar. Cada disco es un objeto de la clase Disco.
 */

/* version hpp: convertimos todo en un metodo
   que se encarga de toda la dinamica.
   La idea es poder usar esto como input para
   una animacion. 
*/



#include "interaccion01.hpp"
#include "tiemposchoque01.hpp"


using namespace std;
using namespace arma;



double dinamicaunchoque(Disco &Uno, Disco &Dos){
  /*Programa que juega al billar con dos discos rigidos
    adentro de una caja
    
    Da el tiempo de choque.
  */
    
  
  //Tolerancia Numerica
  vec tau(5);
  double tauchoque=0.000;
  double t;
  uword choque;

  tau.fill(999);
  
  if(Uno.px==0){
    tau(0)=7777;
  }else{
    tau(0)=TiempoChoqueParedVert(Uno);}
 
  if(Uno.py==0){
    tau(1)=7999;
  }else{
    tau(1)=TiempoChoqueParedHor(Uno);}
    
  if(Dos.px==0){
    tau(2)=7877;
  }else{
    tau(2)=TiempoChoqueParedVert(Dos);}

  if(Dos.py==0){
    tau(3)=7944;
  }else{
    tau(3)=TiempoChoqueParedHor(Dos);}


  tau(4)=TiempoChoqueDosDiscos(Uno, Dos);
  if(tau(4)<=0){tau(4)=7782;}
    //};
   
  t=tau.min(choque);
  
  chocador=(int)choque;
  //cout<<"tiempo" <<t << " chocador " << chocador <<endl;


  double result=t;
    
  
  Uno.avanzarvacio(t);
  Dos.avanzarvacio(t);
  
  
  if(chocador==0){
    //Rebote disco 1
    Uno.px=-Uno.px;
    }else if(chocador==1){
    Uno.py=-Uno.py;
  }else if(chocador==2){
    Dos.px=-Dos.px;
    }else if(chocador==3){
    Dos.py=-Dos.py;
  }else{
    reboteentrediscos(Uno,Dos);   
  };
       
    return result;
};


double hopper(Disco &Uno, Disco &Dos){
  //Calcula el tiempo de "pasaje" entre las
  //cordenadas x, si eso acontece. En caso contrario, devuelve
  //un 77777.
  double result;
  double difposx;
  double veloefectiva;
  
  if( (Uno.px!=0.000) || (Dos.px!=0.000) ){
    difposx=Uno.qx-Dos.qx;
    veloefectiva=Dos.px/Dos.masa-Uno.px/Uno.masa;
    result=difposx/veloefectiva;
  }else{
    result=777777;
  }

  return result;

};

    
