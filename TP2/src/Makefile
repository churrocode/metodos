main: MatrizBanda.o main.o
	g++ -o main MatrizBanda.o main.o

MatrizBanda.o: MatrizBanda.cpp MatrizBanda.h
	g++ -c MatrizBanda.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm main MatrizBanda.o main.o