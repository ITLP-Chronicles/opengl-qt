#include "linea.h"

Linea::Linea() {
    p1 = new Vertice();
    p2 = new Vertice();
    sig=nullptr;
}

Linea::~Linea() {
    delete p1;
    delete p2;
}

Linea::Linea(Vertice *p1, Vertice *p2) {
    this->p1 = p1;
    this->p2 = p2;
    sig=nullptr;
}

Linea::Linea(float x1,float y1,float z1, float x2,float y2, float z2) {
    p1 = new Vertice(x1,y1,z1);
    p2 = new Vertice(x2,y2,z2);
    sig=nullptr;
}

void Linea::desplegar() {
    /*
    float dx = p2->x - p1->x;
    float dy = p2->y - p1->y;
    int pixelsToTravel = (abs(dx) > abs(dy) ? abs(dx) : abs(dy));
    float xIncrement = dx /pixelsToTravel;
    float yIncrement = dy /pixelsToTravel;
    Vertice *p = p1->copia();
    for(int i = 0; i <= pixelsToTravel; i++){
        p->desplegar(painter);
        p->x += xIncrement;
        p->y += yIncrement;
    }
    delete p;
    */
}

Linea* Linea::copia()
{
    Linea *linea = new Linea(p1->copia(),p2->copia());
    linea->sig=nullptr;
    return linea;
}

void Linea::transformar(Matriz3D* matriz)
{
    p1->transformar(matriz);
    p2->transformar(matriz);
}



