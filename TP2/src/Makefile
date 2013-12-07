main: MatrizBanda.o backwardSubstitution.o Puente.o Heuristica.o main.o
	g++ -ggdb -o main MatrizBanda.o backwardSubstitution.o Puente.o heuristica.o main.o

MatrizBanda.o: MatrizBanda.cpp MatrizBanda.h
	g++ -ggdb -c MatrizBanda.cpp

backwardSubstitution.o: backwardSubstitution.cpp backwardSubstitution.h
	g++ -ggdb -c backwardSubstitution.cpp

puente.o: Puente.cpp Puente.h
	g++ -ggdb -c Puente.cpp

Heuristica.o: heuristica.cpp heuristica.h
	g++ -ggdb -c heuristica.cpp

main.o: main.cpp
	g++ -ggdb -c main.cpp	

competencia: MatrizBanda.o backwardSubstitution.o Puente.o Heuristica.o competencia.o
	g++ -ggdb -o competencia MatrizBanda.o backwardSubstitution.o Puente.o heuristica.o competencia.o

competencia.o: competencia.cpp
	g++ -ggdb -c competencia.cpp

clean:
	rm main MatrizBanda.o main.o backwardSubstitution.o Puente.o heuristica.o competencia.o
