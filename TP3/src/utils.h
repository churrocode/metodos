#include <vector>
#define minimum(x,y) (x <= 0 ? x : y)
typedef double num;
class MatrizEsparsa;
using namespace std;

vector<num> restarVectores(vector<num> &v1, vector<num> &v2);
vector<num> sumarVectores(vector<num> &v1, vector<num> &v2);
vector<num> multPorEscalar(vector<num> &v1, num escalar);
void vectorNegado(vector<num> &v);

vector<num> backwardSubstitution(MatrizEsparsa &mt, vector<num> &b);
