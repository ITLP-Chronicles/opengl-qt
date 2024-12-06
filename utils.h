#ifndef UTILS_H
#define UTILS_H
#include "objeto3d.h"

// Function to create a rectangular prism with a single color and optional transparency
    void CrearPrismaRectangular(Objeto3D* objeto,
                           float x, float y, float z,
                           float ancho, float alto, float profundo,
                           float colorR = 1.0f,
                           float colorG = 0.0f,
                           float colorB = 0.0f,
                           float opacidad = 1.0f);

// Overloaded function to create a rectangular prism with specific colors per face and optional transparency
void CrearPrismaRectangular(Objeto3D* objeto,
                            float x, float y, float z,
                            float ancho, float alto, float profundo,
                            float colorFrontal[3],
                            float colorTrasera[3],
                            float colorSuperior[3],
                            float colorInferior[3],
                            float colorDerecha[3],
                            float colorIzquierda[3],
                            float opacidad = 1.0f);
void Graficar(Objeto3D* objeto3D);

#endif // UTILS_H
