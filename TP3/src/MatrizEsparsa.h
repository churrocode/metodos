#ifndef MATRIZESPARSA_H
#define	MATRIZESPARSA_H

#include <list>
#include <utility>
#include <vector>
typedef double num;
#define eps 10e-16
#define iguales(x, y) ((- eps < x - y)  && (x - y < eps))
#define abs(x) (x >= 0 ? x : - x)
#define minimum(x,y) (x <= 0 ? x : y)
#define maximum(x,y) (x >= y ? x : y)

using namespace std;

class MatrizEsparsa {
    class Fila{
    public:
        list<pair<int, num> > noNulos;
        Fila() : noNulos() {};
        void sumarMultiploDeFila(const Fila& f1, num m);
        num get(const int j);
        void set(const int j, const num a); //a != 0, por favor!
        void setLast(const int j, const num a);
    };
public:
    MatrizEsparsa(int n, int m);
    // MatrizEsparsa(const MatrizBanda& orig);
    num get(const int i, const int j);
    num primeroDeLaFila(const int i);
    void set(const int i, const int j, const num a);
    void sumarMultiploDeFila(const int i1, const int i2, const num k); // Fi1 <- Fi1 + Fi2*k
    void intercambiarFilas(const int i1, const int i2);
    pair<int, int> getDim();
    int getDimFilas();
    int getDimCols();
    void printMatriz(bool soloNoNulos = false);
    const list< pair<int, num> >& getFila(const int i);
    void setLast(const int i, const int j, const num a);
    bool columnaDeCeros(int col);
private:
    int n;
    int m;
    vector<Fila> filas;
};

#endif	/* MATRIZESPARSA_H */
