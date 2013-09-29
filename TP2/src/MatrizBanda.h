#ifndef MATRIZBANDA_H
#define	MATRIZBANDA_H

#include <list>
#include <utility>
#include <vector>
typedef double num;
#define eps 10e-12
#define iguales(x, y) ((- eps < x - y)  && (x - y < eps))
#define abs(x) (x >= 0 ? x : - x)
#define minimum(x,y) (x <= 0 ? x : y)

using namespace std;

class MatrizBanda {
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
    MatrizBanda(int n, int m);
    // MatrizBanda(const MatrizBanda& orig);
    virtual ~MatrizBanda();
    num get(const int i, const int j);
    num primeroDeLaFila(const int i);
    void set(const int i, const int j, const num a);
    void sumarMultiploDeFila(const int i1, const int i2, const num k); // Fi1 <- Fi1 + Fi2*k
    void intercambiarFilas(const int i1, const int i2);
    pair<int, int> getDim();
    void triangularConGauss();
    void printMatriz(bool soloNoNulos = false);
    MatrizBanda::Fila getFila(const int i) { return filas[i]; }
    // void reemplazarFila(const int i, list< pair<int,num> >& nuevaFila);
    void setLast(const int i, const int j, const num a);
private:
    int n;
    int m;
    vector<Fila> filas;
};

#endif	/* MATRIZBANDA_H */
