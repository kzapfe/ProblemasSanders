/*
Programa que corre dos discos en una caja.
 */

/* Que saca las distribuciones importantes */
/* Dado que es muy idiota tratar de esperar a que se "ergodice todo"
   vamos a usar un ensemble de condiciones iniciales */
// estos dos son los de gsl
// Version Paralela

/* Este codigo, marcado con la señal 01, corre VARIAS vez sobre el mismo
elemento del ensamble, calculando realmente Un RETURN TIME, no un
FIRST PASSAGE TIME. Curiosamente, este es el que da el limite correcto,
pero el comportamiento no es tan del todo correcto. Tiene sus bemoles,
especificamente esa Pancita caida respecto a la curva teorica.
 */

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>


#include "VariablesGlobalesParalel01.hpp"
#include "DosDiscosDinamica.hpp"
#include "RandomConditions01.hpp"

// math esta incluido en Disco.

using namespace std;


int main(){

  //FreeTime escribe TODOS los chocques, no tenemos tanto disco duro...
  //bajale al ensemble, subele a las colisiones
  
  const int Geometrias=128;
  const int ensemble=1000;

  const int Ntotal=ensemble*colisionesmax;
  
  const gsl_rng_type *T;
  T = gsl_rng_ranlxs2;    
  
  const double epsilonagujero=0.05; //para el Sojourn Time
  
  const double radioefemin=0.001;
  const double radioefemax=radiomaxforhop;
  //const double radioefemax=epsilonagujero/2.0-0.0001;
  
#pragma omp parallel num_threads(8)

  {
#pragma omp  for schedule(dynamic)
    //Se supone que todo lo que esta declarado dentro del for es privado.
    
    //Para HopTimes, no tiene sentido buscar arriba de r=0.25, 
    // tu programa no es robusto, revisa eso, algo falla.
    //    for(int n=85; n<Geometrias; n++){
    for(int n=1; n<Geometrias; n++){
          
    double hoptime=0.00;
    double acumtimes=0.00;
    double acumtimescuad=0.0;
    double meantime,meansquare,stddev,stderr; 
    double tiempodechoque=0;
    double tiempoentrebrincos=0.0;
    //    const double toleranciacahoques=0.000000001;

    gsl_rng *r ;  
    r = gsl_rng_alloc(T);
    gsl_rng_env_setup();
    gsl_rng_set(r,238109);
  

    int numeraauxiliar=1000+n;
    ofstream tiemposfree, tiemposhop;

    std::ostringstream escupehop;
          
    //solo el disco UNO puede escapar
    escupehop<<numeraauxiliar<<"_MeanChoqueVert01.dat"<<std::ends;
      
    std::string stringhop;

    stringhop=escupehop.str();
      
    const char *nombrehop=stringhop.c_str();
    
    /*Fijate que todo el desmadre de arriba
      es solo para convertir un numero a char*/ 
    streamsize prec=tiemposhop.precision(16);
    
    tiemposhop.open(nombrehop);

    double radio=radioefemin+
      (double)n/(double)Geometrias*(radioefemax-radioefemin);
    double distancia;


    cout<<"Estoy comenzando el proceso "<< n << " con radio="<<radio<<endl;           
    tiemposhop<<"radio "<<radio<<endl;
    tiemposhop<<"Energia "<<Energia<<endl;
    // tiemposhop<<endl; //no necesitamos blanklines
    double energiapromedio=0.000;
    

    for(int j=0; j<ensemble; j++){
      //Random initial conditions.

      Disco uno(0.0,0.25,0.0, 0.0,radio);
      Disco dos(0.0,-0.25,0.0,0.0,radio);
      
      int chocador=-1; //armadillo indexes. ^Better this one.
      bool condicionagujero=false;
      
      double energianumerica;
      
      //RandomAtEntrance(uno,dos,Energia,epsilonagujero, r);
      AbsolutRandomDiscos(uno,dos,Energia,r);

      tiempodechoque=0.0; 
      tiempoentrebrincos=0.0;
      hoptime=0;
     
      //Dado que estamos esperando un RETURN TIME
      //Primero tenemos que ergodicidar Sobre condiciones EN EL HOP-Posture
      //EXACTAMENTE
      int cuentachoques=0; 
      chocador=-1; //pretend that we are on the UNINTERESTING WALL      
      tiempoentrebrincos=0.00;

      //cabexota, mano cabexota.

      while(cuentachoques<colisionesmax){
	tiempoentrebrincos=0.00;
	chocador=-1; //pretend that we are on the UNINTERESTING WALL      
	/* -1 -> nada
	   0 uno choca con pared vertical
	   1 uno choca con pared horizontal
	   2 dos choca con pared vertical
	   3 dos choca con pared horizontal
	   4 uno y dos colisionan
	   5 hop vertical.
	*/
	
	while(/* Tiempo de escape por agujero
	      //!((chocador==0)&&(uno.qx>0.0)&&
	      //(uno.qy<epsilonagujero/2.)&&(uno.qy>-epsilonagujero/2.)) */
	      (chocador!=0)) //hopingtime
	  {
	    tiempodechoque=dinamicaunchoqueyhopp(uno,dos,chocador);	
	    tiempoentrebrincos+=tiempodechoque;
	  }
	
	acumtimes+=tiempoentrebrincos;
	acumtimescuad+=tiempoentrebrincos*tiempoentrebrincos;
	cuentachoques++;
	/* Karel, creo que ya es momento de que no escribas todos
	   los datos, basta las medias y la desviacion y el N de pruebas */
	//tiemposhop<<tiempoentrebrincos<<endl;

    } //cierra sobre los choques/eventos
      energianumerica=uno.EnergiaKinetica()+dos.EnergiaKinetica();
      energiapromedio+=energianumerica;
      // solo vamos a escribir el total de ahora en adelante.
      //tiemposhop<<tiempoentrebrincos<<endl;
      // cout<<" vamos en el disco "<<j+1<<endl;
      //cout<<" tuvo tantos choques "<<cuentachoques<<endl;
      
    }//cierra sobre el ensamble

    meantime=acumtimes/(double)Ntotal;
    meansquare=acumtimescuad/(double)Ntotal;
    stddev=sqrt(meansquare-meantime*meantime);
    stderr=stddev/sqrt((double)Ntotal);
    energiapromedio/=ensemble;
    tiemposhop<<"# radio \t tiempopromedio \t tcuadpromedio \t stdev \t sterr \t Ntot"<<endl;
    tiemposhop<<radio<<"\t"<<meantime<<"\t"<<meansquare<<"\t"<<stddev<<"\t"<<stderr<<"\t"<<Ntotal<<endl;
    cout<<"He terminado con el proceso "<<n<<endl;
    cout<<"La energia promedio final fue "<<energiapromedio<<endl;
    
    } //Cierra el loop paralelizable
    
  } //Cierra el pragma de openmp
 
  return 0;
  
}
