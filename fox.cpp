#include "fox.h"
#include <GL/gl.h>
#include <cmath>

fox::fox(foxhead* head, foxbody* body, foxleg* frontRight, foxleg* frontLeft,
         foxleg* backRight, foxleg* backLeft, foxtail* tail)
    : head(head), body(body), frontRight(frontRight), frontLeft(frontLeft),
    backRight(backRight), backLeft(backLeft), tail(tail)
{
}

void fox::display() {
    glPushMatrix();

    // Draw each body part
    if (body) {
        glColor3f(0.7f, 0.4f, 0.2f);  // Brown color for body
        body->desplegar();
    }

    if (head) {
        glPushMatrix();
        glColor3f(0.8f, 0.5f, 0.3f);  // Slightly lighter brown for head
        head->desplegar();
        glPopMatrix();
    }

    // Draw legs
    if (frontRight) {
        glPushMatrix();
        glColor3f(0.6f, 0.3f, 0.1f);  // Darker brown for legs
        frontRight->desplegar();
        glPopMatrix();
    }

    if (frontLeft) {
        glPushMatrix();
        glColor3f(0.6f, 0.3f, 0.1f);
        frontLeft->desplegar();
        glPopMatrix();
    }

    if (backRight) {
        glPushMatrix();
        glColor3f(0.6f, 0.3f, 0.1f);
        backRight->desplegar();
        glPopMatrix();
    }

    if (backLeft) {
        glPushMatrix();
        glColor3f(0.6f, 0.3f, 0.1f);
        backLeft->desplegar();
        glPopMatrix();
    }

    if (tail) {
        glPushMatrix();
        glColor3f(0.5f, 0.2f, 0.1f);  // Darker color for tail
        tail->desplegar();
        glPopMatrix();
    }

    glPopMatrix();
}

void fox::moveHead(double angle) {
    if (head) {
        // Rotate head up or down around X-axis
        glPushMatrix();
        glRotatef(angle, 1.0f, 0.0f, 0.0f);
        head->rotar(angle, head->rotationAxe);  // Assuming rotar method in Objeto3D
        glPopMatrix();
    }
}

void fox::moveLeg(FoxLeg leg, double angle) {
    foxleg* selectedLeg = nullptr;
    switch(leg) {
    case FrontRight: selectedLeg = frontRight; break;
    case FrontLeft:  selectedLeg = frontLeft;  break;
    case BackRight:  selectedLeg = backRight;  break;
    case BackLeft:   selectedLeg = backLeft;   break;
    }

    if (selectedLeg) {
        // Convertir a radianes y aplicar la rotación
        double angleInRadians = angle * M_PI / 180.0;
        
        // Aplicar la rotación usando el eje horizontal para movimiento de péndulo
        selectedLeg->rotar(angleInRadians, selectedLeg->rotationAxe);
    }
}

void fox::moveTail(double angle) {
    if (tail) {
        // Rotate tail sideways around Y-axis
        glPushMatrix();
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        tail->rotar(angle, tail->rotationAxe);  // Assuming rotar method in Objeto3D
        glPopMatrix();
    }
}

void fox::rotateItself(AxeDirection direction, double angle) {
    // Convert angle to radians
    float angleInRadians = angle * M_PI / 180.0f;
    
    // Create rotation matrix based on direction
    Matriz3D* rotationMatrix = new Matriz3D();
    float cosA = cos(angleInRadians);
    float sinA = sin(angleInRadians);
    
    switch(direction) {
    case X:
        rotationMatrix->datos[1][1] = cosA;
        rotationMatrix->datos[1][2] = -sinA;
        rotationMatrix->datos[2][1] = sinA;
        rotationMatrix->datos[2][2] = cosA;
        break;
    case Y:
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        break;
    case Z:
        rotationMatrix->datos[0][0] = cosA;
        rotationMatrix->datos[0][1] = -sinA;
        rotationMatrix->datos[1][0] = sinA;
        rotationMatrix->datos[1][1] = cosA;
        break;
    }
    
    // Apply rotation to each part
    if (body) body->transformar(rotationMatrix);
    if (head) head->transformar(rotationMatrix);
    if (frontRight) frontRight->transformar(rotationMatrix);
    if (frontLeft) frontLeft->transformar(rotationMatrix);
    if (backRight) backRight->transformar(rotationMatrix);
    if (backLeft) backLeft->transformar(rotationMatrix);
    if (tail) tail->transformar(rotationMatrix);
    
    // Clean up
    delete rotationMatrix;
    
    // Display the transformed fox
    display();
}
