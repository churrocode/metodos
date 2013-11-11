main: MatrizEsparsa.o utils.o factorizacionQR.o quadraticExtrapolation.o main.o
	g++ -o main MatrizEsparsa.o utils.o factorizacionQR.o quadraticExtrapolation.o main.o

MatrizEsparsa.o: MatrizEsparsa.cpp MatrizEsparsa.h
	g++ -c MatrizEsparsa.cpp

factorizacionQR.o: factorizacionQR.cpp factorizacionQR.h
	g++ -c factorizacionQR.cpp

quadraticExtrapolation.o: quadraticExtrapolation.cpp quadraticExtrapolation.h
	g++ -c quadraticExtrapolation.cpp

utils.o: utils.cpp utils.h
	g++ -c utils.cpp

main.o: main.cpp
	g++ -c main.cpp	
	
clean:
	rm main MatrizEsparsa.o main.o factorizacionQR.o quadraticExtrapolation.o utils.o
