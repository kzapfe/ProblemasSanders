
#include <fstream>
#include <iostream>
#include <sstream>
#include <gsl/gsl_rng.h> //Inicializa el gsl random
#include <gsl/gsl_randist.h> //las distribuciones de gsl
# include "Animal01.hpp"

using namespace std;

int main(){


  gsl_rng *r ; 
  const gsl_rng_type *T;
  T = gsl_rng_ranlxs2; 
  
  
  r = gsl_rng_alloc(T);
  gsl_rng_env_setup();
  gsl_rng_set(r,238107);
	

  Animalculo uno(0.5), dos(0.5);
  
  AbsolutRandomAnimals(uno, dos, r);
  
  cout<<uno.x<<"\t"<<endl;
  
  double auxiliarpendeja;

  for(int t=0; t<30; t++){
    uno.VueloBrown(r);
    
    
    
    if(fabs(uno.x)>0.5) {
      cout<<"This should evaluate TRUE"<<endl;
      cout<<(fabs(uno.x)>0.5)<<endl;
    }

    cout<<uno.x<<"\t"<<uno.y<<endl;
  

  }

  return 0;


}
