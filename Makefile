lCXX = gcc
#CXX = icpc

#Spine
IGEN = -I/home/sdorsher -I/home/sdorsher/libconfig-1.5/install/include
ITNT = -I/home/sdorsher/tnt -I/home/sdorsher/jama -I/usr/local/packages/gsl-1.16-intel/lib
LCONF = -L/home/sdorsher/libconfig-1.5/execinstall/lib/ -lconfig++
ESRC = /home/sdorsher/scalar1deffectivesourceCurrent/scalar1deffectivesource
#LGSL = `pkg-config --libs gsl`
LGSL = -L/usr/local/packages/gsl-1.16-intel/include -lm


#Both
LCPP = -lstdc++
#FLGS = -g -lm -std=c++11 -O3 -p

#FLGS = -g -lm -std=c++11 -O3 -fopenmp -ftree-vectorize -ffast-math -fopt-info-vec-optimized-missed -Wall
FLGS = -g -lm -std=c++11 -O3
 
#FLGS = -g -lm -std=c++11 -O3 


#Steven's Mac
#IGEN = -I/Users/sdorsher/Documents/Diener -I/home/sdorsher
#ITNT = -I/home/sdorsher/tnt -I/Users/sdorsher/Documents/Diener/tnt -I/home/knarf/codes/dorsher/libtnt/libtnt-1.2.6/src/ -I /home/knarf/codes/dorsher/libjama/libjama-1.2.4/src
#LCONF = -L/Users/sdorsher/utils/lib/ -lconfig++
#ESRC = /Users/sdorsher/Documents/Diener/Scalar1DEffectiveSource/scalar1deffectivesource
LGSL=`pkg-config --libs gsl`


#LGSL = -L/usr/local/packages/gsl-1.16-intel/lib -lgsl -lgslcblas





#GridFunction, VectorGridFunction, and TwoDVectorGridFunction lines are missing

dg1D : main.o ReferenceElement.o Grid.o Evolution.o globals.o ConfigParams.o DiffEq.o CharacteristicFlux.o Modes.o Coordinates.o namespaces.o numerics.o WriteFile.o EllipticalOrbit.o CircularOrbit.o WorldTube.o Orbit.o
	$(CXX) $(FLGS) $(ITNT) $(IGEN) -I$(ESRC) main.o  ReferenceElement.o Grid.o Evolution.o globals.o ConfigParams.o DiffEq.o CharacteristicFlux.o Modes.o Coordinates.o namespaces.o  $(ESRC)/EffectiveSource-acceleration.o $(ESRC)/WignerDMatrix.o numerics.o WriteFile.o EllipticalOrbit.o CircularOrbit.o WorldTube.o Orbit.o $(LCONF) $(LGSL) $(LCPP) -o dg1D
	uname | grep -q Linux || install_name_tool -change /usr/local/lib/libconfig++.9.dylib $(HOME)/utils/lib/libconfig++.9.dylib dg1D

main.o: main.cpp GridFunction.h GridFunction.tpp ReferenceElement.h VectorGridFunction.h VectorGridFunction.tpp TwoDVectorGridFunction.h TwoDVectorGridFunction.tpp Evolution.h DiffEq.h TNT2.h ConfigParams.h Modes.h Coordinates.h namespaces.h Orbit.h numerics.h WriteFile.h vecMatrixTools.h Coordinates.h EllipticalOrbit.h CircularOrbit.h WorldTube.h CharacteristicFlux.h OutputIndices.h
	$(CXX) $(FLGS) $(ITNT) $(IGEN) -I$(ESRC) $(LCONF) -c main.cpp


Orbit.o: Orbit.cpp Orbit.h globals.h ConfigParams.h
	$(CXX) $(FLGS) $(ITNT) $(IGEN) -I$(ESRC) -c Orbit.cpp

EllipticalOrbit.o: EllipticalOrbit.cpp EllipticalOrbit.h namespaces.h ConfigParams.h Orbit.h Coordinates.h
	$(CXX) $(FLGS) $(ITNT) $(IGEN) -I$(ESRC) -c EllipticalOrbit.cpp

CircularOrbit.o: CircularOrbit.cpp CircularOrbit.h namespaces.h ConfigParams.h Orbit.h
	$(CXX) $(FLGS) $(ITNT) $(IGEN) -I$(ESRC) -c CircularOrbit.cpp

Coordinates.o: Coordinates.cpp Coordinates.h globals.h ConfigParams.h Grid.h
	$(CXX) $(FLGS) $(ITNT) $(IGEN) -I$(ESRC) -c Coordinates.cpp

WorldTube.o: WorldTube.cpp WorldTube.h Coordinates.h globals.h ConfigParams.h GridFunction.h Grid.h namespaces.h
	$(CXX) $(FLGS) $(ITNT) $(IGEN) -I$(ESRC) -c WorldTube.cpp

ReferenceElement.o: ReferenceElement.cpp ReferenceElement.h globals.h TNT2.h
	$(CXX) $(FLGS) $(ITNT) $(IGEN) -I$(ESRC) -c ReferenceElement.cpp

#GridFunction.o: GridFunction.cpp GridFunction.h TNT2.h
#	$(CXX) $(FLGS) $(ITNT) $(IGEN) -I$(ESRC) -c GridFunction.cpp

#VectorGridFunction.o: VectorGridFunction.cpp VectorGridFunction.h GridFunction.h TNT2.h
#	$(CXX) $(FLGS) $(ITNT) $(IGEN) -c VectorGridFunction.cpp

Grid.o: Grid.cpp Grid.h ReferenceElement.h GridFunction.h GridFunction.tpp TNT2.h DiffEq.h CharacteristicFlux.h TwoDVectorGridFunction.h TwoDVectorGridFunction.tpp  VectorGridFunction.h VectorGridFunction.tpp namespaces.h OutputIndices.h
	$(CXX) $(FLGS) $(ITNT) $(IGEN) -I$(ESRC) -c Grid.cpp

Evolution.o: Evolution.cpp Evolution.h GridFunction.h GridFunction.tpp TwoDVectorGridFunction.h TwoDVectorGridFunction.tpp ReferenceElement.h TNT2.h ConfigParams.h DiffEq.h WorldTube.h Orbit.h CircularOrbit.h EllipticalOrbit.h Coordinates.h Modes.h WriteFile.h
	$(CXX) $(FLGS) $(ITNT) $(IGEN) -I$(ESRC) $(LCONF) -c Evolution.cpp

globals.o: globals.cpp globals.h
	$(CXX) $(FLGS) $(ITNT) $(IGEN) -I$(ESRC) -c globals.cpp

ConfigParams.o: ConfigParams.cpp ConfigParams.h
	$(CXX) $(FLGS) $(ITNT) $(IGEN) -I$(ESRC) $(LCONF) -c ConfigParams.cpp

DiffEq.o: DiffEq.cpp DiffEq.h ConfigParams.h Grid.h CharacteristicFlux.h VectorGridFunction.h VectorGridFunction.tpp Modes.h Coordinates.h vecMatrixTools.h TwoDVectorGridFunction.h $(ESRC)/EffectiveSource-acceleration.h namespaces.h Orbit.h EllipticalOrbit.h CircularOrbit.h WorldTube.h OutputIndices.h numerics.h 
	$(CXX) $(FLGS) $(ITNT) $(IGEN) -I$(ESRC) $(LCONF) -c DiffEq.cpp

CharacteristicFlux.o: CharacteristicFlux.cpp CharacteristicFlux.h TNT2.h globals.h ConfigParams.h
	$(CXX) $(FLGS) $(ITNT) $(IGEN) -I$(ESRC) -c CharacteristicFlux.cpp


Modes.o: Modes.cpp Modes.h TwoDVectorGridFunction.h ConfigParams.h namespaces.h TwoDVectorGridFunction.tpp ConfigParams.h Orbit.h EllipticalOrbit.h CircularOrbit.h
	$(CXX) $(FLGS) $(ITNT) $(IGEN) -I$(ESRC) -c Modes.cpp

namespaces.o: namespaces.cpp namespaces.h
	$(CXX) $(FLGS) $(ITNT) $(IGEN) -I$(ESRC) -c namespaces.cpp

numerics.o: numerics.cpp numerics.h 
	$(CXX) $(FLGS) $(ITNT) $(IGEN) -I$(ESRC) -c numerics.cpp


WriteFile.o: WriteFile.cpp WriteFile.h TwoDVectorGridFunction.h Grid.h DiffEq.h Orbit.h namespaces.h EllipticalOrbit.h CircularOrbit.h
	$(CXX) $(FLGS) $(ITNT) $(IGEN) -I$(ESRC) -c WriteFile.cpp

clean:
	rm -f *.o dg1D
