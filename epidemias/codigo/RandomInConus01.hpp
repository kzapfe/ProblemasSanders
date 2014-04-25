
#ifndef __RandomConus__
#define __RandomConus__


#include <gsl/gsl_rng.h> //Inicializa el gsl random
#include <gsl/gsl_randist.h> //las distribuciones de gsl
#include "CaminantesNoPlanos01.hpp" //Los caminantes no rebotan, esto veras como arreglarlo


Caminante3D RandomInConus3D(double radiointerior, double radioexterior, gsl_rng *r){
  //El cono tiene angulo recto, entonces zmax=radioexterrior.
  Caminante3D result;
  
  //Ni pedo, podriamos hacerlo Perfecto, pero no andamos de humor
  
  //los ponemos en el cuadrado que engloba al anillo
  result.x=gsl_ran_flat(r, -radioexterior,radioexterior);
  result.y=gsl_ran_flat(r, -radioexterior,radioexterior);
  result.z=gsl_ran_flat(r, 0.00 ,radioexterior);
  
  while(((result.DistanciaPlana()<radiointerior)||
	 (result.DistanciaPlana()>radioexterior))||
	(result.z>(radioexterior-result.DistanciaPlana())))
    {
    result.x=gsl_ran_flat(r, -radioexterior,radioexterior);
    result.y=gsl_ran_flat(r, -radioexterior,radioexterior);
    result.z=gsl_ran_flat(r, 0.00,radioexterior);
    }
  
  return result; 
}

Caminante4D RandomInConus4D(double radiointerior, double radioexterior, gsl_rng *r){
  //El cono tiene angulo recto, entonces zmax=radioexterrior.
  Caminante4D result;
  
  //Ni pedo, podriamos hacerlo Perfecto, pero no andamos de humor
  
  //los ponemos en el cuadrado que engloba al anillo
  result.x1=gsl_ran_flat(r, -radioexterior,radioexterior);
  result.x2=gsl_ran_flat(r, -radioexterior,radioexterior);
  //Dos radios, dos alturas
  result.x3=gsl_ran_flat(r, 0.00 ,radioexterior);
  result.x4=gsl_ran_flat(r, 0.00 ,radioexterior);
  
  while(
	((result.DistanciaPlana()<radiointerior)||
	 (result.DistanciaPlana()>radioexterior))||
	(result.x3>(radioexterior-result.DistanciaPlana()))||
	(result.x4>(radioexterior-result.DistanciaPlana()))
	)
    {
    result.x1=gsl_ran_flat(r, -radioexterior,radioexterior);
    result.x2=gsl_ran_flat(r, -radioexterior,radioexterior);
    result.x3=gsl_ran_flat(r, 0.00,radioexterior);
    result.x4=gsl_ran_flat(r, 0.00,radioexterior);
    }
  
  return result; 
}

#endif
