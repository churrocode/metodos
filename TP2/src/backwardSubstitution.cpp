#include "backwardSubstitution.h"

vector<num>* backwardSubstitution(MatrizBanda& mt, vector<num> b) {
	vector<num>* x = new vector<num>(mt.getDim().first);
	pair<int,int> dim = mt.getDim();
	int n = dim.first;
	int m = dim.second;
    num x_max;
    int i_fuerza = n-1;
	(*x)[n-1] = b[n-1]/(mt.get(n-1,n-1) == 0 ? 1 : mt.get(n-1, n-1)); //permitimos tener 0*x_n = 0 en la última fila
    x_max = abs((*x)[n-1]);

	for(int i = n - 2; i >= 0; --i) {
		(*x)[i] = b[i];
        num elemento_diagonal = mt.get(i,i);
        list< pair<int, num> >::const_reverse_iterator itFila = mt.getFila(i).rbegin();
        while(itFila != mt.getFila(i).rend() && itFila->first != i) {
            int j = itFila->first;
            num a_ij = itFila->second;
            (*x)[i] -= a_ij* (*x)[j];
            ++itFila;
        }
		(*x)[i] /= elemento_diagonal;
        num x_max_aux = x_max;
        x_max = maximum(x_max,abs((*x)[i]));
        i_fuerza = (iguales(x_max,x_max_aux)) ? i_fuerza : i;
    }
    mt.setearFuerzaMaxima(x_max,i_fuerza);

	return x;
}

void printMatriz2(MatrizBanda& m) {
	for (int i = 0; i < m.getDim().first ; ++i) {
		for (int j = 0; j < m.getDim().second ; ++j) {
			cout << m.get(i,j) << " "; //get(i,j) sólo acá!
		}
		cout << endl;
	}
	cout << endl;
}

void testBackwardSubstitution() {
	MatrizBanda m(4,4);
    
    m.set(0,0,1);
    m.set(0,1,2);
    m.set(0,2,3);
    m.set(0,3,4);

    m.set(1,0,0);
    m.set(1,1,2);
    m.set(1,2,6);
    m.set(1,3,12);

    m.set(2,0,0);
    m.set(2,1,0);
    m.set(2,2,6);
    m.set(2,3,24);

    m.set(3,0,0);
    m.set(3,1,0);
    m.set(3,2,0);
    m.set(3,3,24);

    vector<num> b;
    b.push_back(2);
    b.push_back(8);
    b.push_back(18);
    b.push_back(24);

    printMatriz2(m);
    for(int i=0; i < b.size(); ++i) {
    	cout << "b[" << i << "]: " << b[i];
    	if(i+1 < b.size())
    		cout << " ";
    	else
    		cout << endl;
    }
    vector<num>* x;
    x = backwardSubstitution(m,b);

    for(int i=0; i < x->size(); ++i) {
    	cout << "x[" << i << "]: " << (*x)[i];
    	if(i+1 < x->size())
    		cout << " ";
    	else
    		cout << endl;
    }

    delete x;
}
