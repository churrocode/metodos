#include "MatrizBanda.h"

using namespace std;

MatrizBanda::MatrizBanda(int n, int m) : n(n), m(m), filas(n, MatrizBanda::Fila()) {
}

MatrizBanda::MatrizBanda(const MatrizBanda& orig) {
}

MatrizBanda::~MatrizBanda() {
}

num MatrizBanda::primeroDeLaFila(const int i) {
	if (filas[i].noNulos.empty()) {
		return 0;
	} else {
		return filas[i].noNulos.front().second;
	}
}

num MatrizBanda::get(int i, int j) {
	return filas[i].get(j);
}

void MatrizBanda::set(int i, int j, num a) {
	filas[i].set(j, a);
}

void MatrizBanda::sumarMultiploDeFila(const int i1, const int i2, const num k) {
	filas[i1].sumarMultiploDeFila(filas[i2], k);
}

pair<int, int> MatrizBanda::getDim() {
	return pair<int, int>(n,m);
}
void MatrizBanda::Fila::sumarMultiploDeFila(const Fila& f, num k) {
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

num MatrizBanda::Fila::get(const int j) {
	if (noNulos.front().first < j && j < noNulos.back().second	) {
		list< pair<int, num> >::iterator it = noNulos.begin();
		for (; it != noNulos.end() && it->first < j; ++it);
		if (it != noNulos.end()) {
			return it->second;
		}
	}
	return 0;
}

void MatrizBanda::Fila::set(const int j, const num a) {
	if (j < noNulos.front().first) {
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
