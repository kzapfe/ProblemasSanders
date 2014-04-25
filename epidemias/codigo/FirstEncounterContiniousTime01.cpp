//Programa para encontrar el tiempo de primer encuentro
//Dada una simulacion de la dinamica
//Toma en cuenta que la dinamica es BASTANTE Molesta.4
//No algebra lineal, cierto?

#include <fstream>
#include <iostream>
#include <sstream>
#include <gsl/gsl_rng.h> //Inicializa el gsl random
#include <gsl/gsl_randist.h> //las distribuciones de gsl
# include "Animal01.hpp"

using namespace std;

int main(){

  const int Geometrias=50;   
  const int ensemble=4000;
  const double radiomax=sqrt(2)/2.0;

  const gsl_rng_type *T;
  T = gsl_rng_ranlxs2; 

  cout<<" +++++++++++++++++++++++++++++++++++++"<<endl;
  cout<<"Dada la geometria, el radio maximo es "<<radiomax<<endl;
  cout<<"Los animales pueden alcanzar las orillas. "<<radiomax<<endl;
  cout<< "++++++++++++++++++++++++++++++++++++++++"<<endl;
  cout<<"Version en paralelos " <<endl;
  cout<<endl; 

#pragma omp parallel num_threads(7)
    {
#pragma omp  for 
      
  
      for(int n=7; n<14; n++){
	//Si paralelizas la Rutina, tienes que meter esto al omp loop.
        gsl_rng *r ; 
	
	double hoptime=0.00;
	double tiempodechoque=0;
	double tiempoentrebrincos=0.0;

	r = gsl_rng_alloc(T);
	gsl_rng_env_setup();
	gsl_rng_set(r,238107);
	
	double radio=(double)n/(double)Geometrias*radiomax;
	
	cout<<"El radio es " << radio<<endl;
	
	//Ash, ya deberias de hacer una rutina que haga este
	 //desmadrito de numerar archivos, carajo.
	int numeraauxiliar=1000+n;
	ofstream tiemposfirst, condini;
	 
	ostringstream escupefirst, escupeelotro, escupemas;
	escupefirst<<numeraauxiliar<<"_FirstTimeContagio.dat"<<std::ends;         
	std::string stringfirst;
	stringfirst=escupefirst.str();
	const char *nombrefirst=stringfirst.c_str();
	
	//recicla Variables
	escupeelotro<<numeraauxiliar<<"_CondIniciales.dat"<<std::ends;         
	stringfirst=escupeelotro.str();
	const char *nombrecondini=stringfirst.c_str();
	
	tiemposfirst.open(nombrefirst);   
	condini.open(nombrecondini);
	 
	streamsize prec=tiemposfirst.precision(15);
	
	for(int j=0; j<ensemble; j++){
	   
	  Animalculo Uno(radio), Dos(radio);
	  
	  AbsolutRandomAnimals(Uno, Dos, r);
	  
	  Uno.enfermo=true;
	  Dos.enfermo=false;
	  
	  condini<<Uno.x<<"\t"<<Uno.y<<"\t"<<Dos.x<<"\t"<<Dos.y<<"\t"<<endl;
	  
	   double t=0.00;
	   const double tmaxtol=700;
	   double distancia;
	   
	   while((!Dos.enfermo)&&(t<tmaxtol)){	
	     //Mido el tiempo en unidades de la celda de finura.
	     t+=Uno.finura;
	     Uno.caminar(r);
	     Dos.caminar(r);
	
	     distancia=dist(Uno,Dos);
	     if(distancia<= Uno.radio+Dos.radio) Dos.enfermo=true;
	
	   }
	   
	   tiemposfirst<<t<<endl;
	   
	}    
      }
    }

    return 0;
    
}

