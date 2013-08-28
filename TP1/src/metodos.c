#include <stdio.h>
#include "metodos.h"
#define abs(x) (x >= 0 ? x : - x)
#define max(x,y) (x > y ? x : y)
#define sg(x) (x >= 0 ? 1 : -1)
#define inf 1.0/0.0

num errorTolerable = epsilon;
#ifdef MEDIR
int itersBiseccion = 0;
int itersNewton = 0;

void setearErrorTolerable(num error){
	errorTolerable = error;
}

void resetearContadores() {
	itersBiseccion = 0;
	itersNewton = 0;
}

int getItersNewton(){
	return itersNewton;
}

int getItersBiseccion(){
	return itersBiseccion;
}
#endif

int parar(num alpha, num raiz, num raizAnterior, short iters) {
	if (iters > 100)
		return 1;
	if (abs((raiz - raizAnterior)/raizAnterior) < errorTolerable) {
		return 1;
	}
	return 0;
}

num sqrtNewton(num alpha){
	#define f(x) x*x - alpha
	#define g(x) (x + alpha/x)/2
	//bisección hasta asegurar a >= 0.82*b, max(g(a), g(b)) <= b
	if (iguales(alpha, 0)) return 0;
	if (iguales(alpha, 1)) return 1;
	num a = 0;
	num b = alpha > 1 ? alpha : 1;
	// printf("Empecé a achicar el intervalo\n");
	while(! (a >= 0.58*b && g(a)<= b && g(b) <= b)) {
		// printf("[%.9f, %.9f]     ", a,b);
		num medio = (a + b)/2;
		num fDeMedio = f(medio);
		if (iguales(fDeMedio, 0))
			return medio;
		if (fDeMedio < 0) {
			a = medio;
		} else {
			b = medio;
		}
		#ifdef MEDIR
			++itersBiseccion;
		#endif
	}
	// printf("\nTerminé de achicar el intervalo: [%.9f, %.9f] en %d pasos\n", a,b, bisecciones);
	num raiz = (a + b) /2;

	// num raiz = alpha > 1 ? alpha : 1;
	num raizAnterior = inf;
	short iters;
	while (!parar(alpha, raiz, raizAnterior, iters)){
		raizAnterior = raiz;
		raiz = g(raiz);
		++iters;
		// printf("%.15f \n", raiz);
	}
	#ifdef MEDIR
		itersNewton = iters;
	#endif
	return raiz;
}

num invSqrtNewton(num alpha){
	return 1/sqrtNewton(alpha);
}

num invSqrtENewton(num alpha){
	//e(x) = 1/x^2 - alpha
	#undef g
	#define g(x) (-alpha/2.0 * x*x*x + 1.5*x)
	#define gPrima(x) (1.5 * (1 - alpha * x*x))

	// num a = 0;
	// num b = alpha > 1 ? alpha : 1/alpha;
	//terminar si alpha = 1 o alpha = 0

	//bisección cabeza para asegurar la convergencia de newton
	// unsigned char bisecciones = 0;

	// while (!( (abs(gPrima(a)) < 1) && (abs(gPrima(b)) < 1 && a <= g(a) && g(b) <= b))){
	// 	num medio = (a+b)/2;
	// 	num gPrimaDeMedio = gPrima(medio);
	// 	if (iguales(gPrimaDeMedio, 0))
	// 		return medio;
	// 	if (gPrimaDeMedio < 0) {
	// 		b = medio;
	// 	} else {
	// 		a = medio;
	// 	}
	// 	++bisecciones;
	// }
	// printf("\nTerminé de achicar el intervalo: [%.9f, %.9f] en %d pasos\n", a,b, bisecciones);
	// num raiz = (a+b)/2;
	// num raiz = alpha > 1 ? 1/alpha : alpha;
	num raiz = alpha > 1 ? (1/(1.733 * alpha)) : alpha/1.733;
	num raizAnterior = inf;
	unsigned short iters = 0;
	while (!parar(alpha, raiz, raizAnterior, iters)){
		raizAnterior = raiz;
		raiz = g(raiz);
		++iters;
		// printf("%.15f \n", raiz);
	}
	#ifdef MEDIR
		itersNewton = iters;
	#endif
		// printf("%d :", iters);
	return raiz;
}

num invSqrtEFlash(num alpha) {
	#undef g
	#define g(x) (1/alpha * 1/x - (x - alpha * x*x*x)/2)
	//g'' no se anula nunca, o sea, g' es siempre crec o decrec.
	//g' tiene un 0 en 1/sqrt(a), podemos bisectarla para buscar un buen intervalo para aplicar g
	#undef gPrima
	#define gPrima(x) (-1/alpha * 1/(x*x) - (1 - 3*alpha * x*x)/2)

	num a = 1/alpha;
	num b = 1;
	char sgA = sg(gPrima(a));
	while (!( (abs(gPrima(a)) < 1) && (abs(gPrima(b)) < 1))){
		// printf("g\'(%.15f) = %.15f, g\'(%.15f) = %.15f\n", a, gPrima(a), b, gPrima(b));
		num medio = (a+b)/2;
		num gPrimaDeMedio = gPrima(medio);
		if(iguales(gPrimaDeMedio, 0))
			return medio;
		if (sg(gPrimaDeMedio) == sgA){
			a = medio;
		} else {
			b = medio;
		}
		#ifdef MEDIR
		++itersBiseccion;
		#endif

		// printf("g\'(%.15f) = %.15f, [%.15f, %.15f] \n", medio, gPrimaDeMedio, a, b);
	}
	// printf("Terminé de achicar el intervalo: [%.9f, %.9f] en %d pasos\n", a,b, bisecciones);

	num raiz = (a+b)/2;

	num raizAnterior = inf;
	unsigned short iters = 0;
	while (!parar(alpha, raiz, raizAnterior, iters)){
		raizAnterior = raiz;
		raiz = g(raiz);
		++iters;

		// printf("%.15f \n", raiz);
	}
	#ifdef MEDIR
		itersNewton = iters;
	#endif
	return raiz;
}

num biseccion(num alpha){
	#undef f
	#define f(x) (x*x - alpha)
	num a = 0;
	num b = alpha > 1 ? alpha : 1;
	// printf("Empecé a achicar el intervalo\n");
	num raiz = (a + b)/2;
	short iters = 0;
	//por cómo es la bisección, nos conviene mirar el tamaño del intervalo
	//el error absoluto es <= (b-a)/2, entonces el relativo es <= (b-a/2) /((a+b)/2) = (b-a)/(a+b)
	while((1/a - 1/b)/(2/(a+b)) > errorTolerable && iters < 100) {
	// while(iters < 1000) {
		raiz = (a + b)/2;
		num fDeMedio = f(raiz);
		if (iguales(fDeMedio, 0))
			break;
		if (fDeMedio < 0) {
			a = raiz;
		} else {
			b = raiz;
		}
		++iters;
		// printf("%.15f\n", errorTolerable);
	}
	#ifdef MEDIR
		itersBiseccion = iters;
	#endif
	// printf("Hice %d pasos\n", iters);
	return 1/raiz;
}

double invSqrtHW(double alpha){
	double res, uno = 1.0;
	__asm__("movd %1, %%xmm0; sqrtsd %%xmm0, %%xmm0; movd %%xmm1, %2 ; divsd %%xmm0, %%xmm1; movd %%xmm1, %0"
			: "=r" (res) /* output */
			: "r" (alpha), "r" (uno) /*input*/
	);
	return res;
}
