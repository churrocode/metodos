#ifndef MATRIZBANDA_H
#define	MATRIZBANDA_H

#include <list>
#include <utility>
#include <vector>
typedef double num;
#define eps 10e-12
#define iguales(x, y) (- eps < x - y  && x -y < eps)

using namespace std;

class MatrizBanda {
    class Fila{
    public:
        list<pair<int, num> > noNulos;
        void sumarMultiploDeFila(const Fila& f1, num m);
        num get(const int j);
        void set(const int j, const num a); //a != 0, por favor!
    };
public:
    MatrizBanda(int n, int m, int p, int q);
    MatrizBanda(const MatrizBanda& orig);
    virtual ~MatrizBanda();
    num get(int i, int j);
    void set(int i, int j, num a);
    void sumarMultiploDeFila(int i1, int i2, num k);
    //operator[](int i, int j);
private:
    int n;
    int m;
    int p;
    int q;
    vector<Fila> filas;
};

#endif	/* MATRIZBANDA_H */
