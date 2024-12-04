#include "vertice.h"

Vertice::Vertice() {
    x=0;
    y=0;
}

Vertice::Vertice(float x,float y, float z) {
    this->x=x;
    this->y=y;
    this->z=z;
}

void Vertice::desplegar() {
    glVertex3f(x,y,z);
}

Vertice* Vertice::copia(){
    Vertice *pCopia = new Vertice(x,y,z);
    return pCopia;
}

void Vertice::transformar(Matriz3D* matriz)
{
    float xa = x;
    float ya = y;
    float za = z;
    x = matriz->datos[0][0] * xa +
        matriz->datos[0][1] * ya +
        matriz->datos[0][2] * za +
        matriz->datos[0][3];
    y = matriz->datos[1][0] * xa +
        matriz->datos[1][1] * ya +
        matriz->datos[1][2] * za +
        matriz->datos[1][3];
    z = matriz->datos[2][0] * xa +
        matriz->datos[2][1] * ya +
        matriz->datos[2][2] * za +
        matriz->datos[2][3];
}







