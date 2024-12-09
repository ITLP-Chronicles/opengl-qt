#ifndef FOXTAIL_H
#define FOXTAIL_H
#include "objeto3d.h"

class foxtail : public Objeto3D
{
public:
    foxtail(Vertice* o, Linea* rotationAxe);
    virtual Objeto3D* copia() override;
};

#endif // FOXTAIL_H
