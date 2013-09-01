#include <stdio.h>
#include "metodos.h"
#include <time.h>
#include <sys/time.h>
#ifdef MEDIR
	extern itersBiseccion, itersNewton, errorTolerable, topeItersBiseccion, conBiseccion;
#endif

//no cambiar el orden de este array, nos vamos a referir a estos métodos por su número!
num(*metodos[4])(num) = {&invSqrtNewton, &invSqrtENewton, &invSqrtEFlash, &biseccion};
double ordenes[9] = {0.000000001, 0.000001, 0.001, 0.1, 1, 10, 1000, 1000000, 1000000000};
double alphas[3]  = {1, 4, 7};

void aplicarAlRango(void (*medir)(), num (*metodo)(), FILE* out){
	int i = 0;
	for (; i < 9; ++i){
		double orden = ordenes[i];
		double paso = orden/10;
		int j = 0;
		for (j = 0; j < 2; ++j) {
			double centro = alphas[j] * orden;
			int k = -10;
			for (; k <= 10; ++k){
				double alpha = centro + paso*k;
				if (alpha > 0) {
					// fprintf(out, "%d :", i);
					medir(alpha, metodo, out, i);
				}
			}
		}
	}
}

void medirError(num alpha, num (*metodo)(), FILE* out, int orden){
	double laRaiz = metodo(alpha);
	double laRaizPosta = invSqrtHW(alpha);
	double elError = laRaiz - laRaizPosta;
	double elErrorRelativo = elError/laRaiz;
	fprintf(out, " %d : %.20f : %.20f : %.20f : %.20f : %.20f\n", orden, alpha, laRaiz, laRaizPosta, elError, elErrorRelativo);
}

void buscarErrorTolerable(){
	num errores[6] = {0.001, 0.000001, 0.000000001, 0.000000000001, 0.000000000000001, 0.000000000000000001};
	int i,j = 0;
	for (j = 0; j < 4; j++) {
		char archivo[150];
		snprintf(archivo, 150, "../data/buscarParadaMetodo%d.dat", j);
		// snprintf(archivo, 150, "HOLA%d.dat", j);
		FILE* fileDesc = fopen(archivo, "w");
		fprintf(fileDesc, "# Errores de medición para este método según cota para el error relativo en el criterio de parada.\n# Se miden 6 valores para el rango de siempre, se indica el final de la medición correspondiente para cada valor de error con una línea '* tolerancia: 10^-i'\n");
		for (i = 0; i < 6; ++i) {
			fprintf(fileDesc, "# orden[i] : alpha : invSqrt(alpha) : invSqrt(alpha) HWare : error : errorRelativo\n");
			setearErrorTolerable(errores[i]);
			aplicarAlRango(&medirError, metodos[j], fileDesc);
			fprintf(fileDesc, "* tolerancia: 10^-%d\n", (i+1)*3 );
		}
		fclose(fileDesc);
	}
}

void contarIteraciones(num alpha, num(*metodo)(), FILE* out, int orden){
	#ifdef MEDIR
	resetearContadores();
	int topeItersBiseccion = getTopeItersBiseccion();
	double laRaiz = metodo(alpha);
	fprintf(out, "%d : %.20f : %d : %d : %d : %d\n", orden, alpha, itersBiseccion, itersNewton, itersBiseccion + itersNewton, topeItersBiseccion);
	#endif
}

/* retorna "a - b" en segundos */
double timeval_diff(struct timeval *a, struct timeval *b)
{
  printf("%f\n", (double)a->tv_sec + (double)a->tv_usec/1000000 );
  return
	(double)(a->tv_sec + (double)a->tv_usec/1000000) -
	(double)(b->tv_sec + (double)b->tv_usec/1000000);
}


void medirTiempoEjecucion(num alpha, void (*metodo)(), FILE* out, int orden){
	struct timeval t_ini, t_fin;

	gettimeofday(&t_ini, NULL);
	metodo(alpha);
	gettimeofday(&t_fin, NULL);

	num secs = timeval_diff(&t_fin, &t_ini);
//	printf("SECS %f", secs);
	num tiempoEjecucion = secs * 1000000.0;
	fprintf(out, "%d : %.20f : %.16g\n", orden, alpha, tiempoEjecucion);
}

void medirTiempoEjecucion2(num alpha, void (*metodo)(), FILE* out, int orden){
	struct timeval t, t2;
	float microsegundos;
	gettimeofday(&t, NULL);

	metodo(alpha);

	gettimeofday(&t2, NULL);
	microsegundos = ((t2.tv_usec - t.tv_usec) * 1000000.0f);
	printf("%f\n", microsegundos );
	fprintf(out, "%d : %.20f : %.16g\n", orden, alpha, microsegundos);
}

void medirTiempos(){
	int i,j = 0;
	for (j = 0; j < 4; j++) {
		char archivo[150];
		snprintf(archivo, 150, "../data/medirTiemposParaMetodo%d.dat", j);
		FILE* fileDesc = fopen(archivo, "w");
		fprintf(fileDesc, "# Tiempos de ejecución para este método según cota para el error relativo en el criterio de parada.\n# Se miden 6 valores para el rango de siempre, se indica el final de la medición correspondiente para cada valor de error con una línea '* tolerancia: 10^-i'\n");
		fprintf(fileDesc, "# orden[i] : alpha : tiempoEjecucion\n");
		aplicarAlRango(&medirTiempoEjecucion2, metodos[j], fileDesc);
		fclose(fileDesc);
	}
}

void buscarMenorCantidadIters() {
	int i,j = 0;

	for (j = 0; j < 4; j++) {
		char archivo[150];
		if(j == 1){
			char archivoENewtonConBiseccion[150], archivoENewtonSinBiseccion[150];
			snprintf(archivoENewtonConBiseccion, 150, "../data/buscarItersMetodo%d(ConBiseccion).dat", j);
			snprintf(archivoENewtonSinBiseccion, 150, "../data/buscarItersMetodo%d(SinBiseccion).dat", j);
			FILE* fileDescConBis = fopen(archivoENewtonConBiseccion, "w");
			FILE* fileDescSinBis = fopen(archivoENewtonSinBiseccion, "w");
			
			fprintf(fileDescConBis, "# Cantidad de iteraciones para este método con una tolerancia fija.\n# Se miden 6 valores para el rango de siempre'\n");
			fprintf(fileDescConBis, "# orden : alpha : itersBiseccion : itersNewton : itersBiseccion + itersNetwon : topeItersBiseccion\n");

			fprintf(fileDescSinBis, "# Cantidad de iteraciones para este método con una tolerancia fija.\n# Se miden 6 valores para el rango de siempre'\n");
			fprintf(fileDescSinBis, "# orden : alpha : itersBiseccion : itersNewton : itersBiseccion + itersNetwon : topeItersBiseccion\n");
			
			setBiseccion(1);
			aplicarAlRango(&contarIteraciones, metodos[j], fileDescConBis);
			fclose(fileDescConBis);

			setBiseccion(0);
			aplicarAlRango(&contarIteraciones, metodos[j], fileDescSinBis);
			fclose(fileDescSinBis);
			
		}
		else {
			snprintf(archivo, 150, "../data/buscarItersMetodo%d.dat", j);
			FILE* fileDesc = fopen(archivo, "w");
			fprintf(fileDesc, "# Cantidad de iteraciones para este método con una tolerancia fija.\n# Se miden 6 valores para el rango de siempre'\n");
			fprintf(fileDesc, "# orden : alpha : itersBiseccion : itersNewton : itersBiseccion + itersNetwon : topeItersBiseccion\n");
			aplicarAlRango(&contarIteraciones, metodos[j], fileDesc);
			fclose(fileDesc);
		}
	}
}

int main(){
	//medirTiempos();
	//buscarMenorCantidadIters();
	//buscarErrorTolerable();
	return 0;
}
