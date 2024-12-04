#ifndef LINEA_H
#define LINEA_H

#include "vertice.h"

class Linea
{
public:
    Vertice *p1;
    Vertice *p2;
    Linea *sig;
    Linea();
    ~Linea();
    Linea(Vertice *,Vertice *);
    Linea(float,float,float,float,float,float);
    void desplegar();
    Linea *copia();
    void transformar(Matriz3D*);
};

#endif // LINEA_H
