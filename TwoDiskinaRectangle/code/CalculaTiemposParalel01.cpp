/*
Programa que corre dos discos en una caja.
 */

/* Que saca las distribuciones importantes */
/* Dado que es muy idiota tratar de esperar a que se "ergodice todo"
   vamos a usar un ensemble de condiciones iniciales */
// estos dos son los de gsl
// Version Paralela

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

int chocador=-1; //armadillo indexes


#include "VariablesGlobalesParalel01.hpp"
#include "DosDiscosDinamica.hpp"
#include "RandomConditions01.hpp"

// math esta incluido en Disco.

using namespace std;


int main(){

  //FreeTime escribe TODOS los chocques, no tenemos tanto disco duro...
  //bajale al ensemble, subele a las colisiones
  
  const int Geometrias=100;
  const int ensemble=16000;
   
  const gsl_rng_type *T;
  T = gsl_rng_ranlxs2;    
    
  const double radioefemin=0.001;
  const double radioefemax=radiomax-radioefemin;

  
#pragma omp parallel num_threads(7)
  {
#pragma omp  for 
    //Se supone que todo lo que esta declarado dentro del for es privado.
    
    //Para HopTimes, no tiene sentido buscar arriba de r=0.25, 
    // tu programa no es robusto, revisa eso, algo falla.
    //    for(int n=85; n<Geometrias; n++){
    for(int n=1; n<86; n++){
          
    double hoptime=0.00;
    double tiempodechoque=0;
    double tiempoentrebrincos=0.0;
    const double toleranciachoques=0.000000001;

    gsl_rng *r ;  
    r = gsl_rng_alloc(T);
    gsl_rng_env_setup();
    gsl_rng_set(r,238109);
  

    int numeraauxiliar=1000+n;
    ofstream tiemposfree, tiemposhop;

    std::ostringstream escupefree;
    std::ostringstream escupehop;
      
    escupefree<<numeraauxiliar<<"_FreeTimeHueco.darn"<<std::ends;
    escupehop<<numeraauxiliar<<"_HopTimeStronger.dat"<<std::ends;
      
    std::string stringfree;
    std::string stringhop;

    stringfree=escupefree.str();
    stringhop=escupehop.str();
      
    const char *nombrefree=stringfree.c_str();
    const char *nombrehop=stringhop.c_str();
    
    /*Fijate que todo el desmadre de arriba
      es solo para convertir un numero a char*/ 
    streamsize prec=tiemposfree.precision(16);
    
    tiemposfree.open(nombrefree);   
    tiemposhop.open(nombrehop);

    double radio=radioefemin+
      (double)n/(double)Geometrias*(radioefemax-radioefemin);
    double distancia;


    cout<<"Estoy comenzando el proceso "<< n << " con radio="<<radio<<endl; 
    
    //Encabezados utiles porfavor zoquete
    tiemposfree<<"radio="<<radio<<endl;
    tiemposfree<<"Energia="<<Energia<<endl;
    tiemposfree<<endl;
    
    tiemposhop<<"radio="<<radio<<endl;
    tiemposhop<<"Energia="<<Energia<<endl;
    tiemposhop<<endl;
    


    for(int j=0; j<ensemble; j++){
      //Random initial conditions.


      Disco uno(0.0,0.25,0.0, 0.0,radio);
      Disco dos(0.0,-0.25,0.0,0.0,radio);
      bool hopeado=false;
      
      AbsolutRandomDiscos(uno,dos,Energia,r);
     
      tiempodechoque=0.0; 
      tiempoentrebrincos=0.0;
      hoptime=0;

    //Line Breaker
        
      for(int i=0; i<colisionesmax;i++){ 
	
	hoptime=-1.0;
	tiempodechoque=dinamicaunchoque(uno,dos);	
	hoptime=hopper(uno,dos);
	
	if((hoptime<tiempodechoque)&&(hoptime>0.000)){	  
	  hopeado=true;
	  tiempoentrebrincos+=hoptime;
	  tiemposhop<<tiempoentrebrincos<<endl;
	  tiempoentrebrincos=0.00;
       
	}else{
	  tiempoentrebrincos+=tiempodechoque;
	  
	}

	/* DEBUG INFO
	distancia=sqrt((uno.qx-dos.qx)*(uno.qx-dos.qx)+
		       (uno.qy-dos.qy)*(uno.qy-dos.qy));
	//Numerical Mistake?
	//if(tiempodechoque>toleranciachoques){
		tiemposfree<<uno.qx<<"\t"<<uno.qy<<"\t"<<
	  dos.qx<<"\t"<<dos.qy<<"\t"<<
	  tiempodechoque<<"\t"<<chocador<<"\t"<<
	  uno.EnergiaKinetica()+dos.EnergiaKinetica()
		   <<"\t"<<distancia<<
		   endl;*/
        //}

	//tiemposfree<<tiempodechoque<<endl;
      
      };
       
      if(!hopeado){
	// tiemposhop<<"# nunca brinque yo de lugar"<<endl;	
	//     tiemposhop<<tiempomax<<endl;
	tiemposhop<<endl;
      };
  

      //      tiemposfree<<endl;

    }
    
    

    cout<<"He terminado con el proceso "<<n<<endl;
    } //Cierra el loop paralelizable
    
  } //Cierra el pragma de openmp
 
  return 0;
  
}
