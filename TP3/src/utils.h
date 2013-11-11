#include <vector>
#include <iostream>

#define minimum(x,y) (x <= 0 ? x : y)
typedef double num;
class MatrizEsparsa;
using namespace std;

vector<num> restarVectores(vector<num> &v1, vector<num> &v2);
vector<num> sumarVectores(vector<num> &v1, vector<num> &v2);
vector<num> multPorEscalar(vector<num> &v1, num escalar);
void vectorNegado(vector<num> &v);
num normaUno(vector<num>& el_vector);
num diferencia_normaUno(vector<num>& v1, vector<num>& v2);
void imprimirVector(vector<num>& v);
vector<num> backwardSubstitution(MatrizEsparsa &mt, vector<num> &b);
