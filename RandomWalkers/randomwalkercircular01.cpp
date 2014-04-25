/* programa que hace un random 
   que inventa cualquier direccion y una distancia aleatorea */

/* rand example: guess the number */
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>       /* cos sen */
#include <iostream>  
#include <fstream>  


using namespace std;

int main ()
{
  
  float paso;
  float dire;
  const int  imax=9000;
  float equis=0, ye=0;
  const float pi=3.1415926; 
  ofstream datos;
  datos.open("CircularWalker01.dat");
    
  /* initialize random seed: */
  srand (time(NULL));

  for(int i=0;i<imax; i++){
    paso=(float)rand()/(float)RAND_MAX;
    dire=(float)rand()/(float)RAND_MAX*2.0*pi;
    equis+=paso*cos(dire);
    ye+=paso*sin(dire);

    datos<<equis<<"\t"<<ye<<endl;    
  };

  cout<<endl;
  cout<<"criptic walker."<<endl;
  

  return 0;

}
