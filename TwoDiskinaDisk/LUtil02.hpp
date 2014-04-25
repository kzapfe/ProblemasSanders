#include "LOpenGL.h"
#include "circuloopengl.hpp"
#include "Disco01.hpp"
#include <iostream>

/*Me gusta todo mas en un solo archivo
//hpp que en uno h y otro cpp.  
//se me hace mucha mamada.
//Por supuesto que con tu convencion la documentacion queda menos clara.
// Pero para tus propositos es suficiente */

//Screen Constants
const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 700;
const int SCREEN_FPS = 60;
const float TimeStep=1.0f/SCREEN_FPS;

//Color modes
//Trazar la cola del disco.
bool trazo=false;

//Centros y velocidades de los discos
float c1x, c2x, c1y, c2y;
float p1x, p2x, p1y, p2y;
float r1,r2;
float radioaparente;
double velangularaparente;

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
  glClearColor( 0.1f, 0.1f, 0.1f, 0.0f );
  // rojo, verde, azul y alfa. 
  //Valore entre 0 y 1 punto flotante.
  
  glutSetWindow(2);
  //Igual para la segundo ventana
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  glClearColor( 0.9f, 0.3f, 0.2f, 0.0f );
  
    //Initialize clear color
  


  //Check for error
  GLenum error = glGetError();
  if( error != GL_NO_ERROR )
    {
      printf( "Muere, no pude inicializar OpenGL!! %s\n", gluErrorString( error ) );
      return false;
    };
  
  return true;
};

void centrardiscos(Disco &uno, Disco &dos){
  
  c1x=uno.qx;
  c2x=dos.qx;
  c1y=uno.qy;
  c2y=dos.qy;
  p1x=uno.px;
  p2x=dos.px;
  p1y=uno.py;
  p2y=dos.py;

  r1=uno.radio;
  r2=dos.radio;

  velangularaparente=uno.VeloAngularEffectiva(1.0)
    +dos.VeloAngularEffectiva(1.0);
  

};

void update(Disco &uno, Disco &dos)
{

  centrardiscos(uno, dos);
  
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
  //Como tus frames son 60/segundo, cada paso requiere avanzar v*1./60
  
  tiempointegrado+=TimeStep;

  c1x+=p1x*TimeStep;
  c1y+=p1y*TimeStep;

  c2x+=p2x*TimeStep;
  c2y+=p2y*TimeStep;  

  glLineWidth(3.0) ;
  glColor3f( 0.2f, 0.0f, 0.0f );
  DrawCircle(0.0,0.0, 0.999, 50); 
  

  glLineWidth(1.0) ;
  glColor3f( 0.45f, 0.1f, 0.1f );
  DrawDisk(c1x, c1y, r1, 50);


  glColor3f( 0.3f, 0.12f, 0.6f );
  DrawDisk(c2x, c2y, r2, 50);
 
  glColor3f( 0.5f, 0.5f, 0.5f );
  glBegin(GL_LINES);
  glVertex2f(0.0f, 0.0f); // origin of the line
  glVertex2f(1.0, 0); // ending point of the line
  glEnd( );
 
  glBegin(GL_LINES);
  glVertex2f(0.0f, 0.0f); // origin of the line
  glVertex2f(0.0, 1.0); // ending point of the line
  glEnd( );
 
 
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
  
  /************************************************/
  //Comienza ventana 2
  /************************************************/

  float xprima1, yprima1;
  float xprima2, yprima2;

  float sinrot, cosrot;
  
  anguloaparente+=velangularaparente*TimeStep;
 
  sinrot=sin(anguloaparente);
  cosrot=cos(anguloaparente);

  xprima1=c1x*cosrot+c1y*sinrot;
  yprima1=-c1x*sinrot+c1y*cosrot;

  //For making a nice plot of the trayectory
  if(xprima1!=0){
    cout<<xprima1<<"\t" << yprima1 <<endl;}
  
  xprima2=c2x*cosrot+c2y*sinrot;
  yprima2=-c2x*sinrot+c2y*cosrot;
  
  
  glutSetWindow(2);
  glClear( GL_COLOR_BUFFER_BIT );
  
  //Reset modelview matrix
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  glLineWidth(3.0) ;
  glColor3f( 0.2f, 0.0f, 0.0f );
  DrawCircle(0.0,0.0, 0.999, 50); 
  
  glColor3f( 0.0f, 0.0f, 0.0f );
  glBegin(GL_LINES);
  glVertex2f(0.0f, 0.0f); // origin of the line
  glVertex2f(cosrot, -sinrot); // ending point of the line
  glEnd( );
 
  glBegin(GL_LINES);
  glVertex2f(0.0f, 0.0f); // origin of the line
  glVertex2f(sinrot, cosrot); // ending point of the line
  glEnd( );
 

  glLineWidth(1.0) ;
  glColor3f( 0.45f, 0.1f, 0.1f );
  DrawDisk(xprima1, yprima1, r1, 50);

  glColor3f( 0.3f, 0.12f, 0.6f );
  DrawDisk(xprima2, yprima2, r2, 50);
 

  glutSwapBuffers();

};


void handleKeys( unsigned char key, int x, int y ){
  //If the user presses q
  
  //if( key == 'x' )glutLeaveMainLoop();
  
  //  if(GLUT_ACTION_ON_WINDOW_CLOSE)glutLeaveMainLoop();
  
  if( key == 't' ){
    trazo=!trazo;   
    };
  
 
};  
  

