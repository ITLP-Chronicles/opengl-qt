#include "foxbody.h"
#include "utils.h"

foxbody::foxbody(Vertice* o) {
    // Crear el cuerpo principal
    CrearPrismaRectangular(this, o->x, o->y, o->z, 0.5, 0.5, 1, 221, 129, 52); // Body
}
