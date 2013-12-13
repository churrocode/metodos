#include <utility>
#include <cmath>
#include "factorizacionQR.h"
#include <iostream>
#include "utils.h"

using namespace std;

void householder2Cols(MatrizEsparsa& A, vector<num>& b) {
    cout << "Entre a householder" << endl;
    num primera_col_norma2 = A.norma_de_columna(0,0);
    //Q1 = Id - 2u_1*u_1'
    //u_1 = (a_1) - ||a_1||e_1
    vector<num> u_1 = A.vector_columna(0);
    int n = A.getDimFilas();
    u_1[0] -= primera_col_norma2;
    normalizar_vector(u_1);
    //setear A(0, 0)  = primera_col_norma2, el resto en 0.
    A.set(0,0, primera_col_norma2);
    A.truncar_columna(0, 1);
    
    //multiplicar la segunda columna de A por Q1 (a_2 = Q1*a_2)
    // a_2 = (Id - 2u1*u1')a2 = a2 - 2(u1'*a2) u1
    vector<num> a_2 = A.vector_columna(1);
    num p_i = producto_interno(u_1, a_2);
    for (int i = 0; i < n; ++i) {
        a_2[i] -= 2*p_i*u_1[i];
        //A.set(i, 1, a_2[i]);
    }
    //El único valor que me interesa conservar en A es el primero de la 2da col
    //el resto de las cuentas las hago sobre a_2 (más eficiente si no es esparso)
    A.set(0, 1, a_2[0]);

    //aplicar al término indepte.
    //Q1*b = (Id - 2u_1*u_1')*b = b - 2(u_1'*b) (u_1)
    p_i = producto_interno(u_1, b);
    for (int i = 0; i < n; ++i) {
        b[i] -= 2*p_i*u_1[i];
    }
    
    //lo mismo con la segunda, pero sin mirar la primera fila!
    //A(1, 1), el resto en 0.
    a_2[0] = 0;
    num segunda_columna_norma2 = norma2(a_2);
    A.set(1,1,segunda_columna_norma2);
    //tirar el resto de los números de la segunda columna !!
    A.truncar_columna(1, 2);
    // "vector<num> u_2 = a_2;"
    //u_2[0] = 0;
    a_2[1] -= segunda_columna_norma2;
    normalizar_vector(a_2);
   
    p_i = producto_interno(a_2, b);
    for (int i = 1; i < n; ++i) {
        b[i] -= 2*p_i*a_2[i];
    }
    cout << "Sali de householder" << endl;
}

void testHouseholder2Cols(){
    
    MatrizEsparsa A = MatrizEsparsa(3, 2);
    
    A.set(0, 0, -3);
    A.set(0, 1, -7);
    A.set(1, 0, -4);
    A.set(1, 1, -5);
    A.set(2, 0, -1);
    A.set(2, 1, -8);
    /*
    A.set(0, 0, -0.1576);
    A.set(0, 1, -0.4854);
    A.set(1, 0, -0.9706);
    A.set(1, 1, -0.8003);
    A.set(2, 0, -0.9572);
    A.set(2, 1, -0.1419);
    */
    A.printMatriz();
    
    vector<num> b;
    
    householder2Cols(A, b);
    
    //givensDosColumnas(A);
    
}

vector<num> backwardSubstitution2Cols(MatrizEsparsa& A, vector<num>& b) {
    //A tiene 2 columnas, por lo menos 2 filas y es triangular superior.
    vector<num> solucion(2, 0.0);
    solucion[1] = b[1] / A.get(1, 1); // si esto viene de una QR, A(1,1) tiene que ser != 0
    solucion[0] = (b[0] - A.get(0, 1) * solucion[1])/A.get(0,0); // como arriba, A(0,0) tiene que ser != 0
    return solucion;
}  
