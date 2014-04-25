/*una version mas simple de RandomoConditions, pero solo en posicion, para probar 
  las formulas del volumen */

void RandomPosition(Disco &Uno,   Disco &Dos, double wentre2, double lentre2,
		    gsl_rng *r){


  double distmincuad, distcuad; 
  double auxx1,auxx2,auxy1,auxy2;
  double medioanchoefe1, medialturaefe1;
  double medioanchoefe2, medialturaefe2;
  distcuad=0.00;
  distmincuad=(Uno.radio+Dos.radio)*(Uno.radio+Dos.radio);
  
  //cout<<" Tienen que estar aleatoreamente a esta distancia cuadrada minima: "<<
  // distmincuad<<endl;
  
  
  int intentos=0;
  medioanchoefe1=wentre2-Uno.radio;
  medioanchoefe2=wentre2-Dos.radio;

  medialturaefe1=lentre2-Uno.radio;
  medialturaefe2=lentre2-Dos.radio;


  Uno.qx=gsl_ran_flat(r, -medioanchoefe1,medioanchoefe1);
  Dos.qx=gsl_ran_flat(r, -medioanchoefe2,medioanchoefe2);
  
  Uno.qy=gsl_ran_flat(r, -medialturaefe1,medialturaefe1);
  Dos.qy=gsl_ran_flat(r, -medialturaefe2,medialturaefe2);
   
  return;

};



