//Bibioteca de interacciones


void reboteentrediscos(Disco &uno, Disco &dos){
/*Rebota contra otro disco de masa finita.
/*cambia los valores de ESTE disco, el otro
  tiene que llamar a la rutina correspondiente */
/* Como eres un mamon, y estas
   trabajando con momentos y no con velocidades
   vas a tener que ajustar la solucion de la 
   wikipedia */
  double normx,normy;
  double pnormuno,ptanuno;
  double pnormdos,ptandos;
  double EnergiaCineticaAntes, EnergiaCineticaDespues;
  

  //Por errores de hiperbolicidad necesitamos renormalizar la energia
  EnergiaCineticaAntes=uno.EnergiaKinetica()+dos.EnergiaKinetica();
  
  normx=(dos.qx-uno.qx)/(dos.radio+uno.radio);
  normy=(dos.qy-uno.qy)/(dos.radio+uno.radio);
  
  pnormuno=uno.px*normx+uno.py*normy;
  ptanuno=-uno.px*normy+uno.py*normx;
  
  pnormdos=dos.px*normx+dos.py*normy;
  ptandos=-dos.px*normy+dos.py*normx;

//Estas son las velocidades a lo largo de la linea de choque
  double u1,u2; //viejas
  double v1,v2; //nuevas
  
  u1=pnormuno/uno.masa;
  u2=pnormdos/dos.masa;
 
  v1=(u1*(uno.masa-dos.masa)+2.0*u2*dos.masa)/
    (uno.masa+dos.masa);
  
  v2=(u2*(dos.masa-uno.masa)+2.0*u1*uno.masa)/
    (uno.masa+dos.masa);
  
  pnormuno=v1*uno.masa;
  pnormdos=v2*dos.masa;
 
  uno.px=pnormuno*normx-ptanuno*normy;
  uno.py=pnormuno*normy+ptanuno*normx;
 
  dos.px=pnormdos*normx-ptandos*normy;
  dos.py=pnormdos*normy+ptandos*normx;
  
  EnergiaCineticaDespues=uno.EnergiaKinetica()+dos.EnergiaKinetica();
  
  double ReNormEnergia;
  ReNormEnergia=sqrt(EnergiaCineticaAntes/EnergiaCineticaDespues);
 
  uno.px=uno.px*ReNormEnergia;
  uno.py=uno.py*ReNormEnergia;
 
  dos.px=dos.px*ReNormEnergia;
  dos.py=dos.py*ReNormEnergia;
 

return;


};
