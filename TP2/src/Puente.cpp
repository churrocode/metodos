#include "Puente.h"
#include <list>
#include "backwardSubstitution.h"

#include <iostream>
using namespace std;

void Puente::generarMatriz() {
    //HAY QUE PUSHEAR POR ÍNDICE CRECIENTE SI USAMOS SETLAST!
    construirPuntas(n);
    if (n == 2) {
        //sin M de medio, compartiendo un link
        //matriz.agregarFila(2, (x2 : cos, x6 : -cos));
        matriz.setLast(2, 2, cos); matriz.setLast(2, 6, -cos);
        //matriz.agregarFila(3, (x2 : -sen, x4 : -1, x6: -sen));
        matriz.setLast(3, 2, -sen); matriz.setLast(3, 4, -1); matriz.setLast(3, 4, -sen);

        // matriz.agregarFila(4, (x3: 1, x5: -1));
        matriz.setLast(4, 3, 1); matriz.setLast(4, 5, -1);
        // matriz.agregarFila(5, (x4 : 1));
        matriz.setLast(5, 4, 1);
    } else {
        construirCentro(n);
        construirResto(n);
    }
}

void Puente::construirPuntas(const int n) {
    // m.agregarFila(0, (x0 : 1 (h0), x2 : -cos , x3 : -1));
    matriz.setLast(0, 0, 1); matriz.setLast(0, 2, -cos); matriz.setLast(0, 3, -1);
    // m.agregarFila(1, (x1 : -1 (v0), x2 : sen));
    matriz.setLast(1, 1, -1); matriz.setLast(1, 2, sen);

    int n4 = 4*n;
    // m.agregarFila(4*n-2, (x4n-2 : cos , x4n-3 : 1);
    matriz.setLast(n4-2, n4-3, 1); matriz.setLast(n4-2, n4-2, cos);
    // m.agregarFila(4n-1, (x4n-1 : -1 (v0), x4n-2 : sen));
    matriz.setLast(n4-1, n4-2, sen); matriz.setLast(n4-1, n4-1, -1);

    if (n > 2) {
        //junta 1
        // m.agregarFila(2, (x2: cos, x5: -1, x6: -cos));
        matriz.setLast(2, 2, cos); matriz.setLast(2, 5, -1); matriz.setLast(2, 6, -cos);
        // m.agregarFila(3, (x2: -sen, x4: -1, x6: -sen));
        matriz.setLast(3, 2, -sen); matriz.setLast(3, 4, -1); matriz.setLast(3, 6, -sen);

        //junta 2
        // m.agregarFila(4, (x3: +1, x7: -1));
        matriz.setLast(4, 3, 1); matriz.setLast(4, 7, -1);
        // m.agregarFila(5, (x4: 1));
        matriz.setLast(5, 4, 1);

        //simétrica de 1
        matriz.setLast(n4-4, n4-7, 1); matriz.setLast(n4-4, n4-3, -1);
        matriz.setLast(n4-3, n4-4, 1);

        //simétrica de 2
        matriz.setLast(n4-6, n4-6, cos); matriz.setLast(n4-6, n4-5, 1); matriz.setLast(n4-6, n4-2, -cos);
        matriz.setLast(n4-5, n4-6, -sen); matriz.setLast(n4-5, n4-4, -1); matriz.setLast(n4-5, n4-2, -sen);
    }
} 

void Puente::construirCentro(const int n) {
    //junta de arriba
    //m.agregarFila(2*n-2, (x2n-3: 1, x2n+3: -1));
    int n2 = 2*n;
    matriz.setLast(n2-2, n2-3, 1); matriz.setLast(n2-2, n2+3, -1);
    // m.agregarFila(2*n-1, (x2n:-1));
    matriz.setLast(n2-1, n2, -1);

    // junta de abajo
    // m.agregarFila(2*n, (x2n-1: 1, x2n-2: cos, x2n+2: -cos, x2n+1: -1));
    matriz.setLast(n2, n2-2, cos); matriz.setLast(n2, n2-1, 1); matriz.setLast(n2, n2+1, -1); matriz.setLast(n2, n2+2, -cos);
    // m.agregarFila(2*n+1, (x2n: 1, x2n-2: sen, x2n+2: sen));
    matriz.setLast(n2+1, n2-2, sen); matriz.setLast(n2+1, n2, 1); matriz.setLast(n2+1, n2+2, sen);
}

void Puente::construirResto(int n) {
    for (int palito = 2; palito < n/2; ++palito) {
        int p4 = 4*palito;
        //mitad izq, arriba
        // m.agregarFila(4p -2, (x4p-3: 1, x4p+1: -1, x4p+2: -cos));
        matriz.setLast(p4-2, p4-3, 1); matriz.setLast(p4-2, p4+1, -1); matriz.setLast(p4-2, p4+2, -cos);
        // m.agregarFila(4p -1, (x4p: -1, x4p+2: -sen));
        matriz.setLast(p4-1, p4, -1); matriz.setLast(p4-1, p4+2, -sen);

        //mitad izq, abajo
        // m.agregarFila(4p, (x4p-1: 1, x4p+3: -1, x4p-2: cos));
        matriz.setLast(p4, p4-2, cos); matriz.setLast(p4, p4-1, 1); matriz.setLast(p4, p4+3, -1);
        // m.agregarFila(4p+1, (x4p: 1, x4p-2: sen));
        matriz.setLast(p4+1, p4-2, sen); matriz.setLast(p4+1, p4, 1);

        int nmp4 = 4*(n-palito);
        //mitad der, arriba
        // m.agregarFila(4nmp, x4nmp+3: -1, x4nmp-1: 1, x4nmp-2: +cos);
        matriz.setLast(nmp4, nmp4-2, cos); matriz.setLast(nmp4, nmp4-1, 1); matriz.setLast(nmp4, nmp4+3, -1);
        // m.agregarFila(4nmp-1, (x4nmp: -1, x4nmp-2: -sen));
        matriz.setLast(nmp4+1, nmp4-2, -sen); matriz.setLast(nmp4+1, nmp4, -1);
        //mitad der, abajo
        // m.agregarFila(4nmp-2, (x4nmp+1: -1, x4nmp-3: 1, x4nmp+2: -cos));
        matriz.setLast(nmp4-2, nmp4-3, 1); matriz.setLast(nmp4-2, nmp4+1, -1); matriz.setLast(nmp4-2, nmp4+2, -cos);
        // m.agregarFila(4nmp-1, (x4nmp: 1, x4nmp+2: sen));
        matriz.setLast(nmp4-1, nmp4, 1); matriz.setLast(nmp4-1, nmp4+2, sen);
    }
}

vector<num>* Puente::resolverPuente() {
    vector<num> *b = new std::vector<num>(4*n);
    (*b)[0] = 0; //hor
    (*b)[1] = 0; //vert
    for (int i = 2; i <= 2*n; ++i) {
        (*b)[2*(i-1)] = 0; //hor
        //cout << 2*(i-1) << " -> " << 0 << endl;
        (*b)[2*(i-1)+1] = ((i % 2 == 1) ? (-1*cargas[i/2 -1]) : 0); //vert
        //cout << 2*(i-1)+1 << " -> " << ((i % 2 == 1) ? (-1*cargas[i/2 -1]) : 0) << endl;
    }
    matriz.triangularConGauss(4, *b);
    vector<num>* sol = backwardSubstitution(matriz, *b);
    
    vector<num> verificar(4*n);
    //matriz.Axb(*sol, verificar);
    /*for (int i = 0; i < 4*n; ++i) {
        cout << verificar[i] << " vs " << (*b)[i] << endl;
    }*/
    
    return sol;
}

bool Puente::esSeguro() {
    double fuerza_max_absoluta = getMatriz().getFuerzaMax().first;
    cout << "EN PUENTE, " << "FMAX: " << getFMax() << " fuerza_max_absoluta: " << fuerza_max_absoluta << endl;
    return (fuerza_max_absoluta <= getFMax() || iguales(fuerza_max_absoluta,getFMax()));
}

double Puente::costo() {
    double costo = 0;
    costo += this->n * this->hip; //los n links oblicuos;
    costo += this->n + ((this->n > 2 ? this->n - 2 : 0)) * (this->span / this->n); //los links horizontales de abajo (n) + los de arriba (n-2, si existen)
    costo += this->h * (n-1);
    num fuerza_max_absoluta = getMatriz().getFuerzaMax().first; 
    return costo*fuerza_max_absoluta;
}

int Puente::junta(const int fuerza) {
    if (fuerza < 4* n) {
        switch (fuerza % 4) {
            case 0:
            case 1:
                return fuerza/2 + 1;
            case 2:
                if (fuerza < n/2) {
                    return fuerza/2 + 2;
                } else {
                    return fuerza/2;
                }
            case 3:
                return fuerza/2;
        }
    } else {
        return -1;
    }
    return 0; //así no se queja el compilador
}
