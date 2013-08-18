#include <stdio.h>
#include "metodos.h"
#define abs(x) x >= 0 ? : - x
#define max(x,y) x > y ? x : y

int parar(num alpha, num raiz, num raizAnterior, short iters) {
	if (iters > 10000)
		return 1;
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
	while(! (a >= 0.82*b && g(a)<= b && g(b) <= b)) {
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
	}
	// printf("Terminé de achicar el intervalo: [%.9f, %.9f]\n", a,b);
	num raiz = (a + b) /2;
	num raizAnterior = 0;
	unsigned short iters = 0;
	while (!parar(alpha, raiz, raizAnterior, iters)){
		raizAnterior = raiz;
		raiz = g(raiz);
		++iters;
	}
	return raiz;
}
