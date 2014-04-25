/*
Programa que corre dos discos en una caja.
 */

/* Que saca las distribuciones importantes */
/* Dado que es muy idiota tratar de esperar a que se "ergodice todo"
   vamos a usar un ensemble de condiciones iniciales */
// estos dos son los de gsl
// Version que calcula los exponentes de Liapunov.


#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <armadillo>

int chocador=-1; //armadillo indexes


#include "VariablesGlobalesParalel01.hpp"
#include "DosDiscosDinamica.hpp"
#include "RandomConditions01.hpp"
#include "DinamicaTangente01.hpp"


// math esta incluido en Disco.

using namespace std;
using namespace arma;


int main(){


  const int Geometrias=12;   
  const int ensemble=1;
  const gsl_rng_type *T;
  T = gsl_rng_ranlxs2;    
  
  //#pragma omp parallel num_threads(6)
  {
    //#pragma omp  for 
    //Se supone que todo lo que esta declarado dentro del for es privado.

    //for(int n=0; n<Geometrias; ++n){
    for(int n=7; n<8; ++n){
          
    //Generador aleatoreo de optima calidad
    gsl_rng *r ;  
    r = gsl_rng_alloc(T);
    gsl_rng_env_setup();
    gsl_rng_set(r,238109);
  
    int numeraauxiliar=1000+n;
    ofstream  LiapunovFile;
    ofstream TestQ1, TestQ2;

    std::ostringstream escupeliap;
          
    escupeliap<<numeraauxiliar<<"_Liapunov"<<std::ends;
      
    std::string stringliap;

    stringliap=escupeliap.str();
      
    const char *nombreliap=stringliap.c_str();
    
    /*Fijate que todo el desmadre de arriba
      es solo para convertir un numero a char*/ 
    streamsize prec=LiapunovFile.precision(16);
   
  
    LiapunovFile.open(nombreliap);
    TestQ1.open("TestQandPUnoVarios.dat");
    TestQ2.open("TestQandPDosVarios.dat");

    //Si el ensamble es muy grande, no escribimos mas que las 
    //condini al disco duro. 

    double radio=(double)n/(double)Geometrias*radiomax;

    for(int j=0; j<ensemble; j++){
      //Random initial conditions.
      
      
      double lambda;
    
      Disco uno(0.0,0.25,0.0, 0.0,radio);
      Disco dos(0.0,-0.25,0.0,0.0,radio);
      vec tangentequno, tangenteqdos;
      vec tangentepuno, tangentepdos;

      vec tangentequnoauxiliar, tangenteqdosauxiliar;
      vec tangentepunoauxiliar, tangentepdosauxiliar;
      vec MomentoRelativoAuxiliar(2);
      

      //Random sampling over disks and tangent space
      RandomizaDiscos(uno,dos,Energia,r);
      
     
      
      tangentequno.randn(2);
      tangenteqdos.randn(2);
      tangentepuno.randn(2);
      tangentepdos.randn(2);

      
      
      tangentequno=tangentequno/norm(tangentequno,2);
      tangenteqdos=tangenteqdos/norm(tangenteqdos,2);
      tangentepuno=tangentepuno/norm(tangentepuno,2);
      tangentepdos=tangentepdos/norm(tangentepdos,2);
     
      

     
      lambda=0.000;

      TestQ1<<uno.qx<<"\t"<<uno.qy<<"\t"<<uno.px<<"\t"<<uno.py
	    <<"\t"<<tangentequno[0]<<"\t"<<tangentequno[1]
	    <<"\t"<<tangentepuno[0]<<"\t"<<tangentepuno[1]
	    <<"\t"<<0<<"\t"<<j<<"\t"<<chocador<<endl;

      TestQ2<<dos.qx<<"\t"<<dos.qy<<"\t"<<dos.px<<"\t"<<dos.py
	    <<"\t"<<tangenteqdos[0]<<"\t"<<tangenteqdos[1]
	    <<"\t"<<tangentepdos[0]<<"\t"<<tangentepdos[1]
	    <<"\t" <<0<<"\t"<<j<<"\t"<<chocador<<endl;

      
   

      for(int i=1; i<=colisionesmax;i++){ 

	
	tangentequnoauxiliar=tangentequno;
	tangentepunoauxiliar=tangentepuno;
	tangenteqdosauxiliar=tangenteqdos;
	tangentepdosauxiliar=tangentepdos;
	
	
	MomentoRelativoAuxiliar[0]=dos.px-uno.px;
	MomentoRelativoAuxiliar[1]=dos.py-uno.py;
	
	
	
	//La dinamica en el espacio fase
	double tiempodechoque=dinamicaunchoque(uno,dos);
	

	//La transformacion inducida en el espacio tangente
	//Recuerda, ambos viajan HASTA que uno se estrella.
	//El que se estrella compone el viaje y luego PLAM
	if(chocador==0){
	  //Si el disco uno pega derecha, izquierda1
	  MapeoDifLibre(tangentequno, tangentepuno, uno, tiempodechoque);
	  MapeoDifParedVertical(tangentequno,tangentepuno);
	  MapeoDifLibre(tangenteqdos, tangentepdos, dos, tiempodechoque);

	}else if (chocador==1){
	  //Si el disco uno pega arriba, abajo
	  MapeoDifLibre(tangentequno, tangentepuno, uno, tiempodechoque);
	  MapeoDifParedHorizontal(tangentequno, tangentepuno);
	  MapeoDifLibre(tangenteqdos, tangentepdos, dos, tiempodechoque);
	  
	}else if (chocador==2){
	  //Si el disco dos pega derecha, izquierda
	  MapeoDifLibre(tangenteqdos, tangentepdos, dos, tiempodechoque);
	  MapeoDifParedVertical(tangenteqdos, tangentepdos);
	  MapeoDifLibre(tangentequno, tangentepuno, uno, tiempodechoque);

	}else if (chocador==3){
	  //Si el disco dos pega arriba, abajo.
	  MapeoDifLibre(tangenteqdos, tangentepdos, dos, tiempodechoque);
	  MapeoDifParedHorizontal(tangenteqdos, tangentepdos);
	  MapeoDifLibre(tangentequno, tangentepuno, uno, tiempodechoque);
	
	}else if (chocador==4){
	  //Si loss discos chocan.
	  
	  MapeoDifLibre(tangentequno, tangentepuno, uno, tiempodechoque);
	  MapeoDifLibre(tangenteqdos, tangentepdos, dos, tiempodechoque); 	  
	  MapeoDifChoque(tangentequno, tangentepuno, tangenteqdos,tangentepdos,
	  		 uno, dos, MomentoRelativoAuxiliar);	  
	 
	}

	
	
      TestQ1<<uno.qx<<"\t"<<uno.qy<<"\t"<<uno.px<<"\t"<<uno.py
	    <<"\t"<<tangentequno[0]<<"\t"<<tangentequno[1]
	    <<"\t"<<tangentepuno[0]<<"\t"<<tangentepuno[1]
	    <<"\t"<<i<<"\t"<<j<<"\t"<<chocador<<endl;

      TestQ2<<dos.qx<<"\t"<<dos.qy<<"\t"<<dos.px<<"\t"<<dos.py
	    <<"\t"<<tangenteqdos[0]<<"\t"<<tangenteqdos[1]
	    <<"\t"<<tangentepdos[0]<<"\t"<<tangentepdos[1]
	    <<"\t"<<i<<"\t"<<j<<"\t"<<chocador<<endl;

      
	
      
      }; //Cierra el ciclo de las choques
       
      TestQ1<<endl;
      TestQ2<<endl;
      
    
    }; //Cierra el ciclo de los ensambles
 
  
    cout<<"Es el paso "<< n<<", con radio "<<radio<<endl;

    } //Cierra el ciclo de las geometrias (paralelizable)

  }
  return 0;
  
}
