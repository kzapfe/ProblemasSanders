/* Clase de animales circulares que tienen un 
territorio cuadrado de lado Unidad, y que 
se mueven como caminantes aleatoreos sobre una malla bidimensional*/

# ifndef __Animalculo__
# define __Animalculo__

#include <math.h>
#include <iostream>

using namespace std;

class Animalculo{
  /*Los animalculos son animales con distancia de interraccion radio.
    Viven en un territorio cuadrado de lado 1.
    Se mueven en pasos aleatoreos de longitud 
    finura.
    Pueden estar enfermos o sanos.
    Si dos estan a menos de 2 radios de distancia,
    se puede contagiar uno de otro */

private:
  const double bordervalue=0.5;


public:

  
  //La finura de la malla
  double finura;

  double radio;  
  double x, y;
  
  bool enfermo;
  //La "esquina" central del territorio
  double CornerX, CornerY;

  Animalculo(){
    finura=0.02;
    this->radio=finura;
    this-> x=0;
    this->y=0;
    this->enfermo=false;
    this->CornerX=-0.5; 
    this->CornerY=-0.5; 

  };

  Animalculo(double radio){
    this->radio=radio;
    x=0;
    y=0;
    enfermo=false;
    CornerX=-0.5; 
    CornerY=-0.5;
    finura=0.001;
   
  }


  Animalculo(double radio, double CornerX, double CornerY) {
    this->radio=radio;
    x=0;
    y=0;
    enfermo=false;
    this->CornerX=CornerX;
    this->CornerY=CornerY;  
    finura=0.01;
  }


  Animalculo(double radio, double CornerX, double CornerY, double x, double y) {
    this->radio=radio;
    this->x=x;
    this->y=y;
    enfermo=false;
    this->CornerX=CornerX;
    this->CornerY=CornerY;  
    finura=0.01;
  }

  double realx(){
    double result=CornerX+x;
    return result;
  }

  double realy() {
    double result=CornerY+y;
    return result;
  }


  void caminar(gsl_rng * r){
    float toincoss=gsl_ran_flat(r, 0, 1);
    //aqui rebotan
    //Chale mano, creo que pusiste que reboraran Adentro del cuadrado...
    if(toincoss<0.25)
      { if(x<bordervalue-radio)
	  {x+=finura;}
	else
	  {x-=finura;}}
    
    else if (toincoss<0.5)
      { if(x>-bordervalue+radio)
	  {x-=finura;}
	else
	  {x+=finura;}}

    else if(toincoss<0.75)
      { if(y<bordervalue-radio)
	  {y+=finura;}
	else
	  {y-=finura;}}
    
    else if (toincoss<1.0)
      { if(y>-bordervalue+radio)
	  {y-=finura;}
	else
	  {y+=finura;}}

    return;

  }

  void VueloBrown(gsl_rng * r){
    /*hace un brinco "browniano" con
     distancia elegida gaussianamente y 
     angulo uniforme. 
     la dispersion es del tamanho de finura- 
     La trayectoria se enrolla si encuentra las paredes.
    */
    double distancia, angulo;
    double deltax, deltay;
  
    distancia= gsl_ran_gaussian(r, 1.0);
    angulo=gsl_ran_flat(r, 0, 2. * M_PI);
    deltax=distancia*cos(angulo);
    deltay=distancia*sin(angulo);
    
    x+=deltax;
    y+=deltay;

     if(fabs(x)>bordervalue)x=trayectoriaenrollada(x);
     if(fabs(y)>bordervalue)y=trayectoriaenrollada(y);
     
    
  
    return;
    
  }
  
  double trayectoriaenrollada(double entrada){
    //Enrolla la trayectoria en una celda de -border a border
    // como si fuera billar.
    double auxiliar;
    int paridad;
    double result;

  
     if(fabs(entrada)>bordervalue){
       //creo que por como esta implementado floor
       //en el caso "negativo" las cosas deben funcionar igual...
       if(entrada>0.00){
	 
	 
	 paridad=pow((-1),(floor(entrada-bordervalue)));
	 auxiliar=entrada-bordervalue-floor(entrada-bordervalue);
	 //	cout<<"aux="<<auxiliar<<endl;
	 result=(bordervalue-auxiliar)*paridad;
	 //cout<<"x="<<x<<endl;
       }
       if(entrada<=0.00){
	 
	 auxiliar=floor(entrada+bordervalue);
	 //cout<<"el otro auxiliar"<<auxiliar<<endl;
	 result=entrada-auxiliar;
	 //cout<<"x en el otro caso="<<x<<endl;
       }    

     }      
     
     return result;
  }




};

/****************************************
//Termina la Clase Animalculo
****************************************/



//Rutinas externas


double dist(Animalculo &uno, Animalculo &dos){
  double result;
  result = (uno.realx()-dos.realx())*(uno.realx()-dos.realx())
    +(uno.realy()-dos.realy())*(uno.realy()-dos.realy());
  result = sqrt(result);

  return result;
};




void  AbsolutRandomAnimals(Animalculo &primo, Animalculo &secundo, gsl_rng *r){
  /*Rutina que les da condiciones iniciales a los Discos
  a partir de la energia y el espacio Disponible
  Think about this...: No es posible poner Ni siquiera el primero donde sea.
  especialmente si son gordos. El centro, por ejemplo, queda excluido.
  Vas a tener que hacer un trial and error. Recuerda que mientras mas
  Gordos sean, mas dificil sera */ 


  double distmincuad, distcuad; 
  double auxx1,auxx2,auxy1,auxy2;
  double medioancho=0.5;
  distcuad=0.00;
  distmincuad=(primo.radio+secundo.radio)*(primo.radio+secundo.radio);
  
  //cout<<" Tienen que estar aleatoreamente a esta distancia cuadrada minima: "<<
  // distmincuad<<endl;
  
  
  int intentos=0;

  while(distcuad<distmincuad){
    //repeat until it comes right...
    intentos++;

    auxx1=gsl_ran_flat(r, -medioancho,medioancho);
    auxx2=gsl_ran_flat(r, -medioancho,medioancho);
   
    auxy1=gsl_ran_flat(r, -medioancho,medioancho);
    auxy2=gsl_ran_flat(r, -medioancho,medioancho);
   
    //Norma euclidiana al cuadrado
    distcuad=(auxx1-auxx2)*(auxx1-auxx2)+(auxy1-auxy2)*(auxy1-auxy2);

    // cout<<" En el intento "<<intentos<<" me salio una distcuad de "<<distcuad<<endl;


  }

  primo.x=auxx1;
  primo.y=auxy1;

  secundo.x=auxx2;
  secundo.y=auxy2;
  
  return;
 
}




# endif

