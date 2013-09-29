#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

#include "MatrizBanda.h"
#include "backwardSubstitution.h"
#include "Puente.h"

using namespace std;


void printMatriz(MatrizBanda& m);
void probarLasFilas();
void testGauss();
MatrizBanda generarMatriz(double span, double h, int n, vector<double>& cargas);

int main(int argc, char** argv) {
    if (argc != 2) {
    	printf("Se espera un único parámtro con el nombre del archivo con los datos del problema en el formato definido por la Cátedra.\n");
    	return 0;
    }
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
	
	Puente p(n, span, h, costoPilar, fMax, cargas);
	p.generarMatriz();

    cout << "MAIN CORRIENDO" << endl;

  //  probarLasFilas();
    //testGauss();
    // testBackwardSubstitution();
    cout <<"asd"<<endl;
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
    
    m.triangularConGauss();
    printMatriz(m);
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

