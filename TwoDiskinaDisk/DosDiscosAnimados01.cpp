/*Programa que corre el programa de los dos discos animados
  y usa la info para hacer animaciones. */

int chocador=0;

#include "LUtil.hpp"
#include "DosDiscosDinamica.hpp"


//Esta parte es el Loop de freeglut.

double radio=0.2;
Disco uno(0.2,0.5,0.1,-0.9,radio);
Disco dos(0.0,-0.5,0.0,0.9,radio);
float tiempodechoque=0;


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
  glutCreateWindow( "Dos Discos en un Circulo" );
  
  //Do post window/context creation initialization
  if( !initGL() )
    {
      printf( "Tienes panchos con GLUT!\n" );
      return 1;
    };
  
  
  /*por el momento sin datos en el disco duro
    Bueno, no si.*/  
  ofstream puntos1, puntos2;
  
  puntos1.open("Qspace01.dat");
  puntos2.open("Qspace02.dat");
 
  //Primeros puntos centro discos
  puntos1<<uno.qx<<"\t"<<uno.qy<<endl;
  puntos2<<dos.qx<<"\t"<<dos.qy<<endl;
  
  tiempodechoque=dinamicaunchoque(uno, dos);
  
  puntos1<<uno.qx<<"\t"<<uno.qy<<endl;
  puntos2<<dos.qx<<"\t"<<dos.qy<<endl;
  
  cout<<tiempodechoque<<endl;

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



