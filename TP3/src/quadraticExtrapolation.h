#include <vector>
#include <list>

class MatrizEsparsa;

typedef double num;

using namespace std;

vector<num> quadraticExtrapolation(vector<num>& xk3, vector<num>& xk2, vector<num>& xk1, vector<num>& xk);
void armarMatriz(MatrizEsparsa& mt, const list< vector<num> >& datos);