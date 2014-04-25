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
const double tiempomax=6666.0;
const int colisionesmax=100000;
const double widthmedia=0.5, heightmedia=0.5;
const double radiomax=(widthmedia+heightmedia)-sqrt(2*widthmedia*heightmedia);
const double Energia=1.00;






