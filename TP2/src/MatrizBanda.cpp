#include "MatrizBanda.h"
#include <iostream>

using namespace std;

MatrizBanda::MatrizBanda(int n, int m) : n(n), m(m), filas(n, MatrizBanda::Fila()) {
}

// MatrizBanda::MatrizBanda(const MatrizBanda& orig) {
// }

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

void MatrizBanda::intercambiarFilas(const int i1, const int i2) {
	MatrizBanda::Fila fAux = filas[i1];
	filas[i1] = filas[i2];
	filas[i2] = fAux;
}

pair<int, int> MatrizBanda::getDim() {
	return pair<int, int>(n,m);
}

void MatrizBanda::reemplazarFila(const int i, list< pair<int,num> >& nuevaFila) {
	filas[i].reemplazarFila(nuevaFila);
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

void MatrizBanda::Fila::set(const int j, const num a) {
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

void MatrizBanda::Fila::reemplazarFila(list< pair<int,num> >& otraFila) {
	noNulos.clear();
	noNulos = otraFila;
}

void MatrizBanda::triangularConGauss(int p, int q, vector<num>& b){
    for(int i = 0; i < (this->m) ; i++){
        this->printMatriz();
        num max = abs(this->get(i, i));
        int fila_pivote = i;
        for(int j = i+1; j < this->n ; j++){
        //for(int j = i+1; j < minimum(this->n, i+p-1) ; j++){
            if (abs(this->get(j, i)) > max){
                max = abs(this->get(j, i));
                fila_pivote = j;
            }
        }
        if(max == 0) return;
        if(fila_pivote != i){
            this->intercambiarFilas(i, fila_pivote);
            num b_temp = b[i];
            b[i] = b[fila_pivote];
            b[fila_pivote] = b_temp;

        }
        num pivote = this->get(i, i);
        for(int j = i+1; j < this->n; j++){
            num multiplicador = this->get(j, i) / pivote;
            this->sumarMultiploDeFila(j, i, -1*multiplicador);
            b[j] -= b[i]*multiplicador;
        }
    }
    
}

void MatrizBanda::printMatriz() {
	for (int i = 0; i < this->getDim().first ; ++i) {
		for (int j = 0; j < this->getDim().second ; ++j) {
			cout << this->get(i,j) << " "; //get(i,j) sólo acá!
		}
		cout << endl;
	}
	cout << endl;
}
