#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "MatrizBanda.h"
#include "backwardSubstitution.h"
#include "Puente.h"
#include "heuristica.h"

#define PAP(x) (cout << "POR AQUI PASE " << x << endl)

using namespace std;
/*
void printMatriz(MatrizBanda& m);
void probarLasFilas();
void testGauss();
MatrizBanda generarMatriz(double span, double h, int n, vector<double>& cargas);*/

int main(int argc, char** argv) {
    if (argc != 2) {
        return 0;
    }
    ifstream file;
    file.open(argv[1], ios::in);
    //file.open("../ejemplos/Ex1.in", ios::in);
    
    ofstream file_out;
    file_out.open("../mediciones/competencia.out", ios::out);

    double span,h,costoPilar,fMax;
    while(file.eof() != 1){
        int n;
        file >> span;
        file >> h;
        file >> n;
        vector<double> cargas(n-1);
        double suma_cargas = 0;
        for (int i = 0; i < n-1; ++i) {
            file >> cargas[i];
        }
        file >> costoPilar;
        file >> fMax;
        cout << "span = " << span << " h = " << h << " n = " << n << " costoPilar = " << costoPilar << " fMax = " << fMax << endl;
        
        Puente p(n, span, h, costoPilar, fMax, cargas);
        p.generarMatriz();
        pair<double, pair< vector<double>, vector<double> > > res_costo = costoTotal(p);
        costo_total = res_costo.first;
        pilares = res_costo.second;
        posiciones_pilares = pilares.first;
        costo_subestructuras = pilares.second;
        
        cout << "Costo total = " << costo_total << endl;

        file_out << costo_total << endl;
        for (int i = 0; i < posiciones_pilares.long()-1; ++i) {
            file >> posiciones_pilares[i];
        }
        for (int i = 0; i < costo_subestructuras.long()-1; ++i) {
            file >> costo_subestructuras[i];
        }
        
        file_out << endl;
            
    }   
    file.close();
    file_out.close();
    
    return 0;
}
