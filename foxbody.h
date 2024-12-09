#ifndef FOXBODY_H
#define FOXBODY_H
#include "objeto3d.h"

class foxbody : public Objeto3D
{
public:
    foxbody(Vertice* o, Linea* rotationAxe);
    virtual Objeto3D* copia() override;
};

#endif // FOXBODY_H
