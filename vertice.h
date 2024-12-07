#ifndef VERTICE_H
#define VERTICE_H

#include <QOpenGLWidget>
#include "matriz3d.h"

class Vertice
{
public:
    float x;
    float y;
    float z;
    Vertice();
    Vertice(float,float,float);
    void desplegar();
    Vertice *copia();
    void transformar(Matriz3D*);

};

#endif // VERTICE_H
