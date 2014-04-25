/* programa que hace pruebas sobre los Animalculos */
/* Version 04, un array de animales con probabilidad Gaussiana
   de traslaparse */

#include <vector>

using namespace std;
vector<float> trazounox(1);
vector<float> trazounoy(1);
int animalgridsize=12;
int animalespecial=0;
double raditodeinteraccion=0.1;
double territorialidad=1.3;

#include <fstream>

#include <gsl/gsl_rng.h> //Inicializa el gsl random
#include <gsl/gsl_randist.h> //las distribuciones de gsl
const gsl_rng_type *T;
gsl_rng *r ; 


# include "Animal01.hpp"

Animalculo * Animal2;

# include "FondosyFiguras04.hpp"



void runMainLoop( int val )
{
//Si hacemos esto, val tiene el valor de frames, no de tiempo.
  val++;
  float time=(float)val/60.0;
  //Frame logic
  //  update();
  render();
  update(Animal2);    
  trazounox.push_back(Animal2[animalespecial].realx());
  trazounoy.push_back(Animal2[animalespecial].realy());

  glutTimerFunc( 100 / SCREEN_FPS, runMainLoop, val );     
  
};


int main(int argc, char* args[]){

  //Argumentos posibles para iniciar freeglut
  glutInit( &argc, args );

  // Create OpenGL 2.1 context
  glutInitContextVersion( 2, 1 );

  //Create Double Buffered Window
  glutInitDisplayMode( GLUT_DOUBLE );
  glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
  glutCreateWindow( "Animales en su territorio" );
  glutPositionWindow(701,0);
  
    //Do post window/context creation initialization
    if( !initGL() )
    {
      printf( "Tienes panchos con GLUT!\n" );
      return 1;
    };

   
  T = gsl_rng_ranlxs2;    
  r = gsl_rng_alloc(T);
  gsl_rng_env_setup();
  gsl_rng_set(r,238108);
  
  ofstream centrosterritorio;
  centrosterritorio.open("Centros01.dat");
  

  Animal2=new Animalculo[animalgridsize*animalgridsize];
  animalespecial=animalgridsize*animalgridsize/2+animalgridsize/2;

  for(int i=0; i<animalgridsize; i++){
    for(int j=0; j<animalgridsize; j++){

      double territorio;
      double sigma;
      territorio=(double)animalgridsize/2.0;
      sigma=0.25*territorialidad;
     
      Animal2[i*animalgridsize+j].CornerX=(-territorio+i+gsl_ran_gaussian(r, sigma))
	*territorialidad;
      
      Animal2[i*animalgridsize+j].CornerY=(-territorio+j+gsl_ran_gaussian(r, sigma))
	*territorialidad;

      Animal2[i*animalgridsize+j].radio=raditodeinteraccion;

      centrosterritorio<<Animal2[i*animalgridsize+j].CornerX<<
	"\t"<<Animal2[i*animalgridsize+j].CornerY<<endl;

    }
    
  }

  Animal2[animalespecial].enfermo=true;

  trazounox[0]=Animal2[animalespecial].realx();
  trazounoy[0]=Animal2[animalespecial].realy();

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


