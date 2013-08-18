#ifndef metodos_h
#define metodos_h

typedef double num;
#define epsilon 0.0000001
#define iguales(x,y)  -epsilon < (x - y) && (x - y) < epsilon

//método de Newton para f(x) = x^2 - alpha
num sqrtNewton(num alpha);

#endif