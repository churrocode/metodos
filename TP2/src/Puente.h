#ifndef PUENTE_H
#define	PUENTE_H

#include "MatrizBanda.h"
#include <vector>
#include <math.h>

using namespace std;

class Puente {
    int n;
    double span, h, costoPilar, fMax, cos, sen;
    vector<double> cargas;
    MatrizBanda matriz;

public:
    Puente(int n, double span, double h, double costoPilar, double fMax, vector<double>& cargas) 
        : n(n), span(span), h(h), costoPilar(costoPilar), fMax(fMax), cargas(cargas), matriz(4*n, 4*n) {
        cos = (span/n)/sqrt(h*h + (span*span)/(n*n));
        sen = h/sqrt(h*h + (span*span)/(n*n));
    };

    void generarMatriz();
    void resolverPuente();
    bool esSeguro();
    void printMatriz(bool soloNoNulos = false) {
        matriz.printMatriz(soloNoNulos);
    }
private:
    void construirPuntas(const int n);
    void construirCentro(const int n);
    void construirResto(const int n);
};

#endif	/* PUENTE_H */
