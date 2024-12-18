#include "foxtail.h"
#include "utils.h"

foxtail::foxtail(Vertice* o, Linea* rotationAxe) {
    this->thisVertex = o;
    this->rotationAxe = rotationAxe;
    CrearPrismaRectangular(this, o->x+0.1, o->y+0.1, o->z-1, 0.3, 0.3, 0.5, 221, 129, 52);

    CrearPrismaRectangular(this, o->x+0.1, o->y+0.1, o->z-1.5, 0.3, 0.3, 0.2, 255, 255, 255);
}

Objeto3D* foxtail::copia() {
    foxtail* copy = new foxtail(this->thisVertex->copia(), this->rotationAxe->copia());
    copy->superficies.clear();
    for (Superficie* superficie : superficies) {
        copy->agregar(superficie->copia());
    }
    return copy;
}
