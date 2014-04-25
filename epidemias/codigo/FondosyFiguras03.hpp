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

GLfloat gProjectionScale = 1.f;

//Color modes
//Trazar la cola del disco.
bool trazo=false;
bool cuadrados=false;

//Centros y velocidades de los discos
float c1x, c1y;

float r1;
float border=sqrt((float)animales)/2.0+0.5;

float *Centro2x, *Centro2y;

float * c2x;
float * c2y;


bool initGL()
{

  c2x= new float[animales];
  c2y= new float[animales];
  Centro2x= new float[animales];
  Centro2y= new float[animales];
  
  gProjectionScale = 1.0f;

  glutSetWindow(1);
  //Initialize Projection Matrix
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  
  glOrtho( -border, border, -border, border, 1.0, -1.0 );
  
  
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



void update(Animalculo &animal, Animalculo *manada)
{

  for(int i=0; i<animales; i++){
    if((dist(animal, manada[i])<2*animal.radio)&&(animal.enfermo)){
      manada[i].enfermo=true;
    }};
  
  
  for(int i=0; i<animales; i++){
    for(int j=i+1; j<animales; j++){

      if((dist(manada[j], manada[i])<2*animal.radio)&&(manada[i].enfermo)){
	manada[j].enfermo=true;}
      
      else if((dist(manada[j], manada[i])<2*animal.radio)&&(manada[j].enfermo)){
	manada[i].enfermo=true;}
    }
  }

  animal.caminar(r);
  c1x=animal.realx();
  c1y=animal.realy();
  r1=animal.radio*border;
  
  for(int i=0; i< animales; i++ ){
    manada[i].caminar(r);
    c2x[i]=manada[i].realx();
    c2y[i]=manada[i].realy();
    Centro2x[i]=manada[i].CornerX;
    Centro2y[i]=manada[i].CornerY;
  }
  

};


void render()
{ 
  glutSetWindow(1);
  //Clear color buffer
  glClear( GL_COLOR_BUFFER_BIT );

  //Reset modelview matrix
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  

  
  glLineWidth(1.0) ; 
  if(Animal1.enfermo){
    glColor3f( 0.75f, 0.1f, 0.1f );
  }else{
    glColor3f( 0.55f, 0.2f, 0.3f );
  }

  DrawDisk(c1x, c1y, r1, 15);

  
  for(int i=0; i<animales; i++){
    glLineWidth(1.0) ;
    if(Animal2[i].enfermo){
      glColor3f( 0.75f, 0.1f, 0.1f );
    }else{
      glColor3f( 0.55f, 0.2f, 0.3f );
  }
    DrawDisk(c2x[i], c2y[i], r1, 15);
  };
  
  if(cuadrados){
    glColor3f( 0.6f, 0.6f, 0.6f );  
    for(int i=0; i<animales; i++){
      glBegin(GL_LINE_LOOP);    
      glVertex2f(-0.5+Centro2x[i], -0.5+Centro2y[i]);//output vertex 
      glVertex2f(0.5+Centro2x[i], -0.5+Centro2y[i]);
      glVertex2f(0.5+Centro2x[i], 0.5+Centro2y[i]);
      glVertex2f(-0.5+Centro2x[i], 0.5+Centro2y[i]);
      glEnd();
    }
  } 

  //Territorio del animal enfermo original
  glColor3f( 0.6f, 0.0f, 0.1f );  
  glBegin(GL_LINE_LOOP);    
  glVertex2f(-0.5, -0.5);//output vertex 
  glVertex2f(0.5, -0.5);//output vertex 
  glVertex2f(0.5, 0.5);//output vertex 
  glVertex2f(-0.5, 0.5);//output vertex 
  glEnd();

  if( trazo ){
    glColor4f( 0.1f, 0.8f, 0.1f, 0.1f );
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
  
  
  if( key == 'c' ){
    cuadrados=!cuadrados;   
    };
 

};  
  

