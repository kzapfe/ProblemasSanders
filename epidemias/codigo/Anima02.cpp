/* programa que hace pruebas sobre los Animalculos */

#include <vector>

using namespace std;
vector<float> trazounox(1);
vector<float> trazounoy(1);
int animales=50;

#include <fstream>

#include <gsl/gsl_rng.h> //Inicializa el gsl random
#include <gsl/gsl_randist.h> //las distribuciones de gsl
const gsl_rng_type *T;
gsl_rng *r ; 


# include "Animal01.hpp"

Animalculo Animal1(0.02);
Animalculo * Animal2;

# include "FondosyFiguras02.hpp"





void runMainLoop( int val )
{
//Si hacemos esto, val tiene el valor de frames, no de tiempo.
  val++;
  float time=(float)val/60.0;
  //Frame logic
  //  update();
  render();
  update(Animal1, Animal2);    
  trazounox.push_back(Animal1.x);
  trazounoy.push_back(Animal1.y);

  glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, val );     
  
};


int main(int argc, char* args[]){

  //Argumentos posibles para iniciar freeglut
  glutInit( &argc, args );

  // Create OpenGL 2.1 context
  glutInitContextVersion( 2, 1 );

  //Create Double Buffered Window
  glutInitDisplayMode( GLUT_DOUBLE );
  glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
  glutCreateWindow( "Animal en su territorio" );
  glutPositionWindow(701,0);
  
    //Do post window/context creation initialization
    if( !initGL() )
    {
      printf( "Tienes panchos con GLUT!\n" );
      return 1;
    };

 
  ofstream walker;
  
  T = gsl_rng_ranlxs2;    
  r = gsl_rng_alloc(T);
  gsl_rng_env_setup();
  gsl_rng_set(r,238108);
  

  walker.open("Testing01.dat");
  
  trazounox[0]=Animal1.x;
  trazounoy[0]=Animal1.y;
  Animal1.enfermo=true;

  Animal2=new Animalculo[animales];
  double ratgen=0.01;
  
  for(int i=0; i<animales; i++){
    Animal2[i].x=gsl_ran_flat(r, -1, 1);
    Animal2[i].y=gsl_ran_flat(r, -1, 1);
  }


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

}


