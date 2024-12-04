// superficie.h (header)
#ifndef SUPERFICIE_H
#define SUPERFICIE_H

#include <vector>
#include <cmath>
#include <GL/gl.h>
#include "vertice.h"
#include "matriz3d.h"

class Superficie {

public:
    // Constructor con opacidad por defecto
    Superficie(float r, float v, float a, float opacidad = 1.0f);
    std::vector<Vertice*> vertices;
    float r, v, a, opacidad;

    // Destructor
    ~Superficie();

    // Agregar un vértice
    void agregar(Vertice* vertice);

    // Crear una copia de la superficie
    Superficie* copia();

    // Desplegar la superficie
    void desplegar();

    // Transformar la superficie
    void transformar(Matriz3D* M);
};

#endif // SUPERFICIE_H
