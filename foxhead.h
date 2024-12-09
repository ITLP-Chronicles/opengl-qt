#ifndef FOXHEAD_H
#define FOXHEAD_H

#include "objeto3d.h"

class foxhead : public Objeto3D
{
public:
    foxhead(Vertice* o, Linea* rotationAxe);
    virtual Objeto3D* copia() override;
};

#endif // FOXHEAD_H
