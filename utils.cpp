#include <superficie.h>
#include <objeto3d.h>

void CrearPrismaRectangular(Objeto3D* objeto, float x, float y, float z, float ancho, float alto, float profundo) {
    // Calcula los vértices del prisma
    float x1 = x, x2 = x + ancho;
    float y1 = y, y2 = y + alto;
    float z1 = z, z2 = z - profundo;

    // Cara frontal
    Superficie* frontal = new Superficie(1, 0, 0);
    frontal->agregar(new Vertice(x1, y1, z1));
    frontal->agregar(new Vertice(x2, y1, z1));
    frontal->agregar(new Vertice(x2, y2, z1));
    frontal->agregar(new Vertice(x1, y2, z1));
    objeto->agregar(frontal);

    // Cara trasera
    Superficie* trasera = new Superficie(1, 0, 0);
    trasera->agregar(new Vertice(x2, y1, z2));
    trasera->agregar(new Vertice(x1, y1, z2));
    trasera->agregar(new Vertice(x1, y2, z2));
    trasera->agregar(new Vertice(x2, y2, z2));
    objeto->agregar(trasera);

    // Cara superior
    Superficie* superior = new Superficie(1, 0, 0);
    superior->agregar(new Vertice(x1, y2, z1));
    superior->agregar(new Vertice(x2, y2, z1));
    superior->agregar(new Vertice(x2, y2, z2));
    superior->agregar(new Vertice(x1, y2, z2));
    objeto->agregar(superior);

    // Cara inferior
    Superficie* inferior = new Superficie(1, 0, 0);
    inferior->agregar(new Vertice(x1, y1, z1));
    inferior->agregar(new Vertice(x1, y1, z2));
    inferior->agregar(new Vertice(x2, y1, z2));
    inferior->agregar(new Vertice(x2, y1, z1));
    objeto->agregar(inferior);

    // Cara derecha
    Superficie* derecha = new Superficie(1, 0, 0);
    derecha->agregar(new Vertice(x2, y1, z1));
    derecha->agregar(new Vertice(x2, y1, z2));
    derecha->agregar(new Vertice(x2, y2, z2));
    derecha->agregar(new Vertice(x2, y2, z1));
    objeto->agregar(derecha);

    // Cara izquierda
    Superficie* izquierda = new Superficie(1, 0, 0);
    izquierda->agregar(new Vertice(x1, y1, z2));
    izquierda->agregar(new Vertice(x1, y1, z1));
    izquierda->agregar(new Vertice(x1, y2, z1));
    izquierda->agregar(new Vertice(x1, y2, z2));
    objeto->agregar(izquierda);
}
