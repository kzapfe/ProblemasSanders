/* programa que hace pruebas sobre los Animalculos */

# include <fstream>
#include <gsl/gsl_rng.h> //Inicializa el gsl random
#include <gsl/gsl_randist.h> //las distribuciones de gsl

# include "Animal01.hpp"

using namespace std;


int main(){
 
  ofstream walker;
  Animalculo Animal1;

  const gsl_rng_type *T;

  gsl_rng *r ;  
  

  T = gsl_rng_ranlxs2;    
  r = gsl_rng_alloc(T);
  gsl_rng_env_setup();
  gsl_rng_set(r,238108);
  
  

  walker.open("Testing01.dat");

  int imax=10000;


  for(int i=0; i<imax; i++){
    Animal1.caminar(r);
    walker<<Animal1.x<<"\t"<<Animal1.y<<"\t"<<i<<endl;
  };

  return 0;

}


