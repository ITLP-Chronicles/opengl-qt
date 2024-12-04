#ifndef OBJETO3D_H
#define OBJETO3D_H

#include "superficie.h"

class Objeto3D
{
public:
    vector<Superficie*> superficies;
    Objeto3D();
    ~Objeto3D();
    void agregar(Superficie*);
    void desplegar();
    Objeto3D *copia();
    void rotar(float,Linea*);
    void transformar(Matriz3D*);
};

#endif // OBJETO3D_H
