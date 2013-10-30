#include "MatrizEsparsa.h"
#include <fstream>
#include <iostream>
#include <cassert>


using namespace std;

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
        for(int i = 0; i < P.getDimCols(); i++){
            col_sum += P.get(i, j); 
        }
        for(int k = 0; k < P.getDimFilas(); k++){
            P.set(k, j, P.get(k, j)/col_sum);
        }
    }
    
    P.printMatriz();

    P.set(0,2,0);
    num numerito = 1.0 / cantidad_paginas;
    for (int j = 0; j < P.getDimCols(); j++){
        if (P.columnaDeCeros(j)){
            for (int i = 0; i < P.getDimFilas(); i++){
                P.set(i, j, numerito);
            }
        }
    }

    P.printMatriz();

    return 0;
 
}


