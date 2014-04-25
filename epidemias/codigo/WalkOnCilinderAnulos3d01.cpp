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

  ofstream CondicionesIniciales, Caminatas, Tiempos;

  CondicionesIniciales.open("CaminantesStart.dat");
  Caminatas.open("CaminataCilindroAnular3d01.dat");
  Tiempos.open("TiemposCilindroAnular3d01.dat");

  Caminante3D Uno,aux3d;


  int tmax=5000;
  int ensamble=66666;
  double rext, rint;
  rext=1.0;
  rint=0.5;

  for(int j=0; j<ensamble; j++){
    Uno=RandomInAnulus(rint, rext, r);
    CondicionesIniciales<<Uno.x<<"\t"<<Uno.y<<"\t"<<Uno.z<<endl;
    
 
    for(int t=0; t<tmax; t++){
      aux3d=Uno;
      Uno.VueloBrown(r);
    
      if(Uno.DistanciaPlana()>rext){	
	EnrollarEnCirculo(aux3d, Uno, rext);
      }
      if(Uno.DistanciaPlana()<rint){
	Caminatas<<Uno.x<<"\t"<<Uno.y<<"\t"<<Uno.z<<"\t"<<endl;
	Caminatas<<endl;
	Tiempos<<t+1<<endl;
	break;
      }
 
      Caminatas<<Uno.x<<"\t"<<Uno.y<<"\t"<<Uno.z<<"\t"<<endl;
    
    }
    Caminatas<<endl;
    

  }

  /*

 

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
  */
  
  return 0;

}
