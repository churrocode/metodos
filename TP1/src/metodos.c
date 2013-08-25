#include <stdio.h>
#include "metodos.h"
#define abs(x) (x >= 0 ? x : - x)
#define max(x,y) (x > y ? x : y)
#define sg(x) (x >= 0 ? 1 : -1)

int parar(num alpha, num raiz, num raizAnterior, short iters) {
	if (iters > 10)
		return 1;
	if (abs((raiz - raizAnterior)/raizAnterior) < epsilon) {
		// printf("%.25f\n", (raiz - raizAnterior)/raizAnterior);
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
	unsigned char bisecciones = 0;
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
		++bisecciones;
	}
	printf("\nTerminé de achicar el intervalo: [%.9f, %.9f] en %d pasos\n", a,b, bisecciones);
	num raiz = (a + b) /2;
	num raizAnterior = 0; //si raiz está cerca de 0, esto nos está arruinando la vida!
	unsigned short iters = 0;
	while (!parar(alpha, raiz, raizAnterior, iters)){
		raizAnterior = raiz;
		raiz = g(raiz);
		// printf("%.15f \n", raiz);
		++iters;
	}
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

	num a = 0;
	num b = alpha > 1 ? alpha : 1/alpha;
	//terminar si alpha = 1 o alpha = 0

	//bisección cabeza para asegurar la convergencia de newton
	unsigned char bisecciones = 0;

	while (!( (abs(gPrima(a)) < 1) && (abs(gPrima(b)) < 1 && a <= g(a) && g(b) <= b))){
		num medio = (a+b)/2;
		num gPrimaDeMedio = gPrima(medio);
		if (iguales(gPrimaDeMedio, 0))
			return medio;
		if (gPrimaDeMedio < 0) {
			b = medio;
		} else {
			a = medio;
		}
		++bisecciones;
	}
	printf("\nTerminé de achicar el intervalo: [%.9f, %.9f] en %d pasos\n", a,b, bisecciones);
	num raiz = (a+b)/2;
	num raizAnterior = 0;
	unsigned short iters = 0;
	while (!parar(alpha, raiz, raizAnterior, iters)){
		raizAnterior = raiz;
		raiz = g(raiz);
		++iters;
		// printf("%.15f \n", raiz);
	}
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
	unsigned char bisecciones = 0;
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
		++bisecciones;
		// printf("g\'(%.15f) = %.15f, [%.15f, %.15f] \n", medio, gPrimaDeMedio, a, b);
	}
	printf("\nTerminé de achicar el intervalo: [%.9f, %.9f] en %d pasos\n", a,b, bisecciones);

	num raiz = (a+b)/2;
	num raizAnterior = 1.0/0.0;
	unsigned short iters = 0;
	while (!parar(alpha, raiz, raizAnterior, iters)){
		raizAnterior = raiz;
		raiz = g(raiz);
		++iters;
		// printf("%.15f \n", raiz);
	}
	return raiz;
}
