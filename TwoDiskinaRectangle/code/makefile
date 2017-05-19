##Lets learn how to do proper makefiles
## Si el TARGET no coincide con el nombre del archivero creado
## fuerzas a make a hacerlo siempre si no tiene dependencias!
## Usefull for huevones who dont list dependencias.

##------------------------------------------------------
## Animaciones

LIBSGEN=-larmadillo
LIBSOPENGL=-lGL -lGLU -lglut
FUENTESCOM=DosDiscosDinamica.hpp Disco01.hpp interaccion01.hpp tiemposchoque01.hpp 
FUENTESCOMPARA=RandomConditions01.hpp VariablesGlobalesParalel01.hpp
FUENTESGL=FondosyFiguras01.hpp LOpenGL.h  circuloopengl.hpp 

# Recuerda que para hacer bien makefiles, 
#las variables de fuentes generales las debes de poner al final
# La primera fuente debe ser la fuente que le quieras pasar al compilador o equivalente


Test01.x:  Prueba01.cpp VariablesGlobales01.hpp $(FUENTESCOM)
	g++ $(LIBSGEN) Prueba01.cpp -o Test01.x
#No compila, no variables y  *.dat's

Animacion01.x:  Animado01.cpp VariablesGlobales01.hpp $(FUENTESCOM) $(FUENTESGL)
	g++ $(LIBSGEN) $(LIBSOPENGL) Animado01.cpp -o Animacion01.x
#falta freeglut al parecer

Tiempos01.x:  CalculaTiempos01.cpp VariablesGlobales01.hpp $(FUENTESCOM)
	g++ $(LIBSGEN) -lgsl  CalculaTiempos01.cpp -o Tiempos01.x
# no compila. Hay algo mal con gsl_rnd

TiemposWithRandom01.x:  CalculaTiempos02.cpp RandomConditions01.hpp VariablesGlobales01.hpp $(FUENTESCOM)
	g++ $(LIBSGEN) -lgsl CalculaTiempos02.cpp -o TiemposWithRandom01.x
#compila bien


CTParalel01.x:  CalculaTiemposParalel01.cpp  $(FUENTESCOM) $(FUENTESCOMPARA)
	g++ $(LIBSGEN) -lgsl -fopenmp CalculaTiemposParalel01.cpp -o CTParalel01.x


CTParalel02.x:  CalculaTiemposParalel02.cpp  $(FUENTESCOM) $(FUENTESCOMPARA)
	g++ $(LIBSGEN) -lgsl -fopenmp $< -o $@
#compila bien

Liapunov01.x: Liapunov01.cpp DinamicaTangente01.hpp  $(FUENTESCOM) $(FUENTESCOMPARA)
	g++ $(LIBSGEN) -lgsl -fopenmp Liapunov01.cpp -o Liapunov01.x
#compila bien

## Codigos Paralelizados con openmp
PrimerChoqueParalel01.x:  CalculaTiemposParalel02.cpp $(FUENTESCOM) $(FUENTESCOMPARA)
	g++ $(LIBSGEN) -lgsl -fopenmp $< -o $@
#Compila

VolumenParalel01.x: FraccionVolumenProhibidaParalel01.cpp $(FUENTESCOM) $(FUENTESCOMPARA)
	g++ $(LIBSGEN) -lgsl -fopenmp $< -o $@	


AreaParalel01.x: FraccionAreaParalel01.cpp $(FUENTESCOM) $(FUENTESCOMPARA)
	g++ $(LIBSGEN) -lgsl -fopenmp $< -o $@	



