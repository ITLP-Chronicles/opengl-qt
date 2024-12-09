#include "foxleg.h"
#include "utils.h"

foxleg::foxleg(Vertice* o, float offsetX, float offsetZ, Linea* rotationAxe) {
    this->offset_x = offsetX;
    this->offset_z = offsetZ;
    this->thisVertex = o;
    this->rotationAxe = rotationAxe;
    // Crear la parte principal de la pata
    CrearPrismaRectangular(this,
                           o->x + offsetX,
                           o->y - this->altoPata,
                           o->z + offsetZ,
                           this->anchoPata, this->altoPata, this->profundidadPata,
                           this->colorPataR, this->colorPataG, this->colorPataB);

    // Crear la parte inferior (patita)
    CrearPrismaRectangular(this,
                           o->x + offsetX,
                           o->y - this->altoPata - this->altoPatita,
                           o->z + offsetZ,
                           this->anchoPatita, this->altoPatita, this->profundidadPatita,
                           31, 32, 38);
}

Objeto3D* foxleg::copia() {
    foxleg* copy = new foxleg(this->thisVertex->copia(), this->offset_x, this->offset_z, this->rotationAxe->copia());
    for (Superficie* superficie : superficies) {
        copy->agregar(superficie->copia());
    }
    return copy;
}
