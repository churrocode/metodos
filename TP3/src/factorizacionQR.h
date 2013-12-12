#ifndef FACTORIZACIONQR_H
#define	FACTORIZACIONQR_H
#include "MatrizEsparsa.h"

MatrizEsparsa* givensDosColumnas(MatrizEsparsa& A);
void householder2Cols(MatrizEsparsa& A, vector<num>& b);
void testHouseholder2Cols();
vector<num> backwardSubstitution2Cols(MatrizEsparsa& A, vector<num>& b);

#endif	/* FACTORIZACIONQR_H */

