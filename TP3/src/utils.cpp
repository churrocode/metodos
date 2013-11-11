#include "utils.h"
#include "MatrizEsparsa.h"

vector<num> restarVectores(vector<num>& v1, vector<num>& v2) {
	vector<num> v = vector<num>(v1.size());
	for(int i = 0; i < v1.size(); ++i) {
		v[i] = v1[i] - v2[i];
	}

	return v;
}

void vectorNegado(vector<num>& v) {
	for(int i = 0; i < v.size(); ++i) {
		v[i] = -v[i];
	}
}

vector<num> sumarVectores(vector<num>& v1, vector<num>& v2) {
	vector<num> vector_resultante = vector<num>(v1.size());
	for(int i = 0; i < v1.size(); ++i) {
		vector_resultante[i] = v1[i] + v2[i];
	}

	return vector_resultante;
}

vector<num> multPorEscalar(vector<num>& v1, num escalar) {
	vector<num> vector_resultante = vector<num>(v1.size());
	for(int i = 0; i < v1.size(); ++i) {
		vector_resultante[i] = v1[i] * escalar;
	}

	return vector_resultante;
}

vector<num> backwardSubstitution(MatrizEsparsa& mt, vector<num>& b) {
	int n = mt.getDimFilas();
	int m = mt.getDimColumnas();
	vector<num> x = vector<num>(n);
	for(int i = minimum(n,m); i < n; ++i) {
		x[i] = 0;
	}

	x[minimum(n,m)-1] = b[minimum(n,m)] / mt.get(minimum(n,m)-1,minimum(n,m)-1);

	for(int i = minimum(n,m)-2; i >= 0; --i) {
		x[i] = b[i];
		num elemento_diagonal = mt.get(i,i);
		for(int j = minimum(n,m)-1; j > i; --j) {
			num a_ij = mt.get(i,j);
			x[i] -= a_ij * x[j];
		}
		x[i] /= elemento_diagonal;	
	}
	return x;
}

num diferencia_normaUno(vector<num>& v1, vector<num>& v2) {
    num acum = 0;
    for (int i = 0; i < v1.size(); ++i){
        acum += abs(v1[i]-v2[i]);
    }
    return acum;
}

num normaUno(vector<num>& el_vector) {
    num norma = 0;
    for(int i = 0; i < el_vector.size(); ++i) {
        norma += abs(el_vector[i]);
    }
    return norma;
}

void imprimirVector(vector<num>& v) {
	cout << "[ ";
	for(int i = 0; i < v.size(); ++i) {
		cout << v[i];
		(i + 1 >= v.size()) ? cout << " ]" : cout << " ";
	}
}