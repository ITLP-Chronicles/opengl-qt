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
    // Select the correct leg based on enum
    foxleg* selectedLeg = nullptr;
    switch(leg) {
    case FrontRight: selectedLeg = frontRight; break;
    case FrontLeft:  selectedLeg = frontLeft;  break;
    case BackRight:  selectedLeg = backRight;  break;
    case BackLeft:   selectedLeg = backLeft;   break;
    }

    if (selectedLeg) {
        // Rotate leg forward or backward around X-axis
        glPushMatrix();
        glRotatef(angle, 1.0f, 0.0f, 0.0f);
        selectedLeg->rotar(angle, nullptr);  // Assuming rotar method in Objeto3D
        glPopMatrix();
    }
}

void fox::moveTail(double angle) {
    if (tail) {
        // Rotate tail sideways around Y-axis
        glPushMatrix();
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        tail->rotar(angle, nullptr);  // Assuming rotar method in Objeto3D
        glPopMatrix();
    }
}

void fox::rotateItself(AxeDirection direction, double angle) {
    glPushMatrix();

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
    if (head) head->rotar(angle, nullptr);
    if (body) body->rotar(angle, nullptr);
    if (frontRight) frontRight->rotar(angle, nullptr);
    if (frontLeft) frontLeft->rotar(angle, nullptr);
    if (backRight) backRight->rotar(angle, nullptr);
    if (backLeft) backLeft->rotar(angle, nullptr);
    if (tail) tail->rotar(angle, nullptr);

    glPopMatrix();
}
