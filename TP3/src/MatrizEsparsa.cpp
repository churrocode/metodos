#include "MatrizEsparsa.h"
#include <iostream>

using namespace std;

MatrizEsparsa::MatrizEsparsa(int n, int m) : n(n), m(m), filas(n, MatrizEsparsa::Fila()) {
}

num MatrizEsparsa::primeroDeLaFila(const int i) {
	if (filas[i].noNulos.empty()) {
		return 0;
	} else {
		return filas[i].noNulos.front().second;
	}
}

num MatrizEsparsa::get(int i, int j) {
	return filas[i].get(j);
}

void MatrizEsparsa::set(int i, int j, num a) {
	filas[i].set(j, a);
}

void MatrizEsparsa::setLast(const int i, const int j, const num a) {
	filas[i].setLast(j,a);
}

void MatrizEsparsa::sumarMultiploDeFila(const int i1, const int i2, const num k) {
	filas[i1].sumarMultiploDeFila(filas[i2], k);
}

void MatrizEsparsa::intercambiarFilas(const int i1, const int i2) {
	MatrizEsparsa::Fila fAux = filas[i1];
	filas[i1] = filas[i2];
	filas[i2] = fAux;
}

const list< pair<int,num> >& MatrizEsparsa::getFila(const int i) {
	return filas[i].noNulos;
} 

pair<int, int> MatrizEsparsa::getDim() {
	return pair<int, int>(n,m);
}

int MatrizEsparsa::getDimFilas() {
	return n;
}

int MatrizEsparsa::getDimCols() {
	return m;
}
void MatrizEsparsa::Fila::sumarMultiploDeFila(const Fila& f, num k) {
	list< pair<int, num> >::iterator itThis = this->noNulos.begin();
	list< pair<int, num> >::const_iterator itF = f.noNulos.begin();
	while (itThis != this->noNulos.end() && itF != f.noNulos.end()) {
		if (itThis->first < itF->first) { //f tiene un 0 en el lugar de itThis
			++itThis;
		}else if (itThis->first == itF->first) { //f tiene un valor en el mismo lugar que itThis
			itThis->second += itF->second * k;
			if (iguales(itThis->second,0)) {
				itThis = noNulos.erase(itThis);
			} else {
				++itThis;
			}
			++itF;
		} else { //itThis > itF, itThis es el primer valor que supera la posición del que estamos mirando en f.
			noNulos.insert(itThis, *itF)->second *= k;
			++itF;
		}
	}
	for (; itF != f.noNulos.end(); ++itF) {
		noNulos.push_back(*itF);
		noNulos.back().second *= k;
	}
}

num MatrizEsparsa::Fila::get(const int j) {
	if (noNulos.empty()) {
		return 0;
	} else if (noNulos.front().first == j) {
		return  noNulos.front().second;
	} else if (noNulos.back().first == j) {
		return noNulos.back().second;
	} else if (noNulos.front().first < j && j < noNulos.back().first) {
		list< pair<int, num> >::iterator it = noNulos.begin();
		for (; it != noNulos.end() && it->first < j; ++it);
		if (it->first == j) {
			return it->second;
		}
	}
	return 0;
}

void MatrizEsparsa::Fila::set(const int j, const num a) {
	if (noNulos.empty() || j < noNulos.front().first) {
		pair<int, num> p(j, a);
		noNulos.push_front(p);
	} else if (j > noNulos.back().first) {
		pair<int, num> p(j, a);
		noNulos.push_back(p);
	} else {
		list<pair <int, num> >::iterator it = noNulos.begin();
		for (; it!= noNulos.end() && it->first < j; ++it);
		if (it->first == j) {
			it->second = a;
		} else {
			pair<int, num> p(j, a);
			noNulos.insert(it, p);
		}
	}
}

void MatrizEsparsa::Fila::setLast(const int j, const num a) {
	pair<int, num> p(j,a);
	noNulos.push_back(p);
}

void MatrizEsparsa::printMatriz(bool soloNoNulos) {
	for (int i = 0; i < this->getDim().first ; ++i) {
        cout << i << "\t";
		for (int j = 0; j < this->getDim().second ; ++j) {
			if (soloNoNulos) {
				if (i == j) {
					cout << (iguales(get(i,j), 0)? "*" : "+") << " ";
				} else {
					cout << (iguales(get(i,j), 0)? "·" : "X") << " ";	
				}
			} else { 
				cout << this->get(i,j) << " "; //get(i,j) sólo acá!
			}
		}
		cout << endl;
	}
	cout << endl;
}

bool MatrizEsparsa::columnaDeCeros(int col){
	for (int i = 0; i < this->getDimFilas(); i++){
		if (this->get(i,col) != 0) return false;
	}
	return true;
}