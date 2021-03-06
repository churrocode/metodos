#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "MatrizBanda.h"
#include "backwardSubstitution.h"
#include "Puente.h"

#define PAP(x) (cout << "POR AQUI PASE " << x << endl)

using namespace std;

void printMatriz(MatrizBanda& m);
void probarLasFilas();
void testGauss();
MatrizBanda generarMatriz(double span, double h, int n, vector<double>& cargas);

int main(int argc, char** argv) {
    if (argc != 3 or ((*argv[2] != '0' and *argv[2] != '1'))) {
    	printf("Se esperan dos parámetros, el primero con el nombre del archivo y el segundo debe ser 0 si se mide span variable, 1 si se mide carga variable\n");
    }
    ifstream file;
    file.open(argv[1], ios::in);
    
    ofstream file_out;
    if (*argv[2] == '0') file_out.open("../mediciones/medicionesConSpanVariable.out", ios::out);
    else if (*argv[2] == '1') file_out.open("../mediciones/medicionesConCargaVariable.out", ios::out);

    double span,h,costoPilar,fMax;
    while(file.eof() != 1){
        //levantar los datos de un puente
        int n;
        file >> span;
        file >> h;
        file >> n;
        vector<double> cargas(n-1);
        for (int i = 0; i < n-1; ++i) {
            file >> cargas[i];
        }
        file >> costoPilar;
        file >> fMax;
        cout << "span = " << span << " h = " << h << " n = " << n << " costoPilar = " << costoPilar << " fMax = " << fMax << endl;
        
        //generar el sistema y resolverlo
        Puente p(n, span, h, costoPilar, fMax, cargas);
        p.generarMatriz();  
        vector<num>* sols = p.resolverPuente();

        // for (int i = 0; i< 4*n; ++i) {
        //     cout << 'F' << i+1 << ' ' << (*sols)[i] << endl;
        // }

        // CALCULO LA MAXIMA FUERZA EJERCIDA SOBRE UN LINK
        double max = abs((*sols)[0]);
        for (int i = 1; i < 4*n; ++i){
            if (abs((*sols)[i]) > max) max = abs((*sols)[i]); 
        }
        cout << "maxima = " << max << endl;

        if (*argv[2] == '0'){
            // SALIDA PARA SPAN VARIABLE
            // <span> <n> <FMax>
            file_out << span << ' ' << n << ' ' << max << endl;
        } else if (*argv[2] == '1') {
            // SALIDA PARA CARGA VARIABLE, con carga uniforme
            // <carga> <n> <FMax>
            file_out << cargas[0] << ' ' << n << ' ' << max << endl;
        }
            

    }   
    file.close();
    file_out.close();
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

    m.triangularConGauss(3, b);
    
    printMatriz(m);
    cout << "b triangulada = " << b[0] << ' ' << b[1] << ' ' << b[2] << ' ' << b[3] << endl;
    
    vector<num>* x = backwardSubstitution(m, b);
    
    
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
