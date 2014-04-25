/* Modelo Susceptible, Infectado, Recuperado, Discretizado */


#include <vector>



#include <fstream>

#include <gsl/gsl_rng.h> //Inicializa el gsl random
#include <gsl/gsl_randist.h> //las distribuciones de gsl
/* porque vamos a usar random ?
Porque las tazas de infecion y cura son numeros reales,
pero los numeros sosn discretos, asi que usamos un volado
cargado para saber si alguien se cura o se infecta */


using namespace std;


int main(int argc, char* args[]){

  const int poblacion=10000;
  const int tmax=200; //Dias

  const gsl_rng_type *T;
  gsl_rng *r ; 
     
  T = gsl_rng_ranlxs2;    
  r = gsl_rng_alloc(T);
  gsl_rng_env_setup();
  gsl_rng_set(r,238108);

  
  int infectados=1;
  int sanos;
  int recuperados;
  float tazainfecto, tazacura;
  float volado;

  for(int t=0; t< tmax; t++){
    
    sanos=sanos*(1-tazainfecto*Infecto);
    infectados=infectados*(1+tazainfecto*sanos-tazacura);
    recuperados=tazacura*infectados;
    
  }

  return 0;
  

}
