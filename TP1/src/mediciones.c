#include <stdio.h>
#include "metodos.h"
#ifdef MEDIR
	extern itersBiseccion, itersNewton, errorTolerable;
#endif

//no cambiar el orden de este array, nos vamos a referir a estos métodos por su número!
num(*metodos[4])(num) = {&invSqrtNewton, &invSqrtENewton, &invSqrtEFlash, &biseccion};
double ordenes[9] = {0.000000001, 0.000001, 0.001, 0.1, 1, 10, 1000, 1000000, 1000000000};
double alphas[3]  = {1, 4, 7};

void aplicarAlRango(void (*medir)(), num (*metodo)(), FILE* out){
	int i = 0;
	for (; i < 8; ++i){
		double orden = ordenes[i];
		double paso = orden/10;
		int j = 0;
		for (j = 0; j < 2; ++j) {
			double centro = alphas[j] * orden;
			int k = -10;
			for (; k <= 10; ++k){
				double alpha = centro + paso*k;
				if (alpha > 0) {
					medir(alpha, metodo, out);
				}
			}
		}
	}
}

void medirError(num alpha, num (*metodo)(), FILE* out){
	double laRaiz = metodo(alpha);
	double laRaizPosta = invSqrtHW(alpha);
	double elError = laRaiz - laRaizPosta;
	double elErrorRelativo = elError/laRaiz;
	fprintf(out, "%.20f : %.20f : %.20f : %.20f : %.20f\n", alpha, laRaiz, laRaizPosta, elError, elErrorRelativo);
}

void buscarErrorTolerable(){
	num errores[6] = {0.001, 0.000001, 0.000000001, 0.000000000001, 0.000000000000001, 0.000000000000000001};
	int i,j = 0;
	for (j = 0; j < 4; j++) {
		char archivo[150];
		snprintf(archivo, 150, "../data/buscarParadaMetodo%d.dat", j);
		FILE* fileDesc = fopen(archivo, "w");
		fprintf(fileDesc, "# Errores de medición para este método según cota para el error relativo en el criterio de parada.\n# Se miden 6 valores para el rango de siempre, se indica el comienzo de la medición correspondiente para cada valor de error con una línea '* tolerancia: 10^-i'\n");
		for (i = 0; i < 6; ++i) {
			fprintf(fileDesc, "# alpha : invSqrt(alpha) : invSqrt(alpha) HWare : error : errorRelativo\n");
			fprintf(fileDesc, "* tolerancia: 10^-%d\n", (i+1)*3 );
				errorTolerable = errores[i];
				aplicarAlRango(&medirError, metodos[j], fileDesc);
		}
		fclose(fileDesc);
	}
}

void contarIteraciones(num alpha, num(*metodo)(), FILE* out){
	#ifdef MEDIR
	resetearContadores();
	double laRaiz = metodo(alpha);
	fprintf(out, "%.20f : %d : %d : %d\n", alpha, itersBiseccion, itersNewton, itersBiseccion + itersNewton);
	#endif
}

int main(){
	buscarErrorTolerable();
	return 0;
}
