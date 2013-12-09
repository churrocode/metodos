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
    ifstream file;
    if (argc != 2) {
        cout << "leyendo datos de ../ejemplos/Ex1.in, puede pasar un archivo por parámetro.\n";
        file.open("../ejemplos/Ex1.in", ios::in);
    } else {
        file.open(argv[1], ios::in);
    }
    
    ofstream file_out;
    file_out.open("../mediciones/competencia.out", ios::out);

    double span,h,costoPilar,fMax;
    //while(file.eof() != 1){       CONSIDERAMOS SÓLAMENTE UN PUENTE POR ARCHIVO
        int n;
        file >> span;
        file >> h;
        file >> n;
        vector<double> cargas(n-1);
        //double suma_cargas = 0;
        for (int i = 0; i < n-1; ++i) {
            file >> cargas[i];
        }
        file >> costoPilar;
        file >> fMax;
        cout << "span = " << span << " h = " << h << " n = " << n << " costoPilar = " << costoPilar << " fMax = " << fMax << endl;
        
        Puente p(n, span, h, costoPilar, fMax, cargas);
        p.generarMatriz();
        pair<double, pair< vector<double>, vector<double> > > res_costo = costoTotal(p);
        double costo_total = res_costo.first;
        pair< vector<double>, vector<double> > pilares = res_costo.second;
        vector<double> posiciones_pilares = pilares.first;
        vector<double> costo_subestructuras = pilares.second;
        
        cout << "Costo total = " << costo_total << endl;
        cout << "Pilares en las posiciones: ";
        file_out << costo_total << endl;
        for (int i = 0; i < posiciones_pilares.size(); ++i) {
            cout << posiciones_pilares[i]<<", ";
            file_out << posiciones_pilares[i] << endl;
        }
        cout << endl;
        for (int i = 0; i < costo_subestructuras.size(); ++i) {
            cout << "costo subestrs: " << costo_subestructuras[i] << endl;
            file_out << costo_subestructuras[i] << endl;
        }
        
        file_out << endl;
            
    //}   
    file.close();
    file_out.close();
    
    return 0;
}
