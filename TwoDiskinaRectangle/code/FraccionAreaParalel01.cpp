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
//El include de arriba jala la mayor parte de include que queremos.
#include "RandomPosition01.hpp"

// math esta incluido en Disco.

using namespace std;


int main(){

  //parametros geometricos y  numericos
  const int Geometrias=100;   
  const int ensemble=32000000;
  const double epsilon=0.001;

  //parametros del 
  const gsl_rng_type *T;
  T = gsl_rng_ranlxs2;    
    
  const double radioefemin=0.001;
  const double radioefemax=radiomax-radioefemin;
  
  cout<<"Dada la geometria, el radio maximo es "<<radiomax<<endl;
  cout<<" lo que nos interesa es el centro de la distribucion"<< endl;
  cout<<" Asi que trabajaremos radios entre "
      << radioefemin << " y " << radioefemax<<endl;
 
#pragma omp parallel num_threads(7)
  {
#pragma omp  for 
    //Se supone que todo lo que esta declarado dentro del for es privado.

  for(int n=1; n<Geometrias; n++){


    gsl_rng *r ;  
    r = gsl_rng_alloc(T);
    gsl_rng_env_setup();
    gsl_rng_set(r,238107);
  
    //Ash, ya deberias de hacer una rutina que haga este
    //desmadrito de numerar archivos, carajo.
    int numeraauxiliar=1000+n;
    ofstream condini;

    std::ostringstream escupeelotro;
    std::string stringfirst;

   
    //recicla Variables
    escupeelotro<<numeraauxiliar<<"_AraTuta001.dat"<<std::ends;         
    stringfirst=escupeelotro.str();
    const char *nombrecondini=stringfirst.c_str();
    
    condini.open(nombrecondini);
    condini.precision(15);

    /*Fijate que todo el desmadre de arriba
      es solo para convertir un numero a char*/ 
    streamsize prec=condini.precision(12);
   
    double radio=radioefemin+
      (double)n/(double)Geometrias*(radioefemax-radioefemin);
    
    cout<<"Empezamos con la geometria " << n<<endl;
    cout<<"El radio es " << radio<<endl;
    
    //Es mas conveniente si contamos los
    //PROHIBIDOS, asi no tenemos que preocuparnos
    //por rescalar el cubo disponible.
    int cuentamalos=0;

    for(int j=0; j<ensemble; j++){
      //Random initial conditions.

      Disco uno(0.0,0.25,0.0, 0.0,radio);
      Disco dos(0.0,-0.25,0.0,0.0,radio);
      
      RandomPosition(uno,dos, widthmedia, heightmedia, r);
      
      double dist;
      dist=sqrt((uno.qx-dos.qx)*(uno.qx-dos.qx)+
		    (uno.qy-dos.qy)*(uno.qy-dos.qy));

      //it has to be OUTSIDE THE CILINDER, and in the hopping position
      if((dist>(uno.radio+dos.radio))
	 &&(
	    (dist<(uno.radio+dos.radio+epsilon)) ||
	    (uno.qx-(-widthmedia+radio)<epsilon) ||
	    ((widthmedia-radio-uno.qx)<epsilon) ||
	    (dos.qx-(-widthmedia+radio)<epsilon) ||
	    ((widthmedia-radio-dos.qx)<epsilon)  ||
	    (uno.qy-(-heightmedia+radio)<epsilon) ||
	    ((heightmedia-radio-uno.qy)<epsilon) ||
	    (dos.qy-(-heightmedia+radio)<epsilon) ||
	    ((heightmedia-radio-dos.qy)<epsilon) 
	    ))
	{condini<<uno.qx<<"\t"<<uno.qy<<"\t"<<
	    dos.qx<<"\t"<<dos.qy<<"\t"<<endl;
	  //Contamos sobre la esfera
	  cuentamalos++;
	  //cout<<" Ya aparecio uno donde querias!"<<endl;
	}else{ //Do notin'
	}
           
    };
        
    cout<<"Ya hicimos el " <<n<<endl;
    //debuger.close();
    double proporcionvolumenmalo;
    proporcionvolumenmalo=(double)cuentamalos/(double)ensemble;
    condini<<endl;
    condini<<"radio: "<< radio<<"\t"<<
      "Proporcion de Volumen alrededor De todas las fronteras: "<<proporcionvolumenmalo<<endl;
    condini.close();
      
  };
 
    
  } //Cierra el loop paralelizable

  return 0;
}

