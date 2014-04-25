

//Ahora lo pones en donde va.
double TiempoChoqueDiscoConcavo(simplectic  &x, simplectic &y){ 
  //choque contra una frontera circular concava de radio 1 
  //centrada en el origen. 
 
  double rho=1.00;//radio efectivo 
    
  double magnvcuad=((x.p*x.p)+(y.p*y.p));
  
  //cout<<" Esto es magnitud Plana al choque "<< sqrt(magnvcuad)<<endl;
  
  double magqcuadrada=(x.q*x.q+y.q*y.q);  
  double distcuad=magqcuadrada-rho*rho;  
  double prodpunto=x.q*x.p+y.q*y.p;
  //en principio, el tiempo mas grande siempre es el correcto.
  //Duda de los herrores num3ricos.
  double t=0;
  
  t=(-prodpunto+
     sqrt(prodpunto*prodpunto-magnvcuad*distcuad))/magnvcuad;
  
  return t;

};



void rebotecontrapared( simplectic &x, simplectic &y){
/* Un disco perfecto es tangente a todo lo que toca*/
/* de ahi que el vector normal sea el vector del centro
   al punto de contacto, y el tangente sea el ortogonal a este.
   Dado que un objeto de masa infinita no es afectado, 
   y esta rutina afecta solamente  a las propiedades del disco
   podemos considerarlo un efecto interno.*/
  double normx, normy;
  double rho=1.0;
  
  normx=x.q/rho;
  normy=y.q/rho;

  double magnvantes=sqrt((x.p*x.p)+(y.p*y.p));

  double pnorm, ptan;

  pnorm=x.p*normx+y.p*normy;
  ptan=-x.p*normy+y.p*normx;

  pnorm=-pnorm;

  x.p=pnorm*normx-ptan*normy;
  y.p=pnorm*normy+ptan*normx;

  double magnvdespues=sqrt((x.p*x.p)+(y.p*y.p));

  // cout<<" La mag de la v plana antes del rebote= " <<magnvantes<<endl;
  //cout<<" La mag de la v plana despu del rebote= " <<magnvdespues<<endl;

  return;


};



