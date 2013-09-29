main: MatrizBanda.o backwardSubstitution.o Puente.o main.o
	g++ -o main MatrizBanda.o backwardSubstitution.o Puente.o main.o

MatrizBanda.o: MatrizBanda.cpp MatrizBanda.h
	g++ -c MatrizBanda.cpp

backwardSubstitution.o: backwardSubstitution.cpp backwardSubstitution.h
	g++ -c backwardSubstitution.cpp

puente.o: Puente.cpp Puente.h
	g++ -c Puente.cpp

main.o: main.cpp
	g++ -c main.cpp	


clean:
	rm main MatrizBanda.o main.o backwardSubstitution.o