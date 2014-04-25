/* Test para la clase caminantes3d y 4d. */
/*Con Celdas */




#include <fstream>
#include <iostream>
#include <sstream>
#include <gsl/gsl_rng.h> //Inicializa el gsl random
#include <gsl/gsl_randist.h> //las distribuciones de gsl
#include "CaminantesNoPlanos01.hpp" //Los caminantes no rebotan, esto veras como arreglarlo
#include "RandomInConus01.hpp" //Los caminantes no rebotan, esto veras como arreglarlo

using namespace std;

int main(){

  
  const gsl_rng_type *T;
  T = gsl_rng_ranlxs2; 
  

  const int Geometrias=100;
  const int tmax=7000000;
  const int ensamble=66666;
  
  

#pragma omp parallel num_threads(4)
    {
#pragma omp  for 
      
      for(int n=1; n<Geometrias; n++){
      
      gsl_rng *r ; 

      r = gsl_rng_alloc(T);
      gsl_rng_env_setup();
      gsl_rng_set(r,238107);

      double rext, rint;
      rext=1.0;
      rint=(double)n/(double)Geometrias*rext;

      cout<<"El radio es " << rint<<endl;

      ofstream CondicionesIniciales, Caminatas, Tiempos;
      int numeraauxiliar=1000+n;    	 
      ostringstream escupefirst, escupeelotro, escupemas;
      /* 
      escupefirst<<numeraauxiliar<<"_TimeCilCeldas3d.dat"<<std::ends;  
      std::string stringfirst;
      stringfirst=escupefirst.str();
      const char *nombrefirst=stringfirst.c_str();
      Tiempos.open(nombrefirst);
      */

      //recicla Variables
      escupeelotro<<numeraauxiliar<<"_CondInicialesCono3d.dat"<<std::ends;      
      std::string stringfirst;
      stringfirst=escupeelotro.str();
      const char *nombrecondini=stringfirst.c_str();
      CondicionesIniciales.open(nombrecondini);  

      /*
      escupemas<<numeraauxiliar<<"_CaminataCilindro3d.dat"<<std::ends;         
      stringfirst=escupemas.str();
      const char *nombrecaminata=stringfirst.c_str();      
      Caminatas.open(nombrecaminata);
      */
      //streamsize prec=Tiempos.precision(12);
	
      Tiempos<<"#Radio="<<rint<<endl;
      Tiempos<<endl;

      
      Caminante3D Uno,aux3d;
      
      for(int j=0; j<ensamble; j++){
	Uno=RandomInConus3D(rint, rext, r);
	CondicionesIniciales<<Uno.x<<"\t"<<Uno.y<<"\t"<<Uno.z<<endl;
	//Caminatas<<Uno.x<<"\t"<<Uno.y<<"\t"<<Uno.z<<"\t"<<endl;

	/*	for(int t=0; t<tmax; t++){
	  aux3d=Uno;
	  Uno.caminar(r);
	  
	  if(Uno.DistanciaPlana()>rext){	
	    Uno=aux3d;
	  }
	  if(Uno.DistanciaPlana()<rint){
	    //  Caminatas<<Uno.x<<"\t"<<Uno.y<<"\t"<<Uno.z<<"\t"<<endl;
	    //Caminatas<<endl;
	    Tiempos<<t+1<<endl;
	    break;
	  }
 
	  //Caminatas<<Uno.x<<"\t"<<Uno.y<<"\t"<<Uno.z<<"\t"<<endl;
	  
	}
	//Caminatas<<endl;
	*/		
      }
	

	//Tiempos.close();
	//Caminatas.close();
      CondicionesIniciales.close();
      
      }//cierra el loop de las geometrias
      
    
    }//Cierra el pragma parallel num threads

  
    return 0;

}
