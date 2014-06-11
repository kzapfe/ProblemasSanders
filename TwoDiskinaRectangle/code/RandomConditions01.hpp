

void  RandomizaDiscos(Disco &Uno, Disco &Dos, double Energia, gsl_rng *r){
  //Rutina que les da condiciones iniciales a los Discos
 // a partir de la energia y el espacio Disponible
  //Think about this...: No es posible poner Ni siquiera el primero donde sea.
  //especialmente si son gordos. El centro, por ejemplo, queda excluido.
  //Por lo tanto, escoge condiciones de Birkhoff.
  // For first try, very simple... una en cada lado del puto cuadrado.
  //They cannot overlap that way.
  //UUUUUPSSSSS:
  // eso solo es cierto si miden menos que la distancia que todavia les
  //permite hoppear... si no, es falso


  double a, b;   

  a=0.00;
  b=widthmedia-Uno.radio;
  Uno.qx=gsl_ran_flat(r, a, b);
  
  a=-heightmedia+Uno.radio;
  b=-a;
  Uno.qy=gsl_ran_flat(r, a, b);

  
  a=-widthmedia+Uno.radio;
  b=0.00;
  Dos.qx=gsl_ran_flat(r, a, b);
  
  a=-heightmedia+Uno.radio;
  b=-a;
  Dos.qy=gsl_ran_flat(r, a, b);
  
  double EnergiaUno;
  double EnergiaDos;
  double RadioVirtualMomento;
  double ThetaMomento;

  //Distribuimos la energia entre dos.
  EnergiaUno=gsl_ran_flat(r, 0, Energia);
  EnergiaDos=Energia-EnergiaUno;
  
  //acuerdate que definiste los pinches Discos a la Hamilton, NO lagrange.
  //Disco Uno
  RadioVirtualMomento=sqrt(EnergiaUno*2.0*Uno.masa);
  ThetaMomento=gsl_ran_flat(r, 0, 6.28318530718);
  Uno.px=cos(ThetaMomento)*RadioVirtualMomento;
  Uno.py=sin(ThetaMomento)*RadioVirtualMomento;
  //Disco Dos
  RadioVirtualMomento=sqrt(EnergiaDos*2.0*Uno.masa);
  ThetaMomento=gsl_ran_flat(r, 0, 6.28318530718);
  Dos.px=cos(ThetaMomento)*RadioVirtualMomento;
  Dos.py=sin(ThetaMomento)*RadioVirtualMomento;
  

  return;
 
}




void  AbsolutRandomDiscos(Disco &Uno, Disco &Dos, double Energia, gsl_rng *r){
  /*Rutina que les da condiciones iniciales a los Discos
  a partir de la energia y el espacio Disponible
  Think about this...: No es posible poner Ni siquiera el primero donde sea.
  especialmente si son gordos. El centro, por ejemplo, queda excluido.
  Vas a tener que hacer un trial and error. Recuerda que mientras mas
  Gordos sean, mas dificil sera */ 


  double distmincuad, distcuad; 
  double auxx1,auxx2,auxy1,auxy2;
  double medioanchoefe1, medialturaefe1;
  double medioanchoefe2, medialturaefe2;
  distcuad=0.00;
  distmincuad=(Uno.radio+Dos.radio)*(Uno.radio+Dos.radio);
  
  //cout<<" Tienen que estar aleatoreamente a esta distancia cuadrada minima: "<<
  // distmincuad<<endl;
  
  
  int intentos=0;
  medioanchoefe1=widthmedia-Uno.radio;
  medioanchoefe2=widthmedia-Dos.radio;

  medialturaefe1=heightmedia-Uno.radio;
  medialturaefe2=heightmedia-Dos.radio;

  while(distcuad<distmincuad){
    //repeat until it comes right...
    intentos++;

    auxx1=gsl_ran_flat(r, -medioanchoefe1,medioanchoefe1);
    auxx2=gsl_ran_flat(r, -medioanchoefe2,medioanchoefe2);
    
    auxy1=gsl_ran_flat(r, -medialturaefe1,medialturaefe1);
    auxy2=gsl_ran_flat(r, -medialturaefe2,medialturaefe2);
   

    //Norma euclidiana al cuadrado
    distcuad=(auxx1-auxx2)*(auxx1-auxx2)+(auxy1-auxy2)*(auxy1-auxy2);
    //cout<<" En el intento "<<intentos<<" me salio una distcuad de "<<distcuad<<endl;
    

  }

  //cout<<" Me tomo encontrar uno viable asi de veces "<< intentos<<endl;
  //cout<<" y se encuentran a una distancia de " <<sqrt(distcuad)<<endl;

  Uno.qx=auxx1;
  Uno.qy=auxy1;

  Dos.qx=auxx2;
  Dos.qy=auxy2;
  
  
  double EnergiaUno;
  double EnergiaDos;
  double RadioVirtualMomento;
  double ThetaMomento;

  //Distribuimos la energia entre dos.
  EnergiaUno=gsl_ran_flat(r, 0, Energia);
  EnergiaDos=Energia-EnergiaUno;
  
  //acuerdate que definiste los pinches Discos a la Hamilton, NO lagrange.
  //Disco Uno
  RadioVirtualMomento=sqrt(EnergiaUno*2.0*Uno.masa);
  ThetaMomento=gsl_ran_flat(r, 0, 6.28318530718);
  Uno.px=cos(ThetaMomento)*RadioVirtualMomento;
  Uno.py=sin(ThetaMomento)*RadioVirtualMomento;
  //Disco Dos
  RadioVirtualMomento=sqrt(EnergiaDos*2.0*Uno.masa);
  ThetaMomento=gsl_ran_flat(r, 0, 6.28318530718);
  Dos.px=cos(ThetaMomento)*RadioVirtualMomento;
  Dos.py=sin(ThetaMomento)*RadioVirtualMomento;
  
  // cout<< "ya voy a regresar los valores para los discos "<<endl;

  return;
 
}




void  RandomAtEntrance(Disco &Uno, Disco &Dos, double Energia, 
		       double epsilon, gsl_rng *r){
  /*Rutina que les da condiciones iniciales a los Discos
    a partir de la energia y epsilon. El disco uno estará en la puerta, y el segundo
    en algun lugar dentro. La puerta estara en la extrema derecha, a la mitad.
    Las velocidades de Uno seran hacia adentro forzosamente.
    No funciona bien para valores grandes de r o de epsilon.
  Gordos sean, mas dificil sera */ 


  double distmincuad, distcuad; 
  double auxx1,auxx2,auxy1,auxy2;
  double medioanchoefe1, medialturaefe1;
  double medioanchoefe2, medialturaefe2;
  distcuad=0.00;
  distmincuad=(Uno.radio+Dos.radio)*(Uno.radio+Dos.radio);
  
  //cout<<" Tienen que estar aleatoreamente a esta distancia cuadrada minima: "<<
  // distmincuad<<endl;
  
  
  int intentos=0;
  medioanchoefe1=widthmedia-Uno.radio;
  medioanchoefe2=widthmedia-Dos.radio;

  medialturaefe1=heightmedia-Uno.radio;
  medialturaefe2=heightmedia-Dos.radio;

  Uno.qx=medioanchoefe1;
  Uno.qy=gsl_ran_flat(r, -epsilon/2., epsilon/2.);
  
  auxx1=Uno.qx;
  auxx2=Uno.qy;
   

  //el primero va  

  while(distcuad<distmincuad){
    //repeat until it comes right...
    intentos++;
    
    auxy1=gsl_ran_flat(r, -medialturaefe1,medialturaefe1);
    auxy2=gsl_ran_flat(r, -medialturaefe2,medialturaefe2);
   
    //Norma euclidiana al cuadrado
    distcuad=(auxx1-auxx2)*(auxx1-auxx2)+(auxy1-auxy2)*(auxy1-auxy2);
    //cout<<" En el intento "<<intentos<<" me salio una distcuad de "<<distcuad<<endl;  

  }

  //cout<<" Me tomo encontrar uno viable asi de veces "<< intentos<<endl;
  //cout<<" y se encuentran a una distancia de " <<sqrt(distcuad)<<endl;

  Dos.qx=auxx2;
  Dos.qy=auxy2;
  
  
  double EnergiaUno;
  double EnergiaDos;
  double RadioVirtualMomento;
  double ThetaMomento;

  //Distribuimos la energia entre dos.
  EnergiaUno=gsl_ran_flat(r, 0, Energia);
  EnergiaDos=Energia-EnergiaUno;
  
  //acuerdate que definiste los pinches Discos a la Hamilton, NO lagrange.
  //Disco Uno
  RadioVirtualMomento=sqrt(EnergiaUno*2.0*Uno.masa);
  //Las velocidades de Uno apuntan hacia la izquierda.
  ThetaMomento=gsl_ran_flat(r, 1.57079632679, 4.71238898);
  Uno.px=cos(ThetaMomento)*RadioVirtualMomento;
  Uno.py=sin(ThetaMomento)*RadioVirtualMomento;
  //Disco Dos
  RadioVirtualMomento=sqrt(EnergiaDos*2.0*Uno.masa);
  ThetaMomento=gsl_ran_flat(r, 0, 6.28318530718);
  Dos.px=cos(ThetaMomento)*RadioVirtualMomento;
  Dos.py=sin(ThetaMomento)*RadioVirtualMomento;
  
  // cout<< "ya voy a regresar los valores para los discos "<<endl;

  return;
 
}






