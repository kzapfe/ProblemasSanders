//Biblioteca de rutinas de choque. Puras funciones double o cosas asi


double TiempoChoqueDiscoConcavo(Disco  &Colisionador){ 
  //choque contra una frontera circular concava de radio 1 
  //centrada en el origen. 
 
  double rho=1.00-Colisionador.radio ; //radio efectivo 
  double vx,vy; //velocidades
  vx=Colisionador.px/Colisionador.masa;
  vy=Colisionador.py/Colisionador.masa;
   
  double magnvcuad=(vx*vx)+(vy*vy);

  double magqcuadrada=(Colisionador.qx*Colisionador.qx)
    +(Colisionador.qy*Colisionador.qy);
  
  double distcuad=magqcuadrada-rho*rho;
  
  double prodpunto=Colisionador.qx*vx+
    Colisionador.qy*vy;

  //en principio, el tiempo mas grande siempre es el correcto.
  //Duda de los herrores num3ricos.
  double t=0;
  
  t=(-prodpunto+
     sqrt(prodpunto*prodpunto-magnvcuad*distcuad))/magnvcuad;
  

  return t;

};


double TiempoChoqueDosDiscos(Disco &Uno, Disco &Dos){ 
  //choque contra una frontera circular concava (vista desde adentro)
  
  double rho=Uno.radio+Dos.radio ; //radio efectivo
  double vx,vy; //velocidades effectivas
  vx=Uno.px/Uno.masa-Dos.px/Dos.masa;
  vy=Uno.py/Uno.masa-Dos.py/Dos.masa;


  double xtilde, ytilde; //posiciones iniciales efectivas
  xtilde=(Uno.qx-Dos.qx);
  ytilde=(Uno.qy-Dos.qy);
  
  //De aqui en adelante es lo mismo que con el circulo exterior.
  double magnvcuad=vx*vx+vy*vy;
  double magqcuadrada=(xtilde*xtilde)
    +(ytilde*ytilde);
  double distcuad=magqcuadrada-rho*rho;  
  double prodpunto=xtilde*vx+ytilde*vy;
  
  //cout<<"magnvcuad"<<"\t"<<"magqcuadrada"<<"\t"<<"distcuad"<<"\t"<<"prodpunto"<<endl;
  //cout<<magnvcuad<<"\t"<<magqcuadrada<<"\t"<<distcuad<<"\t"<<prodpunto<<endl;
 
  double discriminat;
  discriminat=prodpunto*prodpunto-magnvcuad*distcuad;
  //cout<<"discriminat="<<discriminat<<endl;  
  double t=0;

  //Diferencia=>> Aqui queremos el tiempo menor POSITIVO
  //Devolvemos el tiempo aunque sea preterito, main se debe encargar de 
  //no usarlo o usarlo para otra cosa.

  if(discriminat<0){
    t=-996;
  }else{
    t=(-prodpunto-sqrt(prodpunto*prodpunto-magnvcuad*(distcuad)))/magnvcuad;
  };
 
  return t;

};
