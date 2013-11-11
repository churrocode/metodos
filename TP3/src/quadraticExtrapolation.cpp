#include "quadraticExtrapolation.h"
#include "MatrizEsparsa.h"
#include "utils.h"
//#include "factorizacionQR.h"


void imprimirVector(const vector<num>& v) {
	cout << "[ ";
	for(int i = 0; i < v.size(); ++i) {
		cout << v[i];
		(i + 1 >= v.size()) ? cout << " ]" : cout << " ";
	}
}

void armarMatriz(MatrizEsparsa& mt, list< vector<num> >& datos) {
	int i = 0;
	for(list< vector<num> >::const_iterator it = datos.begin(); it != datos.end(); ++it) {
		auto vector<num> v = *it;
		for(int j = 0; j < v.size(); ++j) {
			if(v[j] != 0) {
				mt.set(i,j,v[j]);
			}
		}
		++i;
	}
}

vector<num> quadraticExtrapolation(vector<num>& xk3, vector<num>& xk2, vector<num>& xk1, vector<num>& xk) {
	//vector<num> vector_resultante(xk3.size());
	vector<num> yk2,yk1,yk;
	yk2 = restarVectores(xk2,xk3);
	yk1 = restarVectores(xk1,xk3);
	yk = restarVectores(xk,xk3);
	
	MatrizEsparsa Y(xk3.size(),2);
	list< vector<num> > elementos_matriz;
	elementos_matriz.push_back(yk2); elementos_matriz.push_back(yk1);
	armarMatriz(Y,elementos_matriz);
	Y.printMatriz();

	num gamma_0, gamma_1, gamma_2, gamma_3 = 1.0;
	num beta_0, beta_1, beta_2;

	MatrizEsparsa* Q; //= givensDosColumnas(Y);
	vectorNegado(yk); // -yk
	vector<num> b = Q->multPorVector(yk,true);
	vector<num> gammas_resultantes = backwardSubstitution(Y,b);
	gamma_1 = gammas_resultantes[0];
	gamma_2 = gammas_resultantes[1];
	gamma_0 = -(gamma_1+gamma_2+gamma_3);

	beta_0 = gamma_1 + gamma_2 + gamma_3;
	beta_1 = gamma_2 + gamma_3;
	beta_2 = gamma_3;

	vector<num> v1 = multPorEscalar(xk2,beta_0);
	vector<num> v2 = multPorEscalar(xk1,beta_1);
	vector<num> v3 = multPorEscalar(xk,beta_2);
	v1 = sumarVectores(v1,v2);
	v1 = sumarVectores(v1,v3);

	vector<num> vector_resultante = v1;

	return vector_resultante;
}