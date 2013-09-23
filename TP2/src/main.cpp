#include <cstdlib>
#include <iostream>

#include "MatrizBanda.h"

using namespace std;

float abs(float x){
    return x >= 0? x: -x;
}

void gauss(MatrizBanda m, int n, int m){
    for(int i = 1; i < m; i++){

        max = abs(m[i, i]);
        int fila_pivote = i;
        for(int j = i+1; j < n; j++){
            if (abs(m[j, i]) > max){
                max = abs(m[j, i]);
                fila_pivote = j;
            }
        }
        if(max == 0) return -1;
        if(fila_pivote != i){
        //    m.swapearFilas(i, fila_pivote)
        }
        float pivote = m[i, i];
        for(int j = i+1; j < n; j++){
            float multiplicador = m[j, i] / pivote;
        //    m.sumarMultiploDeFila(j, i, -1*pivote);
        }
    }
    
}

void printMatriz(MatrizBanda& m);
void probarLasFilas();

int main(int argc, char** argv) {
    
    cout << "MAIN CORRIENDO" << endl;

    probarLasFilas();
    
    return 0;
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

