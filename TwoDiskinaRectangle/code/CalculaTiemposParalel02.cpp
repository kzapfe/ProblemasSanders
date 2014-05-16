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
  
  const int Geometrias=100;   
  const int ensemble=160000; //Small test
  const gsl_rng_type *T;
  T = gsl_rng_ranlxs2;    
  
  const double radioefemin=0.002;
  //const double radioefemax=radiomax-radioefemin;
  const double radioefemax=0.248;
  
  cout<<"Dada la geometria, el radio maximo es "<<radiomax<<endl;
  cout<<" lo que nos interesa es el centro de la distribucion"<< endl;
  cout<<" Asi que trabajaremos radios entre "
      << radioefemin << " y " << radioefemax<<endl;
 
#pragma omp parallel num_threads(7)
  {
#pragma omp  for 
    //Se supone que todo lo que esta declarado dentro del for es privado.

  for(int n=1; n<Geometrias; n++){

    
    double hoptime=0.00;
    double tiempodechoque=0;
    double tiempoentrebrincos=0.0;


    gsl_rng *r ;  
    r = gsl_rng_alloc(T);
    gsl_rng_env_setup();
    gsl_rng_set(r,238107);
  

    //Ash, ya deberias de hacer una rutina que haga este
    //desmadrito de numerar archivos, carajo.
    int numeraauxiliar=1000+n;
    ofstream tiemposfirst, condini;

    std::ostringstream escupefirst, escupeelotro, escupemas;
    escupefirst<<numeraauxiliar<<"_HopTimeNew.dat"<<std::ends;         
    std::string stringfirst;
    stringfirst=escupefirst.str();
    const char *nombrefirst=stringfirst.c_str();
    
    //recicla Variables
    escupeelotro<<numeraauxiliar<<"_CondIniciales.dat"<<std::ends;         
    stringfirst=escupeelotro.str();
    const char *nombrecondini=stringfirst.c_str();


    tiemposfirst.open(nombrefirst);   
    condini.open(nombrecondini);
   
    /*
    escupemas<<numeraauxiliar<<"_Debuger.dat"<<std::ends;         
    stringfirst=escupemas.str();
    const char *nombredebuger=stringfirst.c_str();
    ofstream debuger;
    debuger.open(nombredebuger);
    */

    /*Fijate que todo el desmadre de arriba
      es solo para convertir un numero a char*/ 
    streamsize prec=tiemposfirst.precision(12);
   

    double radio=radioefemin+
      (double)n/(double)Geometrias*(radioefemax-radioefemin);
    
    cout<<"Empezamos con la geometria " << n<<endl;
    cout<<"#Radio es " << radio<<endl;
    tiemposfirst<<"# radio " << radio<<endl;
    tiemposfirst<<endl;
    
    //Si el ensamble es muy grande, no escribimos mas que las 
    //condini al disco duro. 

    for(int j=0; j<ensemble; j++){
      //Random initial conditions.

      
      Disco uno(0.0,0.25,0.0, 0.0,radio);
      Disco dos(0.0,-0.25,0.0,0.0,radio);
      
      AbsolutRandomDiscos(uno,dos,Energia,r);
           
      tiempodechoque=0.0; 
      
      condini<<uno.qx<<"\t"<<uno.qy<<"\t"<<
	dos.qx<<"\t"<<dos.qy<<"\t"<<endl;

      bool unoantesquedosoriginal;
      bool unoantesquedos;

      unoantesquedosoriginal=(uno.qx<dos.qx);
      unoantesquedos=unoantesquedosoriginal;

      bool colision=false;
      int colisiones=0;

      while ((!colision) && (colisiones<colisionesmax)){ 
      
	tiempodechoque+=dinamicaunchoqueyhopp(uno,dos);	
	colisiones++;
	unoantesquedos=(uno.qx<dos.qx);
	
	//	if((unoantesquedos != unoantesquedosoriginal) || (chocador==5))
		if((chocador==5))
		  {colision=true;}	

	/*
	debuger<<uno.qx<<"\t"<<uno.qy<<"\t"<<
	  dos.qx<<"\t"<<dos.qy<<"\t"
	       <<uno.px<<"\t"<<uno.py<<"\t"<<
	  dos.px<<"\t"<<dos.py<<"\t"<<endl;
	*/

      }

       
      tiemposfirst<<tiempodechoque<<endl;
      // debuger<<endl;      
      
    };
        
    cout<<"Ya hicimos el " <<n<<endl;
    //debuger.close();
    tiemposfirst.close();
    condini.close();
      

  };
 
    
  } //Cierra el loop paralelizable

  return 0;
}

