#ifndef metodos_h
#define metodos_h

typedef double num;
#define epsilon 0.0000000001
#define iguales(x,y)  (-epsilon < (x - y) && (x - y) < epsilon)

//método de Newton para f(x) = x^2 - alpha
num sqrtNewton(num alpha);
//bisección de f(x) = x^2
num biseccion(num alpha);
//método de Newton para 1/(f(x) = x^2 - alpha)
num invSqrtNewton(num alpha);
//método de Newton para e(x) = 1/x^2 - alpha
num invSqrtENewton(num alpha);
//otra función de punto fijo para e(x) = 1/x^2 - alpha
num invSqrtEFlash(num alpha);
//directamente por hardware, para comparar.
double invSqrtHW(double alpha);

#endif
