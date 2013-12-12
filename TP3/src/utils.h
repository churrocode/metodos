#include <vector>
#include <iostream>

#define minimum(x,y) (x <= 0 ? x : y)
typedef double num;
class MatrizEsparsa;
using namespace std;

vector<num> restarVectores(vector<num> &v1, vector<num> &v2);
vector<num> sumarVectores(vector<num> &v1, vector<num> &v2);
vector<num> multPorEscalar(vector<num> &v1, num escalar);
void dividirPorEscalar(vector<num> &v, num escalar);
void vectorNegado(vector<num> &v);
num normaUno(vector<num>& el_vector);
num diferencia_normaUno(vector<num>& v1, vector<num>& v2);
void imprimirVector(const vector<num>& v);
vector<num> backwardSubstitution(MatrizEsparsa &mt, vector<num> &b);
pair<num,int> sacarMaximo(vector<num> &v);
num norma2(const vector<num>& v);
num producto_interno(const vector<num>& v1, const vector<num>& v2);
num normalizar_vector(vector<num>& v);
void escalar_vector(vector<num>& v, const num a);
