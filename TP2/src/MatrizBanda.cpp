#include "MatrizBanda.h"
#include <iostream>

using namespace std;

MatrizBanda::MatrizBanda(int n, int m) : n(n), m(m), filas(n, MatrizBanda::Fila()) {
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

void MatrizBanda::setLast(const int i, const int j, const num a) {
	filas[i].setLast(j,a);
}

void MatrizBanda::sumarMultiploDeFila(const int i1, const int i2, const num k) {
	filas[i1].sumarMultiploDeFila(filas[i2], k);
}

void MatrizBanda::intercambiarFilas(const int i1, const int i2) {
	MatrizBanda::Fila fAux = filas[i1];
	filas[i1] = filas[i2];
	filas[i2] = fAux;
}

const list< pair<int,num> >& MatrizBanda::getFila(const int i) {
	return filas[i].noNulos;
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

void MatrizBanda::Fila::setLast(const int j, const num a) {
	pair<int, num> p(j,a);
	noNulos.push_back(p);
}

void MatrizBanda::triangularConGauss(const int bandaInferior, vector<num>& b){
    for(int i = 0; i < (this->n) ; i++){
        num max = abs(this->get(i, i)); //(i,i) es el primer elemento no nulo de la fila i :)
        int fila_pivote = i;
        int ultimaFila = (this->n <= i+bandaInferior ? this->n : i+bandaInferior);
        for(int j = i+1; j < ultimaFila; j++){
            if (abs(this->get(j, i)) > max){
                max = abs(this->get(j, i));
                fila_pivote = j;
            }
        }
        if(iguales(max, 0)) {cout << "Sistema singular! Llegué hasta la fila " << i << endl; return;}
        if(fila_pivote != i){
            this->intercambiarFilas(i, fila_pivote);
            num b_temp = b[i];
            b[i] = b[fila_pivote];
            b[fila_pivote] = b_temp;
        }
        num pivote = this->get(i, i);

        for(int j = i+1; j < ultimaFila; j++){
        	num a_ji = this->get(j,i); //(j,i) es el elemento a anular en la fila j. //es nulo, o es el primero no nulo :)
        	if (! iguales(a_ji, 0)) {
	            num multiplicador = a_ji / pivote;
	            this->sumarMultiploDeFila(j, i, -1*multiplicador);
	            b[j] -= b[i]*multiplicador;
	        }
        }
    }
}

void MatrizBanda::printMatriz(bool soloNoNulos) {
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

void MatrizBanda::Axb(vector<num>& x, vector<num>& b) {
    for(int i = 0; i < this->getDim().first; ++i) {
        num suma = 0;
        for(int k = 0; k < this->getDim().second; ++k) {
            suma += this->get(i,k) * x[k];
        }
        b[i] = suma;
    }
}

void MatrizBanda::setearFuerzaMaxima(num fuerza_absoluta, int junta) {
	fuerzaMax.first = fuerza_absoluta;
	fuerzaMax.second = junta;
}

