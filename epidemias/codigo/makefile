LIBSOPENGL=-lGL -lGLU -lglut
FUENTESGEN= LOpenGL.h circuloopengl.hpp Animal01.hpp
FUENTESGEN2= LOpenGL.h circuloopengl.hpp Animal02.hpp

Animacion01.x: AnimaTest01.cpp $(FUENTESGEN) FondosyFiguras01.hpp
	g++ $(LIBSOPENGL) -lgsl AnimaTest01.cpp -o Animacion01.x


Animacion02.x: Anima02.cpp $(FUENTESGEN) FondosyFiguras02.hpp
	g++ $(LIBSOPENGL) -lgsl Anima02.cpp -o Animacion02.x


Animacion03.x: Anima03.cpp $(FUENTESGEN) FondosyFiguras03.hpp
	g++ $(LIBSOPENGL) -lgsl Anima03.cpp -o Animacion03.x


Animacion04.x: Anima04.cpp $(FUENTESGEN) FondosyFiguras04.hpp
	g++ $(LIBSOPENGL) -lgsl Anima04.cpp -o Animacion04.x

AnimaUnTerritorio.x: animadosanimales01.cpp $(FUENTESGEN2) FondosDosAnimales01.hpp
	g++ $(LIBSOPENGL) -lgsl $< -o $@


## .............................................................
## Not animacions enimore.

PrimerContagio01.x: FirstEncounterandContagion01.cpp Animal02.hpp
	g++ -lgsl -fopenmp FirstEncounterandContagion01.cpp -o PrimerContagio01.x

Contagio3D01.x: FirstEncounter3D01.cpp Animal02.hpp
	g++  -lgsl -fopenmp $< -o $@

TestCaminante01.x: TestCaminante01.cpp CaminantesNoPlanos01.hpp 
	g++ -lgsl $< -o $@

TrueCilinder3d01.x: WalkOnCilinderAnulos3d01.cpp CaminantesNoPlanos01.hpp 
	g++ -lgsl $< -o $@

TrueCilinder3dParaTimes01.x: CilinderAnular3dParalel01.cpp CaminantesNoPlanos01.hpp 
	g++ -lgsl -fopenmp $< -o $@

TrueCilinder3dParaTimes02.x: CilinderAnular3dCeldas02.cpp CaminantesNoPlanos01.hpp 
	g++ -lgsl -fopenmp $< -o $@

Cono3D01.x: DinamicaCono3D01.cpp CaminantesNoPlanos01.hpp RandomInConus01.hpp
	g++ -lgsl -fopenmp $< -o $@	

Cono4D01.x: DinamicaCono4D01.cpp CaminantesNoPlanos01.hpp RandomInConus01.hpp
	g++ -lgsl -fopenmp $< -o $@	
