#include "matriz3d.h"

Matriz3D::Matriz3D(){
    datos[0][0] = 1;
    datos[0][1] = 0;
    datos[0][2] = 0;
    datos[0][3] = 0;
    datos[1][0] = 0;
    datos[1][1] = 1;
    datos[1][2] = 0;
    datos[1][3] = 0;
    datos[2][0] = 0;
    datos[2][1] = 0;
    datos[2][2] = 1;
    datos[2][3] = 0;
    datos[3][0] = 0;
    datos[3][1] = 0;
    datos[3][2] = 0;
    datos[3][3] = 1;
}

Matriz3D::Matriz3D(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l){
    datos[0][0] = a;
    datos[0][1] = b;
    datos[0][2] = c;
    datos[0][3] = d;
    datos[1][0] = e;
    datos[1][1] = f;
    datos[1][2] = g;
    datos[1][3] = h;
    datos[2][0] = i;
    datos[2][1] = j;
    datos[2][2] = k;
    datos[2][3] = l;
    datos[3][0] = 0;
    datos[3][1] = 0;
    datos[3][2] = 0;
    datos[3][3] = 1;
}

Matriz3D::Matriz3D(float valores[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->datos[i][j] = valores[i][j];
        }
    }
}

Matriz3D::Matriz3D(Matriz3D* otraMatriz) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->datos[i][j] = otraMatriz->datos[i][j];
        }
    }
}

//Métodos

Matriz3D* Matriz3D::mult(Matriz3D *otraMatriz) {
    Matriz3D* resultado = new Matriz3D();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            resultado->datos[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                resultado->datos[i][j] += this->datos[i][k] * otraMatriz->datos[k][j];
            }
        }
    }
    return resultado;
}

Matriz3D* Matriz3D::copia() {
    return new Matriz3D(datos);
}
