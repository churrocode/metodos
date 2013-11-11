main: MatrizEsparsa.o factorizacionQR.o main.o
	g++ -o main MatrizEsparsa.o factorizacionQR.o main.o

MatrizEsparsa.o: MatrizEsparsa.cpp MatrizEsparsa.h
	g++ -c MatrizEsparsa.cpp

factorizacionQR.o: factorizacionQR.cpp factorizacionQR.h
	g++ -c factorizacionQR.cpp

main.o: main.cpp
	g++ -c main.cpp	
	
clean:
	rm main MatrizEsparsa.o factorizacionQR.o main.o