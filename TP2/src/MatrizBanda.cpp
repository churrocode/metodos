#include "MatrizBanda.h"

MatrizBanda::MatrizBanda(int n, int m, int p, int q) {
    this->n = n;
    this->m = m;
    this->p = p;
    this->q = q;
}

MatrizBanda::MatrizBanda(const MatrizBanda& orig) {
}

MatrizBanda::~MatrizBanda() {
}

float* MatrizBanda::getValues(){
    return this->values;
}


/*
MatrizBanda::operator[](int i, int j){
    
}
 */
