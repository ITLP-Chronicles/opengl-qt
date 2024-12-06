#include "foxleg.h"
#include "utils.h"

foxleg::foxleg(Vertice* o) {

    // Pata 1 - Esquina inferior izquierda delantera
    CrearPrismaRectangular(this,
                           o->x,
                           o->y - altoPata,
                           o->z - 1 + profundidadPata,
                           anchoPata, altoPata, profundidadPata,
                           colorPataR, colorPataG, colorPataB);
    CrearPrismaRectangular(this,
                           o->x,
                           o->y - altoPata - altoPatita,
                           o->z - 1 + profundidadPata,
                           anchoPatita, altoPatita, profundidadPatita,
                           31,32,38);
    /*
    // Pata 2 - Esquina inferior derecha delantera
    CrearPrismaRectangular(this,
                           o->x + 0.5 - anchoPata,
                           o->y - altoPata,
                           o->z - 1 + profundidadPata,
                           anchoPata, altoPata, profundidadPata,
                           colorPataR, colorPataG, colorPataB);
    CrearPrismaRectangular(this,
                           o->x + 0.5 - anchoPata ,
                           o->y - altoPata - altoPatita,
                           o->z - 1 + profundidadPata,
                           anchoPatita, altoPatita, profundidadPatita,
                           31,32,38);


    // Pata 3 - Esquina inferior izquierda trasera
    CrearPrismaRectangular(this,
                           o->x,
                           o->y - altoPata,
                           o->z ,
                           anchoPata, altoPata, profundidadPata,
                           colorPataR, colorPataG, colorPataB);
    CrearPrismaRectangular(this,
                           o->x,
                           o->y - altoPata - altoPatita,
                           o->z ,
                           anchoPatita, altoPatita, profundidadPatita,
                           31,32,38);

    // Pata 4 - Esquina inferior derecha trasera
    CrearPrismaRectangular(this,
                           o->x + 0.5 - anchoPata,
                           o->y - altoPata,
                           o->z,
                           anchoPata, altoPata, profundidadPata,
                           colorPataR, colorPataG, colorPataB);
    CrearPrismaRectangular(this,
                           o->x + 0.5 - anchoPata,
                           o->y - altoPata - altoPatita,
                           o->z,
                           anchoPatita, altoPatita, profundidadPatita,
                           31,32,38);
*/
}
