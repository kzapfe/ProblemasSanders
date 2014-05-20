/*
Programa que corre dos discos en una caja.
 */

/* Version de prueba */

int chocador=-1; //armadillo indexes


#include <vector>
#include "VariablesGlobales01.hpp"
#include "DosDiscosDinamica.hpp"
// math esta incluido en Disco.

double tiempointegrado;
vector<float> trazounox(1);
vector<float> trazounoy(1);

#include "FondosyFiguras01.hpp"

using namespace std;


void runMainLoop( int val )
{
  //Si hacemos esto, val tiene el valor de frames, no de tiempo.
  val++;
  float time=(float)val/(float)SCREEN_FPS;
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
    cout<<"Energia Cinetica Total final"<<endl;   
    cout<<uno.EnergiaKinetica()+dos.EnergiaKinetica()<<endl;
    time=0.0f;
    val=0;
    glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, val );    
  };
  
};


int main(int argc, char* args[]){

  //Argumentos posibles para iniciar freeglut
  glutInit( &argc, args );

  // Create OpenGL 2.1 context
  glutInitContextVersion( 2, 1 );

  //Create Double Buffered Window
  glutInitDisplayMode( GLUT_DOUBLE );
  glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
  glutCreateWindow( "Coordenadas Naturales" );
  glutPositionWindow(701,0);
  
    //Do post window/context creation initialization
    if( !initGL() )
    {
      printf( "Tienes panchos con GLUT!\n" );
      return 1;
    };
    


  ofstream puntos1, puntos2, tiempos;  
  ofstream symbolicdyn;
    
  puntos1.open("qspace01.dat");
  puntos2.open("qspace02.dat");
  tiempos.open("TiemposdeVueloLibre01.dat");


  puntos1<<uno.qx<<"\t"<<uno.qy<<endl;
  puntos2<<dos.qx<<"\t"<<dos.qy<<endl;
       
  cout<<"Energia Cinetica Total inicial"<<endl;   
  cout<<uno.EnergiaKinetica()+dos.EnergiaKinetica()<<endl;  

  trazounox[0]=uno.qx;
  trazounoy[0]=uno.qy;



  //Inicializar las cosas que va hacer freeglut.
  //Set keyboard handler 
  glutKeyboardFunc( handleKeys );  
  //Set rendering function
  glutDisplayFunc( render );
 
  //Set main loop
    glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, 0 );
  //Start GLUT main loop
  glutMainLoop();
   
   
  cout<<"Energia Cinetica Total final"<<endl;   
  cout<<uno.EnergiaKinetica()+dos.EnergiaKinetica()<<endl;


  return 0;
 
}
