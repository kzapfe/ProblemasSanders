//Encabezado estandar
# ifndef __Disco__
# define __Disco__

# include <math.h>
const double pi=3.14159265359;

using namespace std;

template <typename T> int sgn(T val) {
  //A template for signum function. completely general.
    return (T(0) < val) - (val < T(0));
}

class Disco{
/* Una clase de discos rigidos que no rotan y chocan entre ellos */

public:

//Notacion usual, sentido usual.
//Cartesian Coordinates make life easier.
  double qx,qy;
  double px,py;
  double radio, masa;


  Disco(){
    //Constructor por omision
    qx=0;
    qy=0;
    px=0;
    py=0;
    radio=0.02;
    masa=1.0;
  };
  

  Disco(double qx, double qy, double px, double py)
  { //Constructor por omision en masa y radio.
    this->qx=qx;
    this->px=px;
    this->qy=qy;
    this->py=py;
    radio=0.02;
    masa=1.0;
  };
  
  

  Disco(double qx, double qy, double px, double py, double radio)
  { //Constructor por valor omision  de masa.
    this->qx=qx;
    this->px=px;
    this->qy=qy;
    this->py=py;
    this->radio=radio;
    masa=1.0;
  };
  

  Disco(double qx, double qy, double px, double py, double radio, double masa)
  { //Constructor explicito todo.
    /*  if(masa=0){
      cout<<"No puedes hacer particulas de masa cero, foton-man!"<<endl;
      exit( );}*/
    this->qx=qx;
    this->px=px;
    this->qy=qy;
    this->py=py;
    this->radio=radio;
    this->masa=masa;
  };
  
  //copy constructor
  Disco(const Disco&);

  //Destructor
 
  //Propiedades Mecanicas

  double MomentoAngular(){
    //momento angualar respecto al origen
    //convencion mano derecha
    double result=qx*py-qy*px;
    return result;
  };

  double MomentoAngular(double centrox, double centroy){
    //momento angualar respecto al punto centro
    //convencion mano derecha
    double result=(qx-centrox)*py-(qy-centroy)*px;
    return result;
 };


  double angulo(){
    double result=atan2(qy,qx);
    if(result<0.00){
      result=result+2.0*pi;};
    return result;
    
  };

  double EnergiaKinetica(){
    double result;
    result=(px*px+py*py)/(2.0*masa);
    return result;
  };


  double RadioCaustica(){
    //El radio de la caustica.
    double result;
    if(sqrt(px*px+py*py)>0.0){
     result=(qx*py-qy*px)/sqrt(px*px+py*py);
    }else{
      result=0.0;}    
     return result;
    };

  
  double VeloAngularEffectiva(double RadioExterno){
    //Calcula la velocidad angular promedio
    //en una mesa de billar circular de RadioExterno.
    double result;
    double L;
    double magv;   
    double RadioEffectivo;
    double d;
    L=qx*py-qy*px;
    magv=sqrt(px*px+py*py)/masa;
    if(magv>0.00){
    RadioEffectivo=RadioExterno-radio;
    d=sqrt(RadioEffectivo*RadioEffectivo-L*L/(px*px+py*py));
    result=asin(d/RadioEffectivo)*magv*sgn(L)/d;
    }else{result=0.00;}
    
    return result;

  };


    double OmegaInstantanea(){
    //Calcula la velocidad angular promedio
    //en una mesa de billar circular de RadioExterno.
    double result;
    double L,r; 
    L=qx*py-qy*px;
    r=sqrt(qx*qx+qy*qy);
    if(r>0.00){
      result=L/(r*r*masa);
    }else{result=0.00;}
    
    return result;

  };



//Metodos
  
void avanzarvacio(double tau){
/*avanza tau unidades en un espacio vacio.
  Es una transformacion de deslape. 
  Solo funciona en cartesianas, pendejo.*/ 
qx=qx+tau*px/masa;
qy=qy+tau*py/masa;
return;
};




void rebotecontrapared( double contactx, double contacty){
/* Un disco perfecto es tangente a todo lo que toca*/
/* de ahi que el vector normal sea el vector del centro
   al punto de contacto, y el tangente sea el ortogonal a este.
   Dado que un objeto de masa infinita no es afectado, 
   y esta rutina afecta solamente  a las propiedades del disco
   podemos considerarlo un efecto interno.*/
  double normx, normy;
  //double normaantes=sqrt(px*px+py*py);

  normx=(contactx-qx)/radio;
  normy=(contacty-qy)/radio;

 

  double pnorm, ptan;
  
  pnorm=px*normx+py*normy;
  ptan=-px*normy+py*normx;
  
  pnorm=-pnorm;
  
  px=pnorm*normx-ptan*normy;
  py=pnorm*normy+ptan*normx;
  
  //double normadespues=sqrt(px*px+py*py);

  //  px=px*(normaantes/normadespues);
  //py=py*(normaantes/normadespues);

  return;
  

};



};

#endif 
