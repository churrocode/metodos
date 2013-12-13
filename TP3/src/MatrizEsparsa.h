#ifndef MATRIZESPARSA_H
#define	MATRIZESPARSA_H

#include <list>
#include <utility>
#include <vector>
#define eps 10e-16
#define iguales(x, y) ((- eps < x - y)  && (x - y < eps))
#define abs(x) (x >= 0 ? x : - x)
#define minimum(x,y) (x <= 0 ? x : y)
#define maximum(x,y) (x >= y ? x : y)

typedef double num;

using namespace std;

class MatrizEsparsa {
    class Columna{
    public:
        list<pair<int, num> > noNulos;
        Columna() : noNulos() {};
        num get(const int i);
        void set(const int i, const num a); //a != 0, por favor!
        void setLast(const int i, const num a);
        list<pair<int, num> >* sliceColumna(int inicio, int fin);
    };
public:
    MatrizEsparsa(int n, int m);
    num get(const int i, const int j);
    void set(const int i, const int j, const num a);
    pair<int, int> getDim();
    int getDimColumnas();
    int getDimFilas();
    void printMatriz(bool soloNoNulos = false);
    const list< pair<int, num> >& getColumna(const int j);
    num norma_de_columna(int j, int i);
    vector<num> vector_columna(const int j);
    void truncar_columna(const int j, const int i);
    void estocastizar();
    num sumar_columna(const int j); 
    void multiplicar_vector(const vector<num>& v, vector<num>& res);

private:
    int n;
    int m;
    num proba;
    vector<Columna> columnas;
};

#endif	/* MATRIZESPARSA_H */
