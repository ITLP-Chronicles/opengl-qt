#include "fox.h"
#include "matriz3d.h"

fox::fox(foxhead* head, foxbody* body, foxleg* frontRight, foxleg* frontLeft, foxleg* backRight, foxleg* backLeft, foxtail* tail) {
    this->head = head;
    this->body = body;
    this->frontRight = frontRight;
    this->frontLeft = frontLeft;
    this->backRight = backRight;
    this->backLeft = backLeft;
    this->tail = tail;
}

void fox::display(){
    this->head->desplegar();
    this->body->desplegar();
    this->frontRight->desplegar();
    this->frontLeft->desplegar();
    this->backRight->desplegar();
    this->backLeft->desplegar();
    this->tail->desplegar();
}

void fox::moveHead(double angle){}
void fox:: moveLeg(FoxLeg leg, double angle){}
void fox::moveTail(double angle){};
void rotateItself(AxeDirection direction, Matriz3D* rotationMatrix){}
