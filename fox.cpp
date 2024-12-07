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
        head->rotar(angle, nullptr);  // Assuming rotar method in Objeto3D
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
    glPushMatrix();
    Linea* eje = new Linea(0,-0.25,0,0,-0.25,1);

    // Rotate the entire fox based on the specified axis
    switch(direction) {
    case X:
        glRotatef(angle, 1.0f, 0.0f, 0.0f);
        break;
    case Y:
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        break;
    case Z:
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        break;
    }

    // Apply rotation to each body part
    if (head) head->rotar(angle, eje);
    if (body) body->rotar(angle, eje);
    if (frontRight) frontRight->rotar(angle, eje);
    if (frontLeft) frontLeft->rotar(angle, eje);
    if (backRight) backRight->rotar(angle, eje);
    if (backLeft) backLeft->rotar(angle, eje);
    if (tail) tail->rotar(angle, eje);

    glPopMatrix();
}
