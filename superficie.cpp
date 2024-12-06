// superficie.cpp (implementation)
#include "superficie.h"

Superficie::Superficie(float r, float v, float a, float opacidad) {
    this->r = r;
    this->v = v;
    this->a = a;
    this->opacidad = opacidad;
}


Superficie::~Superficie() {
    for (Vertice* vertice : vertices) {
        delete vertice;
    }
}

void Superficie::agregar(Vertice* vertice) {
    vertices.push_back(vertice);
}

Superficie* Superficie::copia() {
    Superficie* copia = new Superficie(r, v, a, opacidad);
    for (Vertice* vertice : vertices) {
        copia->agregar(vertice->copia());
    }
    return copia;
}

void Superficie::desplegar() {
    float x1 = vertices[0]->x;
    float y1 = vertices[0]->y;
    float z1 = vertices[0]->z;
    float x2 = vertices[1]->x;
    float y2 = vertices[1]->y;
    float z2 = vertices[1]->z;
    float x3 = vertices[2]->x;
    float y3 = vertices[2]->y;
    float z3 = vertices[2]->z;

    float nx = y1*(z2-z3) + y2*(z3-z1) + y3*(z1-z2);
    float ny = z1*(x2-x3) + z2*(x3-x1) + z3*(x1-x2);
    float nz = x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2);

    float m = sqrt(pow(nx,2) + pow(ny,2) + pow(nz,2));

    glNormal3f(nx/m, ny/m, nz/m);

    // Usar glColor4f para incluir el canal alfa
    glColor4f(r/255.0f, v/255.0f, a/255.0f, opacidad);

    glBegin(GL_POLYGON);
    for (Vertice* v : vertices) {
        v->desplegar();
    }
    glEnd();
}

void Superficie::transformar(Matriz3D* M) {
    for (Vertice* vertice : vertices) {
        vertice->transformar(M);
    }
}
