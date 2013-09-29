#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

#include "MatrizBanda.h"
#include "backwardSubstitution.h"

using namespace std;


void printMatriz(MatrizBanda& m);
void probarLasFilas();
void testGauss();
MatrizBanda generarMatriz(double span, double h, int n, vector<double>& cargas);

int main(int argc, char** argv) {
    if (argc != 2)
    	printf("Se espera un único parámtro con el nombre del archivo con los datos del problema en el formato definido por la Cátedra.\n");
    ifstream file;
    file.open(argv[1], ios::in);
    double span,h;
    int n;
    file >> span;
    file >> h;
    file >> n;
    vector<double> cargas(n-1);
    for (int i = 0; i < n-1; ++i) {
    	file >> cargas[i];
    }
    double costoPilar, fMax;
    file >> costoPilar;
    file >> fMax;
    file.close();

    cout << "MAIN CORRIENDO" << endl;

  //  probarLasFilas();
    testGauss();
  //  testBackwardSubstitution();
    
    return 0;
}

void testGauss(){
    cout << "Test Gauss" << endl;
    MatrizBanda m(4, 4);
    printMatriz(m);
    
    m.set(0,0,1);
    m.set(0,1,2);
    m.set(0,2,3);
    m.set(0,3,4);
    m.set(1,0,1);
    m.set(1,1,4);
    m.set(1,2,9);
    m.set(1,3,16);
    m.set(2,0,1);
    m.set(2,1,8);
    m.set(2,2,27);
    m.set(2,3,64);
    m.set(3,0,1);
    m.set(3,1,16);
    m.set(3,2,81);
    m.set(3,3,256);
    
    vector<num> b;
    b.push_back(2);
    b.push_back(10);
    b.push_back(44);
    b.push_back(190);

    m.triangularConGauss(3, 3, b);
    
    printMatriz(m);
    cout << "b triangulada = " << b[0] << ' ' << b[1] << ' ' << b[2] << ' ' << b[3] << endl;
    
    vector<num>* x = backwardSubstitution(m, b, 1, 4);
    
    
    cout << "x = " << (*x)[0] << ' ' << (*x)[1] << ' ' << (*x)[2] << ' ' << (*x)[3] << endl;
}

void probarLasFilas() {
	MatrizBanda m(10, 10);
	m.set(2,3,2);
	m.set(2,5,4);
	m.set(2,7,6);
	m.set(3,1,3);
	m.set(3,2,4);
	m.set(3,5,-6);
	m.set(3,8,9);
	printMatriz(m);
	m.sumarMultiploDeFila(3, 2, 1.5);
	printMatriz(m);
	m.intercambiarFilas(3, 1);
	printMatriz(m);
	m.intercambiarFilas(1,5);
	printMatriz(m);
	m.intercambiarFilas(5,2);
	printMatriz(m);
	// cout << m.get(0,0)<< endl;
	// cout << m.getDim().first << " x " << m.getDim().second << ' ' << m.getN() << " x " << m.getM()<< endl;
}

void printMatriz(MatrizBanda& m) {
	for (int i = 0; i < m.getDim().first ; ++i) {
		for (int j = 0; j < m.getDim().second ; ++j) {
			cout << m.get(i,j) << " "; //get(i,j) sólo acá!
		}
		cout << endl;
	}
	cout << endl;
}
/*
MatrizBanda generarMatriz(double span, double h, int n, vector<double>& cargas) {
	MatrizBanda matriz(4*n, 4*n);

	//LA LISTA TIENE QUE ESTAR ORDENADA POR ÍNDICE!!!!

	construirPuntas(matriz, n);
	if (n == 2) {
		//sin M de medio, compartiendo un link
		matriz.agregarFila(2, (x2 : cos, x6 : -cos));
		matriz.agregarFila(3, (x2 : -sen, x4 : -1, x6: -sen));

		matriz.agregarFila(4, (x3: 1, x5: -1));
		matriz.agregarFila(5, (x4 : 1));
	} else {
		construirCentro(matriz, n);
		construirResto(matriz, n);
	}

	void construirPuntas(MatrizBanda& m, int n) {
		m.agregarFila(0, (x0 : 1 (h0), x2 : -cos , x3 : -1));
		m.agregarFila(1, (x1 : -1 (v0), x2 : sen));

		m.agregarFila(4*n-2, (x4n-2 : cos , x4n-3 : 1);
		m.agregarFila(4*n-1, (x4n-1 : -1 (v0), x4n-2 : sen));

		if (n > 2) {
			m.agregarFila(2, (x2: cos, x5: -1, x6: -cos));
			m.agregarFila(3, (x2: -cos, x4: -1, x6: -sen));

			m.agregarFila(4, (x3: +1, x7: -1));
			m.agregarFila(5, (x4: 1));

			m.agregarFila(4*n-6, (x4n-3: -1, x4n-7: 1));
			m.agregarFila(4*n-5, ((x4n-4: 1)));

			m.agregarFila(4*n-4, (x4n-2: -cos, x4n-5: 1, x4n-6: cos));
			m.agregarFila(4*n-3 ) // ?? 
		}
	}

	void construirCentro(MatrizBanda& m, int n) {
		m.agregarFila(2*n-2, (x2n-3: 1, x2n+3: -1));
		m.agregarFila(2*n-1, (x2n:-1));

		m.agregarFila(2*n, (x2n-1: 1, x2n-2: cos, x2n+2: -cos, x2n+1: -1));
		m.agregarFila(2*n+1, (x2n: 1, x2n-2: sen, x2n+2: sen));
	}

	void construirResto(MatrizBanda& m, int n) {
		for (int palito = 2; palito < n/2; ++palito) {
			int 4p = 4*palito;
			//mitad izq, arriba
			m.agregarFila(4p -2, (x4p-3: 1, x4p+1: -1, x4p+2: -cos));
			m.agregarFila(4p -1, (x4p: -1, x4p+2: -sen));
			//mitad izq, abajo
			m.agregarFila(4p, (x4p-1: 1, x4p+3: -1, x4p-2: cos));
			m.agregarFila(4p+1, (x4p: 1, x4p-2: sen));

			int 4nmp = 4(n-palito);
			//mitad der, arriba
			m.agregarFila(4nmp, x4nmp+3: -1, x4nmp-1: 1, x4nmp-2: +cos);
			m.agregarFila(4nmp-1, (x4nmp: -1, x4nmp-2: -sen));
			//mitad der, abajo
			m.agregarFila(4nmp-2, (x4nmp+1: -1, x4nmp-3: 1, x4nmp+2: -cos));
			m.agregarFila(4nmp-1, (x4nmp: 1, x4nmp+2: sen));
		}
	}






}
*/
