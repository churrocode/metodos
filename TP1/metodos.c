#include <stdio.h>
#define epsilon 0.0000001
#define abs(x) x >= 0 ? : - x
#define iguales(x,y)  -epsilon < (x - y) && (x - y) < epsilon
#define max(x,y) x > y ? x : y

typedef double num;

int parar(num alpha, num raiz, num raizAnterior, short iters) {
	if (iters > 10000)
		return true;
	return false;
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
		if (c > 10) break;
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

int main(){
	num raizDe2 = sqrtNewton(2);
	printf("************ La raíz de 2 es %.15f\n", raizDe2);
	num raizDe20000 = sqrtNewton(20000);
	printf("************ La raíz de 20000 es %.15f\n", raizDe20000);
	num raizDe4 = sqrtNewton(4);
	printf("************ La raíz de 4 es %.15f\n", raizDe4);
	num raizDe100 = sqrtNewton(100);
	printf("************ La raíz de 100 es %.15f\n", raizDe100);
 	num raizDe01 = sqrtNewton(0.01);
	printf("************ La raíz de 0.01 es %.15f\n",raizDe01);
	num raizDe0001 = sqrtNewton(0.0001);
	printf("************ La raíz de 0.0001 es %.15f\n",raizDe0001);
	return 0;
}

