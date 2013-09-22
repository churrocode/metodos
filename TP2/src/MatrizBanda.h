#ifndef MATRIZBANDA_H
#define	MATRIZBANDA_H

class MatrizBanda {
public:
    MatrizBanda(int n, int m, int p, int q);
    MatrizBanda(const MatrizBanda& orig);
    virtual ~MatrizBanda();
    float* getValues();
    //operator[](int i, int j);
private:
    int n;
    int m;
    int p;
    int q;
    float values[];
};

#endif	/* MATRIZBANDA_H */

