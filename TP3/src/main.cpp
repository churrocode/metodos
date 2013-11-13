#include "MatrizEsparsa.h"
#include "factorizacionQR.h"
#include "quadraticExtrapolation.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <cassert>
#include <ctime>


using namespace std;

int NODOS;
int LINKS;


vector<num> metodoDeLaPotencia(MatrizEsparsa& , num, bool, bool);
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
    NODOS = cantidad_paginas;
    // segundo int: cantidad de links
    archivo_entrada >> cantidad_links;
    cout << "Cantidad de links = " << cantidad_links << endl;
    LINKS = cantidad_links;
    
    MatrizEsparsa P(cantidad_paginas, cantidad_paginas);
    
    int pagina_origen, pagina_destino;
    // cada dos int leidos (por linea): el primero es la pagina origen del link, el segundo es la pagina destino del link
    while(archivo_entrada.eof() != 1) {
        archivo_entrada >> pagina_origen;
        archivo_entrada >> pagina_destino;
        P.set(pagina_destino-1, pagina_origen-1, 1); // VER SI LA MATRIZ PUEDE EMPEZAR EN 1 Y NO EN 0
    }
    archivo_entrada.close();

    //P.printMatriz();

    // genero P estocastica
    for(int j = 0; j < P.getDimFilas(); j++){   
        num col_sum = 0;
        for(int i = 0; i < P.getDimColumnas(); i++){
            col_sum += P.get(i, j); 
        }
        if(col_sum != 0){
            for(int k = 0; k < P.getDimFilas(); k++){
                P.set(k, j, P.get(k, j)/col_sum);
                }
        }
    }
    
    //P.printMatriz();


    // NO HACIA FALTA, SE HACE DIRECTO EN EL METODO DE LA POTENCIA CON EL ALGORITMO 1
    /*num numerito = 1.0 / cantidad_paginas;
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
    
    P.printMatriz();*/

                                        //                      v BOOL MEDIR      
    vector<num> autovector = metodoDeLaPotencia(P, 0.2, false, true);
                                        //                ^ BOOL USAR EXTRAPOLACION
                                                                
    imprimirVector(autovector);
    
    ofstream archivo_resultados;
    archivo_resultados.open("../parser/resultados2.out");
    pair<num, int> p;
    for(int i = 0; i < autovector.size(); i++) {
        p = sacarMaximo(autovector);
        archivo_resultados << p.second << " "  << p.first  << endl;
    }
    
    
    return 0;
}


/*num normaUno(vector<num>& el_vector) {
    num norma = 0;
    for(int i = 0; i < el_vector.size(); ++i) {
        norma += abs(el_vector[i]);
    }
    return norma;
}

*/void restaVectores(vector<num>& v1, vector<num>& v2) {
    for(int i = 0; i < v1.size(); ++i) {
        v1[i] -= v2[i];
    }
}

/*num diferencia_normaUno(const vector<num>& v1, const vector<num>& v2) {
    num acum = 0;
    for (int i = 0; i < v1.size(); ++i){
        acum += abs(v1[i]-v2[i]);
    }
    return acum;
}*/

/*num productoInterno(vector<num>& v1, vector<num>& v2) ^{
 
}*/
        
vector<num> metodoDeLaPotencia(MatrizEsparsa& P, num c, bool usar_extrapolacion, bool medir) {
    ofstream archivo_mediciones;
    if(medir) {
        archivo_mediciones.open("../parser/mediciones2.out");
        archivo_mediciones << NODOS << endl;
        archivo_mediciones << LINKS << endl;
    }
    int cantidad_paginas = P.getDimFilas(); // la matriz es cuadrada(cant_paginas * cant_paginas)
    num proba = 1.0 / cantidad_paginas;
    vector<num> vector_proba_uniforme = vector<num>(cantidad_paginas,proba);
    num epsilon = 1e-15;
    vector<num> autovector = vector<num>(cantidad_paginas,proba);
    vector<num> autovector_nuevo = vector<num>(cantidad_paginas);
    
    vector<num> autovector_anteultimo = vector<num>(cantidad_paginas, 0);
    vector<num> autovector_antepenultimo = vector<num>(cantidad_paginas, 0);

    int cant_iters = 0;
    num error = 0.0;
    bool seguir_iterando = true;
    time_t inicio, fin;
    num tiempo_ex_en_milisegundos;
    inicio = time(NULL);
    while(seguir_iterando) {
        for(int j = 0; j < cantidad_paginas; j++){ // multiplicamos por P'

            num producto_interno = 0;
            for(int i = 0; i < cantidad_paginas; i++){
                producto_interno += P.get(i,j)*autovector[i];

            }
            //autovector_temp es la iteración que acabamos de calcular
            autovector_nuevo[j] = producto_interno*c;
        }

        //cout << "xk+1: "; imprimirVector(autovector_nuevo); cout << endl;
        //cout << "xk: "; imprimirVector(autovector); cout << endl;
        num norma_autovector_nuevo = normaUno(autovector_nuevo); //cout << "norma xk+1: " << norma_autovector_nuevo << endl;
        num norma_autovector = normaUno(autovector); //cout << "norma xk: " << norma_autovector << endl;
        num w = norma_autovector - norma_autovector_nuevo;
        
        //cout << "v: "; imprimirVector(vector_proba_uniforme); cout << endl;
        vector<num> w_por_v = multPorEscalar(vector_proba_uniforme,w);
        //cout << "w_por_v: "; imprimirVector(w_por_v); cout << endl;

        for(int j = 0; j < cantidad_paginas; j++) {   
            autovector_nuevo[j] += w_por_v[j];
        }
        
        error = diferencia_normaUno(autovector, autovector_nuevo);
        seguir_iterando = error >= epsilon;
        
        if(medir) {
            archivo_mediciones << cant_iters << " " << error << endl;
        }

        if (seguir_iterando && usar_extrapolacion && corresponde_usar_extrapolacion(cant_iters, 10)) {
            cout << "Entre a QE " << endl;
            quadraticExtrapolation(autovector_nuevo, autovector, autovector_anteultimo, autovector_antepenultimo);
        }

        //reacomodamos los vectores:
        if (usar_extrapolacion) {
            //autovector_nuevo ya lo calculamos con la interpolación
            autovector_antepenultimo = autovector_anteultimo;
            autovector_anteultimo = autovector;
        }
        //el autovector es la iteración que acabamos de calcular
        autovector = autovector_nuevo;
        ++cant_iters;
    }
    fin = time(NULL);
    tiempo_ex_en_milisegundos = (fin - inicio) * 1000000.0;

    cout << "TIEMPO: " << tiempo_ex_en_milisegundos << endl;
    
    cout << "Cantidad de iteraciones: " << cant_iters << endl;
    if(medir) {
        archivo_mediciones.close();
    }
    return autovector;
}

bool corresponde_usar_extrapolacion(const int cant_iters, const int k) {
     //una vez que tenemos tres iteraciones anteriores, extrapolamos cada k iteraciones
    cout << "Voy a extrapolar" << endl;
    return (cant_iters > 3) && ((cant_iters-3) % k == 0);
}
