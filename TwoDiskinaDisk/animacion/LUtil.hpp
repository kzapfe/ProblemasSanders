#include "LOpenGL.h"
#include "circuloopengl.hpp"

/*Me gusta todo mas en un solo archivo
//hpp que en uno h y otro cpp.  
//se me hace mucha mamada.
//Por supuesto que con tu convencion la documentacion queda menos clara.
// Pero para tus propositos es suficiente */

//Screen Constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int SCREEN_FPS = 60;

//Color modes
//Trazar la cola del disco.
bool trazo=false;


float centerx=0.00, centery=0.00;
float px=0.0010, py=0.0010;


bool initGL()
{
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //Vamos a usar las coordenadas naturales de OpenGL
    //Se parecen mas a la fisica que te gusta.
   
    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
  
    //Initialize clear color
    glClearColor( 0.4f, 0.4f, 0.4f, 0.25f );
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

void update()
{ /*Since for this demo all we have is a stationary quad, 
there's no real game logic to update.*/
  centerx+=px;
  centery+=py;

};


void render()
{ //Clear color buffer
  glClear( GL_COLOR_BUFFER_BIT );

  //Reset modelview matrix
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  

   //Render the quad
  
  glLineWidth(3.0) ;
  glColor3f( 0.7f, 0.1f, 0.3f );
  DrawCircle(0.0,0.0, 0.999, 50); 
  

  glLineWidth(1.0) ;
  glColor3f( 0.45f, 0.1f, 0.1f );
  DrawDisk(centerx, centery, 0.3, 50);


  if( trazo ){//Seguir la linea?
    glBegin(GL_LINE_LOOP); 
    glLineWidth(2.0) ;
    glColor3f( 0.1f, 0.9f, 0.3f );
    glVertex2f(centerx, centery);//output vertex 
    glEnd();
  };



  //Update screen
    glutSwapBuffers();

    /*At the end of our render() function, we update the screen 
      using glutSwapBuffers().*/


};


void handleKeys( unsigned char key, int x, int y ){
  //If the user presses q
  if( key == 't' )
    {
      //Toggle color mode
      if(trazo)
	{trazo=false;	  
	}else{
	trazo=true;
      };
    
    };
  
};  
  

