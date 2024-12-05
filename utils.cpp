#include <superficie.h>
#include <objeto3d.h>

void CrearPrismaRectangular(Objeto3D* objeto, float x, float y, float z, float ancho, float alto, float profundo,
                            float colorR = 1.0f, float colorG = 0.0f, float colorB = 0.0f, float opacidad = 1.0f) {
    // Calcula los vértices del prisma
    float x1 = x, x2 = x + ancho;
    float y1 = y, y2 = y + alto;
    float z1 = z, z2 = z - profundo;

    // Estructura para definir colores por cara
    struct CaraColor {
        float r, g, b, a;
    };

    // Arreglo de colores por cara (opcional, puede ser modificado)
    CaraColor coloresPorCara[6] = {
        {colorR, colorG, colorB, opacidad},     // Cara frontal
        {colorR * 0.8f, colorG * 0.8f, colorB * 0.8f, opacidad},  // Cara trasera
        {colorR * 0.9f, colorG * 0.9f, colorB * 0.9f, opacidad},  // Cara superior
        {colorR * 0.7f, colorG * 0.7f, colorB * 0.7f, opacidad},  // Cara inferior
        {colorR * 0.6f, colorG * 0.6f, colorB * 0.6f, opacidad},  // Cara derecha
        {colorR * 0.5f, colorG * 0.5f, colorB * 0.5f, opacidad}   // Cara izquierda
    };

    // Cara frontal
    Superficie* frontal = new Superficie(
        coloresPorCara[0].r,
        coloresPorCara[0].g,
        coloresPorCara[0].b,
        coloresPorCara[0].a
        );
    frontal->agregar(new Vertice(x1, y1, z1));
    frontal->agregar(new Vertice(x2, y1, z1));
    frontal->agregar(new Vertice(x2, y2, z1));
    frontal->agregar(new Vertice(x1, y2, z1));
    objeto->agregar(frontal);

    // Cara trasera
    Superficie* trasera = new Superficie(
        coloresPorCara[1].r,
        coloresPorCara[1].g,
        coloresPorCara[1].b,
        coloresPorCara[1].a
        );
    trasera->agregar(new Vertice(x2, y1, z2));
    trasera->agregar(new Vertice(x1, y1, z2));
    trasera->agregar(new Vertice(x1, y2, z2));
    trasera->agregar(new Vertice(x2, y2, z2));
    objeto->agregar(trasera);

    // Cara superior
    Superficie* superior = new Superficie(
        coloresPorCara[2].r,
        coloresPorCara[2].g,
        coloresPorCara[2].b,
        coloresPorCara[2].a
        );
    superior->agregar(new Vertice(x1, y2, z1));
    superior->agregar(new Vertice(x2, y2, z1));
    superior->agregar(new Vertice(x2, y2, z2));
    superior->agregar(new Vertice(x1, y2, z2));
    objeto->agregar(superior);

    // Cara inferior
    Superficie* inferior = new Superficie(
        coloresPorCara[3].r,
        coloresPorCara[3].g,
        coloresPorCara[3].b,
        coloresPorCara[3].a
        );
    inferior->agregar(new Vertice(x1, y1, z1));
    inferior->agregar(new Vertice(x1, y1, z2));
    inferior->agregar(new Vertice(x2, y1, z2));
    inferior->agregar(new Vertice(x2, y1, z1));
    objeto->agregar(inferior);

    // Cara derecha
    Superficie* derecha = new Superficie(
        coloresPorCara[4].r,
        coloresPorCara[4].g,
        coloresPorCara[4].b,
        coloresPorCara[4].a
        );
    derecha->agregar(new Vertice(x2, y1, z1));
    derecha->agregar(new Vertice(x2, y1, z2));
    derecha->agregar(new Vertice(x2, y2, z2));
    derecha->agregar(new Vertice(x2, y2, z1));
    objeto->agregar(derecha);

    // Cara izquierda
    Superficie* izquierda = new Superficie(
        coloresPorCara[5].r,
        coloresPorCara[5].g,
        coloresPorCara[5].b,
        coloresPorCara[5].a
        );
    izquierda->agregar(new Vertice(x1, y1, z2));
    izquierda->agregar(new Vertice(x1, y1, z1));
    izquierda->agregar(new Vertice(x1, y2, z1));
    izquierda->agregar(new Vertice(x1, y2, z2));
    objeto->agregar(izquierda);
}

// Sobrecarga adicional para colores específicos por cara y opacidad
void CrearPrismaRectangular(Objeto3D* objeto, float x, float y, float z, float ancho, float alto, float profundo,
                            float colorFrontal[3], float colorTrasera[3], float colorSuperior[3],
                            float colorInferior[3], float colorDerecha[3], float colorIzquierda[3],
                            float opacidad = 1.0f) {
    // Calcula los vértices del prisma
    float x1 = x, x2 = x + ancho;
    float y1 = y, y2 = y + alto;
    float z1 = z, z2 = z - profundo;

    // Cara frontal
    Superficie* frontal = new Superficie(colorFrontal[0], colorFrontal[1], colorFrontal[2], opacidad);
    frontal->agregar(new Vertice(x1, y1, z1));
    frontal->agregar(new Vertice(x2, y1, z1));
    frontal->agregar(new Vertice(x2, y2, z1));
    frontal->agregar(new Vertice(x1, y2, z1));
    objeto->agregar(frontal);

    // Cara trasera
    Superficie* trasera = new Superficie(colorTrasera[0], colorTrasera[1], colorTrasera[2], opacidad);
    trasera->agregar(new Vertice(x2, y1, z2));
    trasera->agregar(new Vertice(x1, y1, z2));
    trasera->agregar(new Vertice(x1, y2, z2));
    trasera->agregar(new Vertice(x2, y2, z2));
    objeto->agregar(trasera);

    // Cara superior
    Superficie* superior = new Superficie(colorSuperior[0], colorSuperior[1], colorSuperior[2], opacidad);
    superior->agregar(new Vertice(x1, y2, z1));
    superior->agregar(new Vertice(x2, y2, z1));
    superior->agregar(new Vertice(x2, y2, z2));
    superior->agregar(new Vertice(x1, y2, z2));
    objeto->agregar(superior);

    // Cara inferior
    Superficie* inferior = new Superficie(colorInferior[0], colorInferior[1], colorInferior[2], opacidad);
    inferior->agregar(new Vertice(x1, y1, z1));
    inferior->agregar(new Vertice(x1, y1, z2));
    inferior->agregar(new Vertice(x2, y1, z2));
    inferior->agregar(new Vertice(x2, y1, z1));
    objeto->agregar(inferior);

    // Cara derecha
    Superficie* derecha = new Superficie(colorDerecha[0], colorDerecha[1], colorDerecha[2], opacidad);
    derecha->agregar(new Vertice(x2, y1, z1));
    derecha->agregar(new Vertice(x2, y1, z2));
    derecha->agregar(new Vertice(x2, y2, z2));
    derecha->agregar(new Vertice(x2, y2, z1));
    objeto->agregar(derecha);

    // Cara izquierda
    Superficie* izquierda = new Superficie(colorIzquierda[0], colorIzquierda[1], colorIzquierda[2], opacidad);
    izquierda->agregar(new Vertice(x1, y1, z2));
    izquierda->agregar(new Vertice(x1, y1, z1));
    izquierda->agregar(new Vertice(x1, y2, z1));
    izquierda->agregar(new Vertice(x1, y2, z2));
    objeto->agregar(izquierda);
}

