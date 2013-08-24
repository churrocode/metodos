#include <stdio.h>
#include "metodos.h"

int main(int argc, char* argv[]){
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

	num invRaizDe4 = invSqrtENewton(4);
	//esta sale en la bisección
	printf("************ La inv raíz de 4 es %.15f\n", invRaizDe4);
	num invRaizDe9 = invSqrtENewton(9);
	printf("************ La inv raíz de 9 es %.15f\n", invRaizDe9);
	num invRaizDe001 = invSqrtENewton(0.01);
	printf("************ La inv raíz de 0.01 es %.15f\n", invRaizDe001);

	num invRaizFlashDe4 = invSqrtEFlash(4);
	//esta sale en la bisección
	printf("************ La inv raíz flash de 4 es %.15f\n", invRaizFlashDe4);
	num invRaizFlashDe9 = invSqrtEFlash(9);
	printf("************ La inv raíz flash de 9 es %.15f\n", invRaizFlashDe9);
	num invRaizFlashDe001 = invSqrtEFlash(0.01);
	printf("************ La inv raíz flash de 1/100 es %.15f\n", invRaizFlashDe001);
	num invRaizFlashDe04 = invSqrtEFlash(0.04);
	printf("************ La inv raíz flash de 1/25 es %.15f\n", invRaizFlashDe04);
	num invRaizFlashDe0001 = invSqrtEFlash(0.0001);
	printf("************ La inv raíz flash de 1/10000 es %.15f\n", invRaizFlashDe0001);
	return 0;
}
