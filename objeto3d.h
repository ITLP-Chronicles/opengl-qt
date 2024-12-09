#ifndef OBJETO3D_H
#define OBJETO3D_H

#include "superficie.h"
#include "linea.h"
#include "linea.h"

class Objeto3D
{
public:
    std::vector<Superficie*> superficies;
    Linea* rotationAxe;
    Objeto3D();
    ~Objeto3D();
    void agregar(Superficie*);
    void desplegar();
    virtual Objeto3D* copia() = 0;
    void rotar(float,Linea*);
    void transformar(Matriz3D*);
    Vertice* calcularCentroide() const;
};

#endif // OBJETO3D_H
