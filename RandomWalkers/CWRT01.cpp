/* Implementacion Naive de un Continous Time Random Walker */

//

#include <iostream>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_math.h> //para pi

using namespace std;

int main(){
  
  //El tipico chorizo de gsl_rand para inicializar
  const gsl_rng_type *T;
  T = gsl_rng_ranlxs2;    
  gsl_rng *r ;  
  r = gsl_rng_alloc(T);
  gsl_rng_env_setup();
  gsl_rng_set(r,238104);

  double brinco, estancia;
  double postura, tiempototal;
  
   

  const int pasos=66;
  const double tmax=100;
  const double alpha=1.9872;
  const double variacion=1/M_PI;
  const int realizar=35;
  double DispersionCaminante;
  double qvar;
  double ito, streg;
  int brincostotal;

  for(int j=0; j< realizar; j++){
    //Inicializamos todo a cero
    postura=0.00;
    tiempototal=0.00;
    estancia=0.00;
    qvar=0;
    ito=0;
    streg=0;
    brincostotal=0.000;
    
     while(tiempototal+estancia< tmax ){
       
       tiempototal+=estancia;
       brinco=gsl_ran_levy(r,M_PI, alpha);  
       qvar+=brinco*brinco;
       streg+=(postura+brinco/2.0)*brinco;
       postura+=brinco;
       estancia=gsl_ran_exponential(r,1.0);
       cout<<tiempototal<<"\t"<< postura<<"\t"<<j<<endl;
       brincostotal++;

     }
     
     cout<<endl;
     
  }
  
  return 0;

}

