#include <cstdlib>
#include <iostream>

#include "MatrizBanda.h"
#include "backwardSubstitution.h"

using namespace std;


void printMatriz(MatrizBanda& m);
void probarLasFilas();
void testGauss();

int main(int argc, char** argv) {
    
    cout << "MAIN CORRIENDO" << endl;

  //  probarLasFilas();
    //testGauss();
    testBackwardSubstitution();
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

