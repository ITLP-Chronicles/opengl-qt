#ifndef MATRIZ3D_H
#define MATRIZ3D_H

class Matriz3D
{
public:
    float datos[4][4];
    Matriz3D();
    Matriz3D(float,float,float,float,
             float,float,float,float,
             float,float,float,float);
    Matriz3D(float [4][4]);
    Matriz3D(Matriz3D *);
    Matriz3D *copia();
    Matriz3D *mult(Matriz3D*);
    void desplegar();
};

#endif // MATRIZ3D_H
