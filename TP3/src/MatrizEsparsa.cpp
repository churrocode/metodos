#include "MatrizEsparsa.h"
#include <iostream>

using namespace std;

MatrizEsparsa::MatrizEsparsa(int n, int m) : n(n), m(m), proba(1/n), columnas(m, MatrizEsparsa::Columna()) {
}

num MatrizEsparsa::primeroDeLaColumna(const int i) {
	if (columnas[i].noNulos.empty()) {
		return 0;
	} else {
		return columnas[i].noNulos.front().second;
	}
}

num MatrizEsparsa::get(int i, int j) {
	return columnas[j].get(i);
}

void MatrizEsparsa::set(int i, int j, num a) {
	columnas[j].set(i, a);
}

void MatrizEsparsa::setLast(const int i, const int j, const num a) {
	columnas[j].setLast(i,a);
}

/*void MatrizEsparsa::sumarMultiploDeColumna(const int i1, const int i2, const num k) {
	columnas[i1].sumarMultiploDeColumna(columnas[i2], k);
}*/

/*void MatrizEsparsa::intercambiarColumnas(const int i1, const int i2) {
	MatrizEsparsa::Columna fAux = columnas[i1];
	columnas[i1] = columnas[i2];
	columnas[i2] = fAux;
}*/

const list< pair<int,num> >& MatrizEsparsa::getColumna(const int i) {
	return columnas[i].noNulos;
} 

pair<int, int> MatrizEsparsa::getDim() {
	return pair<int, int>(n,m);
}

int MatrizEsparsa::getDimFilas() {
	return n;
}

int MatrizEsparsa::getDimColumnas() {
	return m;
}
/*void MatrizEsparsa::Columna::sumarMultiploDeColumna(const Columna& f, num k) {
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
}*/

num MatrizEsparsa::Columna::get(const int j) {
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

void MatrizEsparsa::Columna::set(const int j, const num a) {
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

void MatrizEsparsa::Columna::setLast(const int j, const num a) {
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
    return this->columnas[col].noNulos.empty();
}

list<pair<int, num> >* MatrizEsparsa::sliceColumna(int col, int inicio, int fin) {
    return this->columnas[col].sliceColumna(inicio, fin);
    
}

list<pair<int, num> >* MatrizEsparsa::Columna::sliceColumna(int inicio, int fin) {
    list<pair<int, num> >* slice = new list<pair<int, num> >();
    list< pair<int, num> >::iterator it = noNulos.begin();
    for (; it != noNulos.end() && it->first <= fin; ++it) {
        if (inicio <= it->first) {
            pair<int, num> p(it->first, it->second);
            slice->push_back(p);
        }
    }
    return slice;
}
