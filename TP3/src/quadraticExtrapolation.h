#include <vector>
#include <list>
#include <iostream>

class MatrizEsparsa;

typedef double num;

using namespace std;

vector<num> quadraticExtrapolation(vector<num>& xk3, vector<num>& xk2, vector<num>& xk1, vector<num>& xk);

void imprimirVector(const vector<num>& v);

void armarMatriz(MatrizEsparsa& mt, list< vector<num> >& datos);