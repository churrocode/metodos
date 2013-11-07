#include <utility>
#include <cmath>

#include "MatrizEsparsa.h"

using namespace std;

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
