#include "objeto3d.h"
#include <cmath>

Objeto3D::Objeto3D() {
    this->superficies = std::vector<Superficie*>();
    this->rotationAxe = nullptr;
}

Objeto3D::~Objeto3D() {
    for (Superficie* superficie:superficies) {
        delete superficie;
    }
}

void Objeto3D::agregar(Superficie* superficie) {
    superficies.push_back(superficie);
}

void Objeto3D::desplegar() {
    for (Superficie* superficie:superficies) {
        superficie->desplegar();
    }
}

Objeto3D* Objeto3D::copia() {
    Objeto3D* copia=new Objeto3D();
    for (Superficie* superficie:superficies) {
        copia->agregar(superficie->copia());
    }
    return copia;
}

void Objeto3D::transformar(Matriz3D* M) {
    for (Superficie* superficie:superficies) {
        superficie->transformar(M);
    }
}

void Objeto3D::rotar(float tetaInRadians, Linea* eje) {
    // Verificar eje válido
    if (!eje || (eje->p1->x == eje->p2->x && 
                 eje->p1->y == eje->p2->y && 
                 eje->p1->z == eje->p2->z)) {
        return;  // O lanzar excepción
    }

    // Calcular vector director del eje
    float a = eje->p2->x - eje->p1->x;
    float b = eje->p2->y - eje->p1->y;
    float c = eje->p2->z - eje->p1->z;

    // Calcular ángulos para alinear con eje Z
    float alfa = atan2(b, c);
    float d = sqrt(b*b + c*c);  // Más eficiente que pow()
    float beta = atan2(a, d);

    // Crear matrices de transformación usando smart pointers
    std::unique_ptr<Matriz3D> T1(new Matriz3D(1,0,0,-eje->p1->x,
                                             0,1,0,-eje->p1->y,
                                             0,0,1,-eje->p1->z));
    
    std::unique_ptr<Matriz3D> R1x(new Matriz3D(1,0,0,0,
                                              0,cos(alfa),-sin(alfa),0,
                                              0,sin(alfa),cos(alfa),0));
    std::unique_ptr<Matriz3D> R1y(new Matriz3D(cos(-beta),0,sin(-beta),0,
                                             0,1,0,0,
                                             -sin(-beta),0,cos(-beta),0));
    std::unique_ptr<Matriz3D> Rz(new Matriz3D(cos(tetaInRadians),-sin(tetaInRadians),0,0,
                                             sin(tetaInRadians),cos(tetaInRadians),0,0,
                                             0,0,1,0));
    std::unique_ptr<Matriz3D> R2y(new Matriz3D(cos(beta),0,sin(beta),0,
                                            0,1,0,0,
                                            -sin(beta),0,cos(beta),0));
    std::unique_ptr<Matriz3D> R2x(new Matriz3D(1,0,0,0,
                                              0,cos(-alfa),-sin(-alfa),0,
                                              0,sin(-alfa),cos(-alfa),0));
    std::unique_ptr<Matriz3D> T2(new Matriz3D(1,0,0,eje->p1->x,
                                             0,1,0,eje->p1->y,
                                             0,0,1,eje->p1->z));

    // Multiplicar matrices en secuencia
    std::unique_ptr<Matriz3D> M(T2->mult(R2x->mult(R2y->mult(Rz->mult(R1y->mult(R1x->mult(T1.get())))))));
    
    // Aplicar transformación
    transformar(M.get());
}

Vertice* Objeto3D::calcularCentroide() const {
    float sumX = 0.0f;
    float sumY = 0.0f;
    float sumZ = 0.0f;
    int numVertices = 0;

    for (const Superficie* superficie : superficies) {
        for (const Vertice* vertice : superficie->vertices) { // Asegúrate de tener un método getVertices() en Surface
            sumX += vertice->x;  // Usa el método correspondiente de Vertex para obtener x, y, z
            sumY += vertice->y;
            sumZ += vertice->z;
            numVertices++;
        }
    }

    if (numVertices == 0) {
        return new Vertice(0.0f, 0.0f, 0.0f);  // En caso de que no haya vértices
    }

    return new Vertice(sumX / numVertices, sumY / numVertices, sumZ / numVertices);
}


















