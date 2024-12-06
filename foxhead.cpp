#include "foxhead.h"
#include "utils.h"

foxhead::foxhead(Vertice* o) {
    // Dimensiones de la cabeza
    float anchoCabeza = 0.6;  // Ancho de la cabeza
    float altoCabeza = 0.5;   // Altura de la cabeza
    float profundidadCabeza = -0.45;  // Profundidad de la cabeza

    CrearPrismaRectangular(this, o->x-0.05, o->y-0.07, o->z, anchoCabeza, altoCabeza, profundidadCabeza, 221, 129, 52); // Head
    // Dimensiones de las orejas
    float anchoOreja = 0.1;  // Ancho de la oreja
    float altoOreja = 0.18;   // Altura de la oreja
    float profundidadOreja = 0.1;  // Profundidad de la oreja

    // Oreja 1 - Derecha
    CrearPrismaRectangular(this,
                           o->x + anchoOreja/2,
                           o->y + altoCabeza - 0.07,
                           o->z - profundidadCabeza - profundidadOreja,
                           anchoOreja, altoOreja, profundidadOreja,
                           0, 0, 0);
    CrearPrismaRectangular(this,
                           o->x + anchoOreja/2 + 0.02,
                           o->y + altoCabeza - 0.07,
                           o->z - profundidadCabeza - profundidadOreja,
                           anchoOreja - 0.04, altoOreja - 0.02, -0.007,
                           230, 230, 230);

    // Oreja 2 - Izquierda
    CrearPrismaRectangular(this,
                           o->x + anchoCabeza - anchoOreja * 5/2,
                           o->y + altoCabeza - 0.07,
                           o->z - profundidadCabeza - profundidadOreja,
                           anchoOreja, altoOreja, profundidadOreja,
                           0, 0, 0);
    CrearPrismaRectangular(this,
                           o->x + anchoCabeza - anchoOreja * 5/2 + 0.02,
                           o->y + altoCabeza - 0.07,
                           o->z - profundidadCabeza - profundidadOreja,
                           anchoOreja - 0.04, altoOreja - 0.02, -0.007,
                           230, 230, 230);
}
