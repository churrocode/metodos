#ifndef MATRIZBANDA_H
#define	MATRIZBANDA_H

#include <list>
#include <pair>
typedef num double;
#define eps 10e-12
#define iguales(x, y) (- eps < x - y  && x -y < eps)

using namespace std;

class MatrizBanda {
    class Fila{
    public:
        list<pair<int, num>> noNulos;
        void sumarMultiploDeFila(const Fila& f1, num m);
        num get(const int j);
    };
public:
    MatrizBanda(int n, int m, int p, int q);
    MatrizBanda(const MatrizBanda& orig);
    virtual ~MatrizBanda();
    num get(i,j);
    void set(i,j, num);
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
