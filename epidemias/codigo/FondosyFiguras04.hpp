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
const float TimeStep=0.5f/SCREEN_FPS;


//Color modes
//Trazar la cola del disco.
bool trazo=false;
bool cuadrados=false;

//Centros y velocidades de los discos

float r1;
float border=(float)animalgridsize/2.0;

float *Centro2x, *Centro2y;

float * c2x;
float * c2y;


bool initGL()
{

  c2x= new float[animalgridsize*animalgridsize];
  c2y= new float[animalgridsize*animalgridsize];
  Centro2x= new float[animalgridsize*animalgridsize];
  Centro2y= new float[animalgridsize*animalgridsize];
  



  glutSetWindow(1);
  //Initialize Projection Matrix
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  double auxborder=border*territorialidad;
  
  glOrtho( -auxborder-0.5, auxborder, -auxborder-0.5, auxborder, 1.0, -1.0 );
  
  
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



void update( Animalculo *manada)

{
 
  

  for(int i=0; i<animalgridsize*animalgridsize; i++){
    for(int j=i+1; j<animalgridsize*animalgridsize; j++){

      if((dist(manada[j], manada[i])<2*raditodeinteraccion)&&(manada[i].enfermo)){
	manada[j].enfermo=true;}
      
      else if((dist(manada[j], manada[i])<2*raditodeinteraccion)&&(manada[j].enfermo)){
	manada[i].enfermo=true;}
    }
  }
 

  for(int i=0; i< animalgridsize; i++ ){
     for(int j=0; j< animalgridsize; j++ ){
       manada[i*animalgridsize+j].caminar(r);
       c2x[i*animalgridsize+j]=manada[i*animalgridsize+j].realx();
       c2y[i*animalgridsize+j]=manada[i*animalgridsize+j].realy();
       Centro2x[i*animalgridsize+j]=manada[i*animalgridsize+j].CornerX;
       Centro2y[i*animalgridsize+j]=manada[i*animalgridsize+j].CornerY;
     }
  }
  //Radio visual NO Es el radio real,
  r1=raditodeinteraccion;

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

  if(cuadrados){
   
    for(int i=0; i<animalgridsize*animalgridsize; i++){
      float azules;
      azules=(float)i/(animalgridsize*animalgridsize)*0.999;
      glColor3f( 0.2f, 0.0f+azules, 0.2f );  
      glBegin(GL_LINE_LOOP);    
      glVertex2f(-0.5+Centro2x[i], -0.5+Centro2y[i]);//output vertex 
      glVertex2f(0.5+Centro2x[i], -0.5+Centro2y[i]);
      glVertex2f(0.5+Centro2x[i], 0.5+Centro2y[i]);
      glVertex2f(-0.5+Centro2x[i], 0.5+Centro2y[i]);
      glEnd();
      if(Animal2[i].enfermo){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glColor4f( 0.8f, 0.0f, 0.0f, 0.5f );  	
	
	//Territorio enfermo
	glBegin(GL_TRIANGLE_FAN); 
	glVertex2f(-0.5+Centro2x[i], -0.5+Centro2y[i]);//output vertex 
	glVertex2f(0.5+Centro2x[i], -0.5+Centro2y[i]);
	glVertex2f(0.5+Centro2x[i], 0.5+Centro2y[i]);
	glVertex2f(-0.5+Centro2x[i], 0.5+Centro2y[i]);
	glEnd();
      }

    }
  } 

  
  for(int i=0; i<animalgridsize*animalgridsize; i++){
    glLineWidth(1.0) ;
    if(Animal2[i].enfermo){
      glColor3f( 0.75f, 0.1f, 0.1f );
    }else{
      glColor3f( 0.55f, 0.2f, 0.3f );
    }
    DrawDisk(c2x[i], c2y[i], r1, 15);
  };
  


  //Territorio del animal enfermo original
  glColor3f( 0.6f, 0.0f, 0.1f );  
  glBegin(GL_LINE_LOOP);    
  glVertex2f(-0.5+Centro2x[animalespecial], -0.5+Centro2y[animalespecial]);
  glVertex2f(0.5+Centro2x[animalespecial], -0.5+Centro2y[animalespecial]);
  glVertex2f(0.5+Centro2x[animalespecial], 0.5+Centro2y[animalespecial]);
  glVertex2f(-0.5+Centro2x[animalespecial], 0.5+Centro2y[animalespecial]);
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
  

