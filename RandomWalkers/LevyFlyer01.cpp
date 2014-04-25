/* programa que hace un volante de Levy */


#include <math.h>       /* cos sen */
#include <iostream>  
#include <fstream>  
#include <gsl/gsl_rng.h> //Inicializa el gsl random
#include <gsl/gsl_randist.h> //las distribuciones de gsl


using namespace std;

int main ()
{
  const gsl_rng_type * T;
  gsl_rng * r;
  
  
  float equis=0, ye=0;
  ofstream datos;
  datos.open("LevyFlyer01.dat"); 
  /* create a generator chosen by the 
     environment variable GSL_RNG_TYPE */
     
  gsl_rng_env_setup();
  
  T = gsl_rng_default;
  r = gsl_rng_alloc (T);

  //parametro de la distribucion
  double mu = 3.0;
  int paso=0;
  float dire=0.0;
  const float pi=3.1415926; 

  for (int i = 0; i < 1000; i++) 
    {
      dire=gsl_ran_flat ( r, 0.00, 2.0*pi);
      paso = gsl_ran_poisson (r, mu);
      equis+=paso*cos(dire);
      ye+=paso*sin(dire);

      datos<<equis<<"\t"<<ye<<endl;    
    }

  gsl_rng_free (r);

  return 0;
}
