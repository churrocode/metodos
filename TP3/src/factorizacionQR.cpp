#include <utility>
#include <cmath>
#include "factorizacionQR.h"
#include <iostream>
#include "utils.h"

using namespace std;

MatrizEsparsa* givensDosColumnas(MatrizEsparsa& A) {
    int n = A.getDimFilas();
    MatrizEsparsa* Q = new MatrizEsparsa(n, n);  
    num x_i_0, x_j_0, x_i_1, x_j_1, norma_dos, cos, sen, aux_1, aux_2;
    //primera columna
    for(int i = 0; i < n-1; i++) {
        x_i_0 = A.get(0, 0);
        x_j_0 = A.get(i+1, 0);
        x_i_1 = A.get(0, 1);
        x_j_1 = A.get(i+1, 1);
        norma_dos = sqrt((x_i_0*x_i_0) + (x_j_0*x_j_0));
        cos = x_i_0 / norma_dos;
        sen = x_j_0 / norma_dos;

        A.set(0, 0, cos*x_i_0 + sen*x_j_0 );
        A.set(i+1, 0, 0 /*(-1)*sen*x_i_0 + cos*x_j_0*/ );
        A.set(0, 1, cos*x_i_1 + sen*x_j_1 );
        A.set(i+1, 1, (-1)*sen*x_i_1 + cos*x_j_1 );

        if(i != 0){
            for(int k = 0; k < n; k++) {
                aux_1 = Q->get(k, 0);
                aux_2 = Q->get(k, i+1);
                Q->set(k, 0, aux_1*cos + aux_2*sen);
                Q->set(k, i+1, aux_1*(-1)*sen + aux_2*cos);
            }
        } else {        // PRIMER PASO, ME ARMO Q = P
            Q->set(0, 0, cos);
            Q->set(1, 0, sen);
            Q->set(0, 1, (-1)*sen);
            Q->set(1, 1, cos);
            for(int k = 2; k < n; k++){
                Q->set(k, k, 1);
            }
        }
    }
    //segunda columna
    for(int i = 1; i < n-1; i++) {
       // x_i_0 = A.get(1, 0);
       // x_j_0 = A.get(i+1, 0);
        x_i_1 = A.get(1, 1);
        x_j_1 = A.get(i+1, 1);
        norma_dos = sqrt((x_i_1*x_i_1) + (x_j_1*x_j_1));
        cos = x_i_1 / norma_dos;
        sen = x_j_1 / norma_dos;

        A.set(1, 1, cos*x_i_1 + sen*x_j_1 );
        A.set(i+1, 1, 0 /*(-1)*sen*x_i_0 + cos*x_j_0*/ );
       // A.set(0, 1, cos*x_i_1 + sen*x_j_1 );
       // A.set(i+1, 1, (-1)*sen*x_i_1 + cos*x_j_1 );

        for(int k = 0; k < n; k++) {
            aux_1 = Q->get(k, 1);
            aux_2 = Q->get(k, i+1);
            Q->set(k, 1, aux_1*cos + aux_2*sen);
            Q->set(k, i+1, aux_1*(-1)*sen + aux_2*cos);
        }
    }    
    Q->printMatriz();
    return Q;
}


void householder2Cols(MatrizEsparsa& A, vector<num>& b) {
    num primera_col_norma2 = A.norma_de_columna(0,0);
    //Q1 = Id - 2u_1*u_1'
    //u_1 = (a_1) - ||a_1||e_1
    vector<num> u_1 = A.vector_columna(0);
    int n = A.getDimFilas();
    u_1[0] -= primera_col_norma2;
    normalizar_vector(u_1);
    //setear A(0, 0)  = primera_col_norma2, el resto en 0 !!!!!

    //multiplicar la segunda columna de A por Q1 (a_2 = Q1*a_2)
    // a_2 = (Id - 2u1*u1')a2 = a2 - 2(u1'*a2) u1
    vector<num> a_2 = A.vector_columna(1);
    num p_i = producto_interno(u_1, a_2);
    for (int i = 0; i < n; ++i) {
        a_2[i] -= 2*p_i*u_1[i];
    }

    //aplicar al término indepte.
    //Q1*b = (Id - 2u_1*u_1')*b = b - 2(u_1'*b) (u_1)
    p_i = producto_interno(u_1, b);
    for (int i = 0; i < n; ++i) {
        b[i] -= 2*p_i*u_1[i];
    }
    //lo mismo con la segunda
    //tirar el resto de los números de la segunda columna !!
    num segunda_columna_norma2 = A.norma_de_columna(1, 1);
    vector<num> u_2 = A.vector_columna(1);
    u_2[1] -= segunda_columna_norma2;
    normalizar_vector(u_2);
    p_i = producto_interno(u_2, b);
    for (int i = 0; i < n; ++i) {
        b[i] -= 2*p_i*u_2[i];
    } 
}
/*
num normaDos(list<pair<int, num> >& la_lista) {
    num norma = 0;
    list< pair<int, num> >::iterator it = la_lista.begin();
    for (; it != la_lista.end(); ++it) norma += (it->second*it->second);
    return sqrt(norma);
}

pair< MatrizEsparsa, MatrizEsparsa > houseHolder(const MatrizEsparsa& A){
    MatrizEsparsa* Q = MatrizEsparsa(A.getDimFilas(), A.getDimColumnas());  
    MatrizEsparsa* R = MatrizEsparsa(A.getDimFilas(), A.getDimColumnas());  
    MatrizEsparsa* H = MatrizEsparsa(A.getDimFilas(), A.getDimColumnas());  
    
    for(int j = 0; j < A.getDimColumnas()-1; j++) {
        list<pair<int, num> > lista_columna = A.sliceColumna(j, j, A.getDimFilas());
        num norma = normaDos(lista_columna);
        pair<int, num> primer_elemento(0, norma);
        if(lista_columna.front().first != 0) lista_columna.pop_front();
        lista_columna.push_front(primer_elemento);
        
    }
}
*/
