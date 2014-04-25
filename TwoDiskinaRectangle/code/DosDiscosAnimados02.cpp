/*Programa que corre el programa de los dos discos animados
  y usa la info para hacer animaciones. */

//Igual metes esto en un puto archivo con todas las variables iniciales

#include <vector>
#include "VariablesGlobales01.hpp"
#include "LUtil02.hpp"
#include "DosDiscosDinamica.hpp"



//Esta parte es el Loop de freeglut.
//Creo que eventualmente la sacaremos de aqui.

void runMainLoop( int val )
{
  //Si hacemos esto, val tiene el valor de frames, no de tiempo.
  val++;
  float time=(float)val/60.0;
  //Frame logic
  //  update();
  render();
  
  if(time<tiempodechoque){
    //Run frame one more time
    glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, val );   
  }else{
    update(uno, dos);
    trazounox.push_back(uno.qx);
    trazounoy.push_back(uno.qy);
    tiempodechoque=dinamicaunchoque(uno, dos);   
    time=0.0f;
    val=0;
    glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, val );    
  };
  
};


int main(int argc, char* args[]){

  //Argumentos posibles para iniciar freeglut
  glutInit( &argc, args );
  
  //Create OpenGL 2.1 context
  glutInitContextVersion( 2, 1 );
  
  //Create Double Buffered Window
  glutInitDisplayMode( GLUT_DOUBLE );
  glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
  glutCreateWindow( "Coordenadas Naturales" );
  glutPositionWindow(701,0);
  glutCreateWindow( "Coordenadas Rotando" );
  glutPositionWindow(0,0);
    //Do post window/context creation initialization
    if( !initGL() )
    {
      printf( "Tienes panchos con GLUT!\n" );
      return 1;
    };
  
  
  /*por el momento sin datos en el disco duro
    Bueno, no si.*/  
  ofstream puntos1, puntos2;
  
  puntos1.open("QspaceAnimado01.dat");
  puntos2.open("QspaceAnimado02.dat");
  MomAngular=uno.MomentoAngular()+dos.MomentoAngular();

  cout<<"# El momento Angular total es "<<MomAngular<<endl;

  //Primeros puntos centro discos
  puntos1<<uno.qx<<"\t"<<uno.qy<<endl;
  puntos2<<dos.qx<<"\t"<<dos.qy<<endl;
   
trazounox[0]=uno.qx;
trazounoy[0]=uno.qy;
 

  tiempodechoque=dinamicaunchoque(uno, dos);
  
  puntos1<<uno.qx<<"\t"<<uno.qy<<endl;
  puntos2<<dos.qx<<"\t"<<dos.qy<<endl;
  
  trazounox.push_back(uno.qx);
  trazounoy.push_back(uno.qy);
  

  //Inicializar las cosas que va hacer freeglut.
  //Set keyboard handler 
  glutKeyboardFunc( handleKeys );  
  //Set rendering function
  glutDisplayFunc( render );
 
  //Set main loop
    glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, 0 );
  //Start GLUT main loop
  glutMainLoop();
   
  return 0;
  
};



