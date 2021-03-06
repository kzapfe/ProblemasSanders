//Programa para encontrar el tiempo de primer encuentro
//Dada una simulacion de la dinamica
//Toma en cuenta que la dinamica es BASTANTE Molesta.4
//No algebra lineal, cierto?

#include <fstream>
#include <iostream>
#include <sstream>
#include <gsl/gsl_rng.h> //Inicializa el gsl random
#include <gsl/gsl_randist.h> //las distribuciones de gsl
#include "Animal02.hpp" //Animal01 REBOTA en las paredes, pedazo de animal!!!

using namespace std;

int main(){

  const int Geometrias=100;   
  const int ensemble=6666;
  //La formula no funciona para el caso Maximo
  //asi que considera el caso de hopping como limite
  const double radiomax=0.5;
  //const double radiomax=0.02;

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
#pragma omp  for  schedule(dynamic) //veamos si esta keyword nos quita problemas
      
  
      for(int n=1; n<Geometrias-1; n++){
      //for(int n=3; n<16; n++){
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
	escupefirst<<numeraauxiliar<<"_TiemposEnc3D.dat"<<std::ends;  
	std::string stringfirst;
	stringfirst=escupefirst.str();
	const char *nombrefirst=stringfirst.c_str();
	
	//recicla Variables
	escupeelotro<<numeraauxiliar<<"_CondIniciales3D.dat"<<std::ends;         
	stringfirst=escupeelotro.str();
	const char *nombrecondini=stringfirst.c_str();
	
	streamsize prec=tiemposfirst.precision(12);

	tiemposfirst.open(nombrefirst);   
	condini.open(nombrecondini);
	 
	tiemposfirst<<"#Radio="<<radio<<endl;
	tiemposfirst<<endl;

	float moneda;
	
	for(int j=0; j<ensemble; j++){
	   
	  Animalculo Uno(radio); 
	  Animalculo1D  Dos(radio);
	  
	  AbsolutRandomAnimals(Uno, Dos, r);
	  
	  Uno.enfermo=true;
	  Dos.enfermo=false;
	  
	  if(j<2000){
	    condini<<Uno.x<<"\t"<<Uno.y<<"\t"<<Dos.x<<endl;
	  }


	   double t=0.00;
	   const double tmaxtol=7000000;
	   double distancia;
	   
	   while((!Dos.enfermo)&&(t<tmaxtol)){	
	     //Mido el tiempo en unidades de la celda de finura.
	     moneda=gsl_ran_flat(r, 0, 1);
	     t+=Uno.finura;
	     if(moneda<0.66666667){
	       Uno.caminar(r);}
	     else{
	       Dos.caminar(r);
	     }

	     distancia=dist(Uno,Dos);
	     if(distancia<= Uno.radio+Dos.radio) Dos.enfermo=true;
	     
	   }
	   
	   tiemposfirst<<t<<endl;
	   
	}    
      }
    }

    return 0;
    
}

