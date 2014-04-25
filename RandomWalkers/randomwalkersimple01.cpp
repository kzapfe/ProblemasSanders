/* programa que hace un random walker simple paso 1 */

/* rand example: guess the number */
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>  
#include <fstream>  


using namespace std;

int main ()
{
  
  int paso;
  const int  imax=9000;
  int equis=0, ye=0;
  ofstream datos;
  datos.open("Walker01.dat");
    
  /* initialize random seed: */
  srand (time(NULL));

  for(int i=0;i<imax; i++){
    paso=rand()%4;
    if(paso==0)equis++;
    if(paso==1)equis--;
    if(paso==2)ye++;
    if(paso==3)ye--;
    datos<<equis<<"\t"<<ye<<endl;    
  };

  cout<<endl;
  cout<<"criptic random message."<<endl;
  

  return 0;

}
