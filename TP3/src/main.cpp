#include <algorithm>
#include "MatrizEsparsa.h"
#include "factorizacionQR.h"
#include "quadraticExtrapolation.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <cassert>
#include <ctime>

#define epsilonDeParada 1e-8

using namespace std;

int NODOS;
int LINKS;

void metodoDeLaPotencia(MatrizEsparsa& , bool, bool, vector<num>&,num,int);
bool corresponde_usar_extrapolacion(const int iters, const int n);
void extrapolacion_cuadratica(
    vector<num>& autovector_nuevo,
    const vector<num>& autovector,
    const vector<num>& autovector_anteultimo,
    const vector<num>& autovector_antepenultimo
); //vector_nuevo:in = estimación de la iteración actual; vector_nuevo:out = extrapolación usando los otros tres.

int main(int argc, char** argv) {
    if(argc < 5) {
        cout << "Uso: " << "leer README para ver los parametros." << endl;
        return 0;
    }


    ifstream archivo_entrada;
    cout << argv[1] << endl;
    archivo_entrada.open(argv[1]);
    
    float ponderadorC; // el tercer argumento de la consola es el c
    sscanf(argv[2],"%f",&ponderadorC);
    
    int arg4, arg5;
    sscanf(argv[3],"%d",&arg4); sscanf(argv[4],"%d",&arg5);
    bool usarQE = arg4 == 1; // el cuarto argumento determina si se usa qe, igual a 1 <-> se usa, != 1 <-> no se usa. Tiene que ser un numero
    bool medir = arg5 == 1;  // el quinto argumento determina si se miden resultados, idem que usarQE.

    int cada_cuanto_qe = -1;
    if(usarQE) {
        if(argc < 6) {
            cout << "Se esta usando extrapolacion cuadratica, hay que pasar un parametro adicional para indicar la periodicidad con la que se aplica. Ver README." << endl; 
            return 0;
        }
        cada_cuanto_qe; // el cuarto argumento de la consola indica cada cuanto aplicamos qe
        sscanf(argv[5],"%d",&cada_cuanto_qe);
    }

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

    P.estocastizar();
    vector<num> autovector;
                //                   v BOOL MEDIR      
    metodoDeLaPotencia(P, usarQE, medir, autovector, ponderadorC, cada_cuanto_qe);
                //            ^ BOOL USAR EXTRAPOLACION
                                                                
    ofstream archivo_resultados;
    string nombre_archivo_resultado_conQE = "../parser/resultadosConQE";
    string nombre_archivo_resultado_sinQE = "../parser/resultadosSinQE";
    string pqe_variable;
    string extension = ".out";
    char ponderadorC_str[21];
    sprintf(ponderadorC_str,"%g",ponderadorC);
    if(cada_cuanto_qe != -1) {
        pqe_variable = "conpQE";
        char cada_cuanto_qe_str[21];
        sprintf(cada_cuanto_qe_str,"%d",cada_cuanto_qe);
        pqe_variable += cada_cuanto_qe_str;
    }

    nombre_archivo_resultado_conQE += ponderadorC_str + ( (cada_cuanto_qe == -1) ? extension: pqe_variable + extension);
    nombre_archivo_resultado_sinQE += ponderadorC_str + extension; 

    if (usarQE) archivo_resultados.open(nombre_archivo_resultado_conQE.c_str());//archivo_resultados.open("../parser/resultadosConQE0.2.out");
    else archivo_resultados.open(nombre_archivo_resultado_sinQE.c_str());//archivo_resultados.open("../parser/resultadosSinQE0.2.out");
    
    vector<pair<num, int> > autovector_indexado(autovector.size());
    for (int i = 0; i < autovector.size(); ++i) {
        autovector_indexado[i] = pair<num, int>(autovector[i], i);
    }
    sort(autovector_indexado.begin(), autovector_indexado.end());

    for(int i = 0; i < autovector_indexado.size(); i++) {
        archivo_resultados << autovector_indexado[i].second << " "  << autovector_indexado[i].first  << endl;
    }
    
    
    return 0;
}


void restaVectores(vector<num>& v1, vector<num>& v2) {
    for(int i = 0; i < v1.size(); ++i) {
        v1[i] -= v2[i];
    }
}

// el c y la periodicidad de la aplicacion de qe son parametros por defecto, ver el prototipo de la funcion mas arriba
void metodoDeLaPotencia(MatrizEsparsa& P, bool usar_extrapolacion, bool medir, vector<num>& autovector, num c, int cada_cuanto_qe) {
    cout << "pQE: " << cada_cuanto_qe << endl;
    ofstream archivo_mediciones;
    if(medir) {    
        string nombre_archivo_mediciones_conQE = "../parser/medicionesConQE";
        string nombre_archivo_mediciones_sinQE = "../parser/medicionesSinQE";
        string pqe_variable;
        string extension = ".out";
        if(cada_cuanto_qe != -1) {
            pqe_variable = "conpQE";
            char cada_cuanto_qe_str[21];
            sprintf(cada_cuanto_qe_str,"%d",cada_cuanto_qe);
            pqe_variable += cada_cuanto_qe_str;
        }
        char ponderadorC_str[21];
        sprintf(ponderadorC_str,"%g",c);
        nombre_archivo_mediciones_conQE += ponderadorC_str + ( (cada_cuanto_qe == -1) ? extension: pqe_variable + extension);
        nombre_archivo_mediciones_sinQE += ponderadorC_str + extension; 
        if (usar_extrapolacion) archivo_mediciones.open(nombre_archivo_mediciones_conQE.c_str());
        else archivo_mediciones.open(nombre_archivo_mediciones_sinQE.c_str());
        archivo_mediciones << NODOS << endl;
        archivo_mediciones << LINKS << endl;
    }

    int cantidad_paginas = P.getDimFilas(); // la matriz es cuadrada(cant_paginas * cant_paginas)
    num proba = 1.0 / cantidad_paginas;

    autovector = vector<num>(cantidad_paginas,proba);
    vector<num> autovector_nuevo = vector<num>(cantidad_paginas);
    
    vector<num> autovector_anteultimo = vector<num>(cantidad_paginas, 0);
    vector<num> autovector_antepenultimo = vector<num>(cantidad_paginas, 0);

    int cant_iters = 1;
    num error = 1/0.0;
    time_t inicio, fin;
    num tiempo_ex_en_segundos;
    inicio = time(NULL);
    while(error >= epsilonDeParada) {
        
        P.multiplicar_vector(autovector, autovector_nuevo);
        escalar_vector(autovector_nuevo, c);
        num norma_autovector_nuevo = normaUno(autovector_nuevo); //cout << "norma xk+1: " << norma_autovector_nuevo << endl;
        num norma_autovector = normaUno(autovector); //cout << "norma xk: " << norma_autovector << endl;
        num w = norma_autovector - norma_autovector_nuevo;
        
        for(int j = 0; j < cantidad_paginas; j++) {  
            autovector_nuevo[j] += w*proba;
        }
        
        if (usar_extrapolacion && corresponde_usar_extrapolacion(cant_iters, cada_cuanto_qe)) {
            cout << "Entre a QE " << endl;
            archivo_mediciones << "QE ";
            quadraticExtrapolation(autovector_nuevo, autovector, autovector_anteultimo, autovector_antepenultimo);
        }

        error = diferencia_normaUno(autovector, autovector_nuevo);
        
        if(medir) {
            archivo_mediciones << cant_iters << " " << error << endl;
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
    tiempo_ex_en_segundos = (fin - inicio);

    cout << "TIEMPO: " << tiempo_ex_en_segundos << endl;
    
    cout << "Cantidad de iteraciones: " << cant_iters << endl;
    if(medir) {
        archivo_mediciones << "secs: " << tiempo_ex_en_segundos << endl;
        archivo_mediciones.close();
    }
}

bool corresponde_usar_extrapolacion(const int cant_iters, const int k) {
     //una vez que tenemos tres iteraciones anteriores, extrapolamos cada k iteraciones
    return (cant_iters > 3) && (cant_iters % k == 0);
}
