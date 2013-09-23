#include <cstdlib>
#include <iostream>

#include "MatrizBanda.h"

using namespace std;

float abs(float x){
    return x >= 0? x: -x;
}

void gauss(MatrizBanda m, int n, int m){
    for(int i = 1; i < m; i++){

        max = abs(m[i, i]);
        int fila_pivote = i;
        for(int j = i+1; j < n; j++){
            if (abs(m[j, i]) > max){
                max = abs(m[j, i]);
                fila_pivote = j;
            }
        }
        if(max == 0) return -1;
        if(fila_pivote != i){
        //    m.swapearFilas(i, fila_pivote)
        }
        float pivote = m[i, i];
        for(int j = i+1; j < n; j++){
            float multiplicador = m[j, i] / pivote;
        //    m.sumarMultiploDeFila(j, i, -1*pivote);
        }
    }
    
}


int main(int argc, char** argv) {
    
    cout << "MAIN CORRIENDO" << endl;

    MatrizBanda m = MatrizBanda(2, 2, 1, 1);
    
    return 0;
}



