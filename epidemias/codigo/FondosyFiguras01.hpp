#include "LOpenGL.h"
#include "circuloopengl.hpp"


#include <iostream>

/*Me gusta todo mas en un solo archivo
//hpp que en uno h y otro cpp.  
//se me hace mucha mamada.
//Por supuesto que con tu convencion la documentacion queda menos clara.
// Pero para tus propositos es suficiente */

//Screen Constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const int SCREEN_FPS = 60;
const float TimeStep=1.0f/SCREEN_FPS;

//Color modes
//Trazar la cola del disco.
bool trazo=false;

//Centros y velocidades de los discos
float c1x, c1y;
float r1;



bool initGL()
{
  glutSetWindow(1);
  //Initialize Projection Matrix
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  //Vamos a usar las coordenadas naturales de OpenGL
  //Se parecen mas a la fisica que te gusta.
  
  //Initialize Modelview Matrix
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  //Initialize clear color
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
  // rojo, verde, azul y alfa. 
  //Valore entre 0 y 1 punto flotante.
  

  //Check for error
  GLenum error = glGetError();
  if( error != GL_NO_ERROR )
    {
      printf( "Muere, no pude inicializar OpenGL!! %s\n", gluErrorString( error ) );
      return false;
    };
  
  return true;
};



void update(Animalculo &animal)
{
  
  animal.caminar(r);
  c1x=animal.x;
  c1y=animal.y;
  r1=animal.radio;

};


void render()
{ 
  glutSetWindow(1);
  //Clear color buffer
  glClear( GL_COLOR_BUFFER_BIT );

  //Reset modelview matrix
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  
  //Render the quad
  

  
  
  /* Tell OpenGL your intentions */
  // glColor3f( 0.1f, 0.1f, 0.1f );
  //glBegin(GL_POLYGON);
  /* Set the vertices */
  //glVertex2d(-widthmedia, heightmedia);
  //glVertex2d(-widthmedia, -heightmedia);
  //glVertex2d(widthmedia, -heightmedia);
  //glVertex2d(widthmedia, heightmedia);
  /* Done making polygon */
  //glEnd(); 
  
  glLineWidth(1.0) ;
  glColor3f( 0.45f, 0.3f, 0.1f );
  DrawDisk(c1x, c1y, r1, 50);

   
 
  if( trazo ){
    glColor3f( 0.9f, 0.9f, 0.3f );
    glLineWidth(2.0) ;
    glBegin(GL_LINES);    
    for(int i=1; i<trazounox.size();i++){
      glVertex2f(trazounox[i-1], trazounoy[i-1]);//output vertex           
      glVertex2f(trazounox[i], trazounoy[i]);//output vertex           
    };
    glEnd();
    
  };


  
  //Update screen 1
  glutSwapBuffers();
  
};


void handleKeys( unsigned char key, int x, int y ){
  //If the user presses q
  
  //  if( key == 'x' )glutLeaveMainLoop();
  
  // if(GLUT_ACTION_ON_WINDOW_CLOSE)glutLeaveMainLoop();
  
  
  if( key == 't' ){
    trazo=!trazo;   
    };
  
  

};  
  

