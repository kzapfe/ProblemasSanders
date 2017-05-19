//Variables de AD HOVUM con librerias tambor.


#include <iostream>
#include <fstream>
#include <armadillo>
#include <math.h>
#include "Disco01.hpp"


//ULTRA GLOBAL OBJECTS
//SON TAN TAN ULTRA GLOBAL QUE SON TANTO PARA LA NUMERICA COMO PARA LA ANIMACION.
// Y deben funcionar para todos los tipos de discos.

const double tolerancia=2.0e-16;
const double tiempomax=66666.0;
const int colisionesmax=4000; //asi es suficiente
//const int colisionesmax=16000; //rayando en demasidoconst double widthmedia=0.5, heightmedia=0.5;
const double widthmedia=0.75, heightmedia=0.5;
const double radiomax=(widthmedia+heightmedia)-sqrt(2*widthmedia*heightmedia);
const double radiomaforhop=0.5;
const double Energia=1.00;






a
