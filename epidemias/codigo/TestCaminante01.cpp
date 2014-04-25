/* Test para la clase caminantes3d y 4d. */





#include <fstream>
#include <iostream>
#include <sstream>
#include <gsl/gsl_rng.h> //Inicializa el gsl random
#include <gsl/gsl_randist.h> //las distribuciones de gsl
#include "CaminantesNoPlanos01.hpp" //Los caminantes no rebotan, esto veras como arreglarlo


int main(){

  
  const gsl_rng_type *T;
  T = gsl_rng_ranlxs2; 
  gsl_rng *r ; 

  r = gsl_rng_alloc(T);
  gsl_rng_env_setup();
  gsl_rng_set(r,238107);

  double RadioExterno=2.0;

  ofstream Celdas3d, Celdas4d;

  Celdas3d.open("CaminataSimple3D.dat");
  Celdas4d.open("CaminataSimple4D.dat");

  Caminante3D Uno;
  Caminante4D Dos;


  int tmax=5;
  

  for(int t=0; t<tmax; t++){
    
    Uno.caminar(r);
    Dos.caminar(r);
    Celdas3d<<Uno.x<<"\t"<<Uno.y<<"\t"<<Uno.z<<"\t"<<endl;
    Celdas4d<<Dos.x1<<"\t"<<Dos.x2<<"\t"<<Dos.x3<<"\t"<<Dos.x4<<endl;

  }


  Celdas3d.close();
  Celdas4d.close();
  
  ofstream Vuelos3d, Vuelos4d;

  Vuelos3d.open("VuelosSimple3D.dat");
  Vuelos4d.open("VuelosSimple4D.dat");

  Caminante3D aux3d;
  cout<<Uno.x<<"\t"<<Uno.y<<"\t"<<"\t"<<endl;

  
  for(int t=0; t<tmax; t++){

    aux3d=Uno;
    Uno.VueloBrown(r);
    if(Uno.DistanciaPlana()>RadioExterno){
      
            EnrollarEnCirculo(aux3d, Uno, RadioExterno);
     }

    Dos.VueloBrown(r);
    // Test to Standar output

    cout<<Uno.x<<"\t"<<Uno.y<<"\t"<<endl;
    Vuelos4d<<Dos.x1<<"\t"<<Dos.x2<<"\t"<<Dos.x3<<"\t"<<Dos.x4<<endl;

  }


  return 0;

}
