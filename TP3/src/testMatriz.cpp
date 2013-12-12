#include "MatrizEsparsa.h"
#include <iostream>

void print_v(vector<num>& v) {
	for (int i = 0; i < v.size(); ++i)
		cout << v[i] << ' ';
	cout << endl;
}

void aplicar_test(MatrizEsparsa& A, vector<num>& v, vector<num>& res) {
	A.printMatriz();
	print_v(v);
	A.multiplicar_vector(v, res);
	print_v(res);
	cout << "---------------\n";
}

int main() {
	MatrizEsparsa Cero(10, 10);
	MatrizEsparsa Id(10, 10); for(int i = 0; i < 10; ++i) Id.set(i,i,1);
	MatrizEsparsa Lambda5(10, 10); for(int i = 0; i < 10; ++i) Lambda5.set(i, i, 5);
	MatrizEsparsa E1(10,10); E1.set(0, 0, 1);
	MatrizEsparsa Alt(10,10); Alt.set(0,0, -1); Alt.set(0, 5, 1); Alt.set(0,8, -1); Alt.set(0,9, 1);
		Alt.set(4, 1, -1); Alt.set(4, 4, -1); Alt.set(4, 6, 1); Alt.set(4, 8, 1);
		Alt.set(8, 6, 1); Alt.set(8, 8, -1);
	//MatrizEsparsa Alt = Id;
	vector<num> res(10);
	vector<num> unos(10, 1);
	vector<num> consecs(10, 1);
	for(int i = 0; i < 10; ++i) {
		consecs[i] = i;
	}

	aplicar_test(Cero, unos, res);
	aplicar_test(Cero, consecs, res);
	aplicar_test(Id, unos, res);
	aplicar_test(Id, consecs, res);
	aplicar_test(Lambda5, unos, res);
	aplicar_test(Lambda5, consecs, res);
	aplicar_test(E1, unos, res);
	aplicar_test(E1, consecs, res);
	aplicar_test(Alt, unos, res);
	aplicar_test(Alt, consecs, res);

	


	return 0;
}