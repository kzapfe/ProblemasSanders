##Lets learn how to do proper makefiles
## Si el TARGET no coincide con el nombre del archivero creado
## fuerzas a make a hacerlo siempre si no tiene dependencias!
## Usefull for huevones who dont list dependencias.


Test01.x: Disco01.hpp Testeadiscos01.cpp 
	g++ Testeadiscos01.cpp -o DosDiscosTest01.x

OneDisks01.x: Disco01.hpp UnDiscosBillar01.cpp tiemposchoque01.hpp
	g++ UnDiscosBillar01.cpp -o OneDisks01.x

TwoDisks01.x:  Disco01.hpp DosDiscosBillar01.cpp tiemposchoque01.hpp interaccion01.hpp 
	g++ DosDiscosBillar01.cpp -o TwoDisks01.x


##------------------------------------------------------
## Animaciones

LIBSOPENGL=-lGL -lGLU -lglut
FUENTESCOM=DosDiscosDinamica.hpp Disco01.hpp interaccion01.hpp tiemposchoque01.hpp
FUENTESGL=LUtil02.hpp LOpenGL.h circuloopengl.hpp

test:
	g++ $(LIBSOPENGL) DosDiscosAnimados01.cpp  -o anime01.x

DosDiscos02.x: $(FUENTESCOM) DosDiscosBillar02.cpp
	g++ DosDiscosBillar02.cpp -o DosDiscos02.x

Anime02.x: $(FUENTESCOM) $(FUENTESGL)  DosDiscosAnimados02.cpp VariablesGlobales01.hpp 
	g++ $(LIBSOPENGL) DosDiscosAnimados02.cpp -o Anime02.x

