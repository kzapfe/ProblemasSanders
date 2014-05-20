//Variables de AD HOVUM con librerias tambor.


#include <iostream>
#include <fstream>
#include <armadillo>
#include <math.h>
#include "Disco01.hpp"


//ULTRA GLOBAL OBJECTS
//SON TAN TAN ULTRA GLOBAL QUE SON TANTO PARA LA NUMERICA COMO PARA LA ANIMACION.

double Ultraradio=0.078;
Disco uno(0.25,0.25,-0.70710678, 0.70710678,Ultraradio);
Disco dos(-0.25,-0.2500,-1.0,0.0,Ultraradio);
const int colisionesmax=200;
double widthmedia=0.5, heightmedia=0.5;
//Variable auxiliar para las animaciones
// es el tiempo de choque cast en float. 
double tiempodechoque=0;
double tiempoentrecolisiones=0.0;
double tiempoentreeventosdisco1=0.0;
double tiempoentrebrincos=0.0;


