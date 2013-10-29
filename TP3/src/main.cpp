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
    archivo_entrada >> cantidad_paginas;
    archivo_entrada >> cantidad_links;
    MatrizEsparsa P(cantidad_paginas, cantidad_paginas);
    
    int linea_leida;
   
    // cada dos int leidos: el primero es la pagina origen del link
    // el segundo es la pagina destino del link
    while(archivo_entrada.eof() != 1) {
        archivo_entrada >> linea_leida;
        cout << linea_leida << endl;
    }
    
    archivo_entrada.close();
    
    return 0;
 
}


