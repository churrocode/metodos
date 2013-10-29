main: MatrizEsparsa.o main.o
	g++ -o main MatrizEsparsa.o main.o

MatrizEsparsa.o: MatrizEsparsa.cpp MatrizEsparsa.h
	g++ -c MatrizEsparsa.cpp

main.o: main.cpp
	g++ -c main.cpp	
	
clean:
	rm main MatrizEsparsa.o main.o