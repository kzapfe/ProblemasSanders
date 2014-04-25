/* Caminantes Aleatoreos No Planares. Vuelan o se mueven en Celdas */

# ifndef __Caminante__
# define __Caminante__

#include <math.h>
#include <iostream>
#include <gsl/gsl_rng.h> //Inicializa el gsl random
#include <gsl/gsl_randist.h> //las distribuciones de gsl


using namespace std;

class Caminante3D{
  /*Los animalculos son animales con distancia de interraccion radio.
    Viven en un territorio cuadrado de lado 1.
    Se mueven en pasos aleatoreos de longitud 
    finura.
    Pueden estar enfermos o sanos.
    Si dos estan a menos de 2 radios de distancia,
    se puede contagiar uno de otro */



public:
  
  //La finura de la malla
  double finura;
  double dispersion;

  double x,y,z;
    

  Caminante3D(){
    finura=0.01;
    dispersion=0.05;
    this-> x=0;
    this->y=0;
    this->z=0;
  };

  Caminante3D(double finura){
    this->finura=finura;
    dispersion=0.05;
    x=0;
    y=0;
    z=0;   
   
  }


     friend void swap(Caminante3D& first, Caminante3D& second) // nothrow
    {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap; 

        // by swapping the members of two classes,
        // the two classes are effectively swapped
        swap(first.finura, second.finura); 
        swap(first.dispersion, second.dispersion);
	swap(first.x, second.x);
	swap(first.y, second.y);
	swap(first.z, second.z);

    }
  
  Caminante3D& operator=(Caminante3D other) // (1)
  {
    swap(*this, other); // (2)

    return *this;
  } 


  double DistanciaAlPunto(){
    //sin argumento, la distancia al origen, si no, a un punto
    double result;
    result=sqrt(x*x+y*y+z*z);
    return result;

  }

  
  double DistanciaPlana(){
    //sin argumento, la distancia al origen, si no, a un punto
    double result;
    result=sqrt(x*x+y*y);
    return result;

  }


  double DistanciaAlPunto(double xprima, double yprima, double zprima){
    //sin argumento, la distancia al origen, si no, a un punto
    double result;
    result=sqrt((x-xprima)*(x-xprima)+
		(y-yprima)*(y-yprima)
		+(z-zprima)*(z-zprima)
		);
    return result;

  }

  double DistanciaPlana(double xprima, double yprima){
    //sin argumento, la distancia al origen, si no, a un punto
    double result;
    result=sqrt((x-xprima)*(x-xprima)+
		(y-yprima)*(y-yprima));
    return result;

  }
  
  void caminar(gsl_rng * r){
    float toincoss=gsl_ran_flat(r, 0, 3);
    //No hay fonteras
    if(toincoss<0.5)
      {x+=finura;}
    else if (toincoss<1.0)
      {x-=finura;}
    else if (toincoss<1.5)
      {y+=finura;}
    else if (toincoss<2.0)
      {y-=finura;}   
    else if (toincoss<2.5)
      {z+=finura;}
    else 
      {z-=finura;} 
    return;

  }

  void VueloBrown(gsl_rng * r){
    /*hace un brinco "browniano" con
     distancia elegida gaussianamente y 
     angulo uniforme. 
     la dispersion es del tamanho de finura- 
     La trayectoria se enrolla si encuentra las paredes.
    */
    double direccionx,direcciony, direccionz;
    double distancia;
    double norma;
    int paridad;
    double auxiliar;

    //Random point in 3 sphere

    direccionx= gsl_ran_gaussian(r, dispersion);
    direcciony= gsl_ran_gaussian(r, dispersion);
    direccionz= gsl_ran_gaussian(r, dispersion);
    
    
    norma=sqrt(direccionx*direccionx+
	       direcciony*direcciony+
	       direccionz*direccionz);
    direccionx/=norma;
    direcciony/=norma;
    direccionz/=norma;
    
    //Then FLYYYYY...
    distancia= gsl_ran_gaussian(r, dispersion);

    direccionx*=distancia;
    direcciony*=distancia;
    direccionz*=distancia;
    
    x+=direccionx;
    y+=direcciony;
    z+=direccionz;
 
    return;
    
  }
  
  

};



class Caminante4D{
  /*Los animalculos son animales con distancia de interraccion radio.
    Viven en un territorio cuadrado de lado 1.
    Se mueven en pasos aleatoreos de longitud 
    finura.
    Pueden estar enfermos o sanos.
    Si dos estan a menos de 2 radios de distancia,
    se puede contagiar uno de otro */



public:
  
  //La finura de la malla
  double finura;
  double dispersion;

  double x1,x2,x3,x4;
    

  Caminante4D(){
    finura=0.01;
    dispersion=1.0;
    this-> x1=0;
    this-> x2=0;
    this-> x3=0;
    this-> x4=0;
  
   
  };

  Caminante4D(double finura){
    this->finura=finura;
    dispersion=1.0;
    x1=0;
    x2=0;
    x3=0;
    x4=0;
    
   
  }
  
  friend void swap(Caminante4D& first, Caminante4D& second) // nothrow
    {
      // enable ADL (not necessary in our case, but good practice)
      using std::swap; 

      // by swapping the members of two classes,
        // the two classes are effectively swapped
      swap(first.finura, second.finura); 
      swap(first.dispersion, second.dispersion);
      swap(first.x1, second.x1);
      swap(first.x2, second.x2);
      swap(first.x3, second.x3);
      swap(first.x4, second.x4);

    }
  
  Caminante4D& operator=(Caminante4D other) // (1)
  {
    swap(*this, other); // (2)

    return *this;
  } 





  double DistanciaAlPunto(){
    //sin argumento, la distancia al origen, si no, a un punto
    double result;
    result=sqrt(x1*x1+x2*x2+x3*x3+x4*x4);
    return result;

  }

  
  double DistanciaPlana(){
    //sin argumento, la distancia al origen, si no, a un punto
    double result;
    result=sqrt(x1*x1+x2*x2);
    return result;

  }


  double DistanciaAlPunto(double x1prima, double x2prima, 
			  double x3prima, double x4prima){
    //sin argumento, la distancia al origen, si no, a un punto
    double result;
    result=sqrt((x1-x1prima)*(x1-x1prima)+
		(x2-x2prima)*(x2-x2prima)
		+(x3-x3prima)*(x3-x3prima)
		+(x4-x4prima)*(x4-x4prima)
		);
    return result;

  }

  double DistanciaPlana(double xprima, double yprima){
    //sin argumento, la distancia al origen, si no, a un punto
    double result;
    result=sqrt((x1-xprima)*(x1-xprima)+
		(x2-yprima)*(x2-yprima));
    return result;

  }


  void caminar(gsl_rng * r){
    float toincoss=gsl_ran_flat(r, 0, 4);
    //No hay fonteras
    if(toincoss<0.5)
      {x1+=finura;}
    else if (toincoss<1.0)
      {x1-=finura;}
    else if (toincoss<1.5)
      {x2+=finura;}
    else if (toincoss<2.0)
      {x2-=finura;}   
    else if (toincoss<2.5)
      {x3+=finura;}
    else if(toincoss<3)
      {x3-=finura;} 
    else if (toincoss<3.5)
      {x4+=finura;}
    else 
      {x4-=finura;} 
    
    return;

  }

  void VueloBrown(gsl_rng * r){
    /*hace un brinco "browniano" con
     distancia elegida gaussianamente y 
     angulo uniforme. 
     la dispersion es del tamanho de finura- 
     La trayectoria se enrolla si encuentra las paredes.
    */
    double direccionx1,direccionx2, direccionx3,direccionx4;
    double distancia;
    double norma;
   

    //Random point in 3 sphere

    direccionx1= gsl_ran_gaussian(r, dispersion);
    direccionx2= gsl_ran_gaussian(r, dispersion);
    direccionx3= gsl_ran_gaussian(r, dispersion);
    direccionx4= gsl_ran_gaussian(r, dispersion);
    
    
    norma=sqrt(direccionx1*direccionx1+
	       direccionx2*direccionx2+
	       direccionx3*direccionx3+
	       direccionx4*direccionx4);
    direccionx1/=norma;
    direccionx2/=norma;
    direccionx3/=norma;
    direccionx4/=norma;
    
    //Then FLYYYYY...
    distancia= gsl_ran_gaussian(r, dispersion);

    direccionx1*=distancia;
    direccionx2*=distancia;
    direccionx3*=distancia;
    direccionx4*=distancia;
    
    x1+=direccionx1;
    x2+=direccionx2;
    x3+=direccionx3;
    x4+=direccionx4;
 
    return;
    
  }
  
  

};

/****************************************
//Terminan las Clases Caminantes
****************************************/

//Rutinas auxiliares

void EnrollarEnCirculo(Caminante3D & anterior, Caminante3D & nuevo, double Radio){
  
  Caminante3D choque;
  choque=anterior;

  /*
  cout<<"Este es Uno atterrizo afuera"<<endl;
  cout<<nuevo.x<<"\t"<<nuevo.y<<"\t"<<endl;
  cout<<"Este es aux deberia estar dentro  "<<endl;
  cout<<anterior.x<<"\t"<<anterior.y<<"\t"<<endl;
  */

  double vx, vy;
  vx=(nuevo.x-anterior.x);
  vy=(nuevo.y-anterior.y);
  double dotprod, reffcuad, vcuad;

  vcuad=vx*vx+vy*vy;
  dotprod=anterior.x*vx+anterior.y*vy;
  reffcuad=(anterior.x*anterior.x+anterior.y*anterior.y)-Radio*Radio;

  double tgrande;

  tgrande=(-dotprod+sqrt(dotprod*dotprod-vcuad*reffcuad))/vcuad;
  
  //cout<<"Esto es t grande "<<tgrande<<endl;
  choque.x=anterior.x+tgrande*vx;
  choque.y=anterior.y+tgrande*vy;

  //linea de prueba
  //cout<<choque.x<<"\t"<<choque.y<<"\t"<<tgrande<<endl;
 
  //Debuging code
  if(tgrande>1.0000){
    cout<<"come mierda"<<endl;
    cout<<vx<<"\t"<<vy<<endl;
    cout<<vcuad<<endl;
    cout<<dotprod<<endl;
    cout<<tgrande<<endl;
    cout<<anterior.DistanciaPlana()<<"\t"<<nuevo.DistanciaPlana()<<"\t"<<vcuad<<endl;
    cout<<choque.x<<"\t"<<choque.y<<endl;
    exit(1);}
  

  //Rotaciones otra vez... esto ya lo deberias escribir con los ojos cerrados
  double compnorm, comptan;
  compnorm=(choque.x*vx+choque.y*vy)/Radio;
  comptan=(-choque.y*vx+choque.x*vy)/Radio;
  
  compnorm=-compnorm;
  
  vx=(choque.x*compnorm-choque.y*comptan)/Radio;
  vy=(choque.y*compnorm+choque.x*comptan)/Radio;
  // a ver chi cherto
  
  nuevo.x=choque.x+(1.-tgrande)*vx;
  nuevo.y=choque.y+(1.-tgrande)*vy;

  if(nuevo.DistanciaPlana()>Radio)
    {//Recursion
      EnrollarEnCirculo(choque,  nuevo,  Radio);
    }
    

  return;

} 




Caminante3D RandomInAnulus(double radiointerior, double radioexterior, gsl_rng *r){

  Caminante3D result;
  
  //Ni pedo, podriamos hacerlo Perfecto, pero no andamos de humor
  
  //los ponemos en el cuadrado que engloba al anillo
  result.x=gsl_ran_flat(r, -radioexterior,radioexterior);
  result.y=gsl_ran_flat(r, -radioexterior,radioexterior);

  while((result.DistanciaPlana()<radiointerior)||
	(result.DistanciaPlana()>radioexterior)){
    result.x=gsl_ran_flat(r, -radioexterior,radioexterior);
    result.y=gsl_ran_flat(r, -radioexterior,radioexterior);
  }
  
  return result;

}

//ahora para 4D

void EnrollarEnCirculo(Caminante4D & anterior, Caminante4D & nuevo, double Radio){
  
  Caminante4D choque;
  choque=anterior;

  /*
  cout<<"Este es Uno atterrizo afuera"<<endl;
  cout<<nuevo.x<<"\t"<<nuevo.y<<"\t"<<endl;
  cout<<"Este es aux deberia estar dentro  "<<endl;
  cout<<anterior.x<<"\t"<<anterior.y<<"\t"<<endl;
  */

  double vx, vy;
  vx=(nuevo.x1-anterior.x1);
  vy=(nuevo.x2-anterior.x2);
  double dotprod, reffcuad, vcuad;

  vcuad=vx*vx+vy*vy;
  dotprod=anterior.x1*vx+anterior.x2*vy;
  reffcuad=(anterior.x1*anterior.x1+anterior.x2*anterior.x2)-Radio*Radio;

  double tgrande;

  tgrande=(-dotprod+sqrt(dotprod*dotprod-vcuad*reffcuad))/vcuad;
  
  //cout<<"Esto es t grande "<<tgrande<<endl;
  choque.x1=anterior.x1+tgrande*vx;
  choque.x2=anterior.x2+tgrande*vy;

  //linea de prueba
  //cout<<choque.x<<"\t"<<choque.y<<"\t"<<tgrande<<endl;
 
  //Debuging code
  if(tgrande>1.0000){
    cout<<"come mierda"<<endl;
    cout<<vx<<"\t"<<vy<<endl;
    cout<<vcuad<<endl;
    cout<<dotprod<<endl;
    cout<<tgrande<<endl;
    cout<<anterior.DistanciaPlana()<<"\t"<<nuevo.DistanciaPlana()<<"\t"<<vcuad<<endl;
    cout<<choque.x1<<"\t"<<choque.x2<<endl;
    exit(1);}
  

  //Rotaciones otra vez... esto ya lo deberias escribir con los ojos cerrados
  double compnorm, comptan;
  compnorm=(choque.x1*vx+choque.x2*vy)/Radio;
  comptan=(-choque.x2*vx+choque.x1*vy)/Radio;
  
  compnorm=-compnorm;
  
  vx=(choque.x1*compnorm-choque.x2*comptan)/Radio;
  vy=(choque.x2*compnorm+choque.x1*comptan)/Radio;
  // a ver chi cherto
  
  nuevo.x1=choque.x1+(1.-tgrande)*vx;
  nuevo.x2=choque.x2+(1.-tgrande)*vy;

  if(nuevo.DistanciaPlana()>Radio)
    {//Recursion
      EnrollarEnCirculo(choque,  nuevo,  Radio);
    }
    

  return;

} 




Caminante4D RandomInAnulus4D(double radiointerior, double radioexterior, gsl_rng *r){

  Caminante4D result;
  
  //Ni pedo, podriamos hacerlo Perfecto, pero no andamos de humor
  
  //los ponemos en el cuadrado que engloba al anillo
  result.x1=gsl_ran_flat(r, -radioexterior,radioexterior);
  result.x2=gsl_ran_flat(r, -radioexterior,radioexterior);

  while((result.DistanciaPlana()<radiointerior)||
	(result.DistanciaPlana()>radioexterior)){
    result.x1=gsl_ran_flat(r, -radioexterior,radioexterior);
    result.x2=gsl_ran_flat(r, -radioexterior,radioexterior);
  }
  
  return result;

}


double DistanciaOrtogonalIntervalo(Caminante3D & anterior, Caminante3D & nuevo){
  //Encuentra la distancia minima de una recta en el plano x, y al origen
  //dada por dos caminantes en el cilindro.
   

  double vx, vy;
  vx=(nuevo.x-anterior.x);
  vy=(nuevo.y-anterior.y);
  
  double result;

  result=sqrt(
	      (anterior.x-vx*(anterior.x+anterior.y)/(vx+vy))*
	      (anterior.x-vx*(anterior.x+anterior.y)/(vx+vy))+ 
	      (anterior.y-vy*(anterior.x+anterior.y)/(vx+vy))*
	      (anterior.y-vy*(anterior.x+anterior.y)/(vx+vy)));


  return result;

}

double TauOrtogonalIntervalo
(Caminante3D & anterior, Caminante3D & nuevo){
  /* El tau donde es ortogonal una chiva definida en el plano de dos punticos */
  
  double vx, vy;
  vx=(nuevo.x-anterior.x);
  vy=(nuevo.y-anterior.y);

  double result;

  result=(anterior.x+anterior.y)/(-vx-vy);

  



}




# endif

