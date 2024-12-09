#ifndef FOXLEG_H
#define FOXLEG_H
#include "objeto3d.h"

class foxleg : public Objeto3D
{
public:

    // Dimensiones de las patas
    float anchoPata = 0.15;  // Ancho de la pata
    float altoPata = 0.3;   // Altura de la pata
    float profundidadPata = 0.15;  // Profundidad de la

    // Color de las patas (marrón oscuro)
    int colorPataR = 101;
    int colorPataG = 67;
    int colorPataB = 33;

    // Dimensiones de las pezuñas
    float anchoPatita = 0.15;
    float altoPatita = 0.05;
    float profundidadPatita = 0.15;

    float offset_x;
    float offset_z;

    foxleg(Vertice* o, float offsetX, float offsetZ, Linea* rotationAxe);
    virtual Objeto3D* copia() override;
};

#endif // FOXLEG_H
