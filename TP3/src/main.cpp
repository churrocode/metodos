#include "MatrizEsparsa.h"
#include <fstream>
#include <iostream>
#include <cassert>


using namespace std;

vector<num> metodoDeLaPotencia(MatrizEsparsa& A, num c);
bool corresponde_usar_extrapolacion(const int iters, const int n);
void extrapolacion_cuadratica(
    vector<num>& autovector_nuevo,
    const vector<num>& autovector,
    const vector<num>& autovector_anteultimo,
    const vector<num>& autovector_antepenultimo
); //vector_nuevo:in = estimación de la iteración actual; vector_nuevo:out = extrapolación usando los otros tres.

int main(int argc, char** argv) {
    if(argc != 2) {
        cout << "Uso: " << "Pasar un archivo de entrada, leer README.txt para ver el formato" << endl;
        return 0;
    }
    ifstream archivo_entrada;
    cout << argv[1] << endl;
    archivo_entrada.open(argv[1]);
    
    int cantidad_paginas, cantidad_links;
    // primer int: cantidad de paginas
    archivo_entrada >> cantidad_paginas;
    cout << "Cantidad de paginas = " << cantidad_paginas << endl;
    // segundo int: cantidad de links
    archivo_entrada >> cantidad_links;
    cout << "Cantidad de links = " << cantidad_links << endl;
    
    MatrizEsparsa P(cantidad_paginas, cantidad_paginas);
    
    int pagina_origen, pagina_destino;
    // cada dos int leidos (por linea): el primero es la pagina origen del link, el segundo es la pagina destino del link
    while(archivo_entrada.eof() != 1) {
        archivo_entrada >> pagina_origen;
        archivo_entrada >> pagina_destino;
        P.set(pagina_destino-1, pagina_origen-1, 1); // VER SI LA MATRIZ PUEDE EMPEZAR EN 1 Y NO EN 0
    }
    archivo_entrada.close();

    P.printMatriz();

    // genero P estocastica
    for(int j = 0; j < P.getDimFilas(); j++){
        num col_sum = 0;
        for(int i = 0; i < P.getDimColumnas(); i++){
            col_sum += P.get(i, j); 
        }
        for(int k = 0; k < P.getDimFilas(); k++){
            P.set(k, j, P.get(k, j)/col_sum);
        }
    }
    
    P.printMatriz();
    /*  NO HACIA FALTA, SE HACE DIRECTO EN EL METODO DE LA POTENCIA CON EL ALGORITMO 1
    num numerito = 1.0 / cantidad_paginas;
    num c = 0.5;
    for (int j = 0; j < P.getDimColumnas(); j++){
        if (P.columnaDeCeros(j)){
            for (int i = 0; i < P.getDimFilas(); i++) {
                P.set(i, j, numerito);
            }
        } else {
            for (int i = 0; i < P.getDimFilas(); i++){
                P.set(i, j, c*P.get(i, j) + (1 - c)*numerito);
            }
        }
    }

    P.printMatriz();
    */
    
    //vector<num> autovector = metodoDeLaPotencia(P, 0.5);
    
    return 0;
}


num normaUno(vector<num>& el_vector) {
    num norma = 0;
    for(int i = 0; i < el_vector.size(); ++i) {
        norma += abs(el_vector[i]);
    }
    return norma;
}

void restaVectores(vector<num>& v1, vector<num>& v2) {
    for(int i = 0; i < v1.size(); ++i) {
        v1[i] -= v2[i];
    }
}

num diferencia_normaUno(const vector<num>& v1, const vector<num>& v2) {
    num acum = 0;
    for (int i = 0; i < v1.size(); ++i){
        acum += abs(v1[i]-v2[i]);
    }
    return acum;
}

/*num productoInterno(vector<num>& v1, vector<num>& v2) ^{
 
}*/
        
vector<num> metodoDeLaPotencia(MatrizEsparsa& P, num c, bool usar_extrapolacion) {
    int cantidad_paginas = P.getDimFilas(); // la matriz es cuadrada(cant_paginas * cant_paginas)
    num proba = 1.0 / cantidad_paginas;
    num epsilon = 1e-28;
    vector<num> autovector = vector<num>(cantidad_paginas,proba);
    vector<num> autovector_nuevo = vector<num>(cantidad_paginas);
    
    vector<num> autovector_anteultimo(cantidad_paginas, 0);
    vector<num> autovector_antepenultimo(cantidad_paginas, 0);

    int iters = 0;
    bool seguir_iterando = true;
    while(seguir_iterando) {
        for(int j = 0; j < cantidad_paginas; j++){

            num producto_interno = 0;
            for(int i = 0; i < cantidad_paginas; i++){
                producto_interno += P.get(i,j)*autovector[i];
            }
            //autovector_temp es la iteración que acabamos de calcular
            autovector_nuevo[j] = producto_interno*c;
        }

        num norma_autovector_nuevo = normaUno(autovector_nuevo);
        num norma_autovector = normaUno(autovector);
        num w = norma_autovector - norma_autovector_nuevo;
        num w_por_v = w*proba;

        for(int j = 0; j < cantidad_paginas; j++) {   
            autovector_nuevo[j] += w_por_v;
        }
 
        seguir_iterando = diferencia_normaUno(autovector, autovector_nuevo) >= epsilon;
        if (seguir_iterando && usar_extrapolacion && corresponde_usar_extrapolacion(iters, 10)) {
            extrapolacion_cuadratica(autovector_nuevo, autovector, autovector_anteultimo, autovector_antepenultimo);
        }

        //reacomodamos los vectores:
        if (usar_extrapolacion) {
            //autovector_nuevo ya lo calculamos con la interpolación
            autovector_antepenultimo = autovector_anteultimo;
            autovector_anteultimo = autovector;

        }
        //el autovector es la iteración que acabamos de calcular
        autovector = autovector_nuevo;
        ++iters;
    }
    
    return autovector;
}

bool corresponde_usar_extrapolacion(const int iters, const int k) {
     //una vez que tenemos tres iteraciones anteriores, extrapolamos cada k iteraciones
    cout << "Voy a extrapolar" << endl;
    return (iters > 3) && ((iters-3) % k == 0);
}
