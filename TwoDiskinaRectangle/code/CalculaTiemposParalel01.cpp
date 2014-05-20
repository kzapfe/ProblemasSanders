/*
Programa que corre dos discos en una caja.
 */

/* Que saca las distribuciones importantes */
/* Dado que es muy idiota tratar de esperar a que se "ergodice todo"
   vamos a usar un ensemble de condiciones iniciales */
// estos dos son los de gsl
// Version Paralela

/* Este codigo, marcado con la señal 01, corre VARIAS vez sobre el mismo
elemento del ensamble, calculando realmente Un RETURN TIME, no un
FIRST PASSAGE TIME. Curiosamente, este es el que da el limite correcto,
pero el comportamiento no es tan del todo correcto. Tiene sus bemoles,
especificamente esa Pancita caida respecto a la curva teorica.
 */

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>


#include "VariablesGlobalesParalel01.hpp"
#include "DosDiscosDinamica.hpp"
#include "RandomConditions01.hpp"

// math esta incluido en Disco.

using namespace std;


int main(){

  //FreeTime escribe TODOS los chocques, no tenemos tanto disco duro...
  //bajale al ensemble, subele a las colisiones
  
  const int Geometrias=100;
  const int ensemble=4000;
   
  const gsl_rng_type *T;
  T = gsl_rng_ranlxs2;    
    
  const double radioefemin=0.0001;
  //  const double radioefemax=radiomax-radioefemin;
  const double radioefemax=0.2499;
  
#pragma omp parallel num_threads(7)
  {
#pragma omp  for schedule(dynamic)
    //Se supone que todo lo que esta declarado dentro del for es privado.
    
    //Para HopTimes, no tiene sentido buscar arriba de r=0.25, 
    // tu programa no es robusto, revisa eso, algo falla.
    //    for(int n=85; n<Geometrias; n++){
    for(int n=1; n<Geometrias; n++){
          
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

    std::ostringstream escupehop;
          
    escupehop<<numeraauxiliar<<"_HopTimeErgodic01.dat"<<std::ends;
      
    std::string stringhop;

    stringhop=escupehop.str();
      
    const char *nombrehop=stringhop.c_str();
    
    /*Fijate que todo el desmadre de arriba
      es solo para convertir un numero a char*/ 
    streamsize prec=tiemposhop.precision(16);
    
    tiemposhop.open(nombrehop);

    double radio=radioefemin+
      (double)n/(double)Geometrias*(radioefemax-radioefemin);
    double distancia;


    cout<<"Estoy comenzando el proceso "<< n << " con radio="<<radio<<endl;           
    tiemposhop<<"radio "<<radio<<endl;
    tiemposhop<<"Energia "<<Energia<<endl;
    tiemposhop<<endl;
    


    for(int j=0; j<ensemble; j++){
      //Random initial conditions.

      Disco uno(0.0,0.25,0.0, 0.0,radio);
      Disco dos(0.0,-0.25,0.0,0.0,radio);
      bool hopeado=false;
      int chocador=-1; //armadillo indexes
      
      AbsolutRandomDiscos(uno,dos,Energia,r);
     
      tiempodechoque=0.0; 
      tiempoentrebrincos=0.0;
      hoptime=0;
     
      //Dado que estamos esperando un RETURN TIME
      //Primero tenemos que ergodicidar Sobre condiciones EN EL HOP-Posture
      //EXACTAMENTE
      int cuentachoques=0;
      int choque=-1;	

      while((!hopeado)&&(cuentachoques<colisionesmax)){	
	tiempodechoque=dinamicaunchoqueyhopp(uno,dos,choque);	
	cuentachoques++;
	if(choque==5)hopeado=true;
      }
        
      if(hopeado){
	hopeado==false;
	hoptime=-1.0;
	for(int i=0; i<colisionesmax;i++){ 
	  	  
	  tiempodechoque=dinamicaunchoque(uno,dos);	
	  hoptime=hopper(uno,dos);
	
	  if((hoptime<=tiempodechoque)&&(hoptime>0.0000)){	  
	    hopeado=true;
	    tiempoentrebrincos+=hoptime;
	    tiemposhop<<tiempoentrebrincos<<endl;
	    tiempoentrebrincos=0.00;
	  
	  }else{
	    tiempoentrebrincos+=tiempodechoque;
	    
	  }

	}//Cierra las repeticiones sobre la dinamica
      
      }else{
	//Nunca paso nada, no escribas NADA
      };
     

    }
       
    cout<<"He terminado con el proceso "<<n<<endl;
    } //Cierra el loop paralelizable
    
  } //Cierra el pragma de openmp
 
  return 0;
  
}
