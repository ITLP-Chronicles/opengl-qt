#ifndef FOX_H
#define FOX_H
#include "foxhead.h"
#include "foxleg.h"
#include "foxtail.h"
#include "matriz3d.h"

enum AxeDirection{
    X,
    Y,
    Z
};

enum FoxLeg{
    FrontRight,
    FrontLeft,
    BackRight,
    BackLeft
};

class fox
{
public:
    foxhead* head;
    foxleg* frontRight;
    foxleg* frontLeft;
    foxleg* backRight;
    foxleg* backLeft;
    foxtail* tail;

    fox(foxhead* head, foxleg* frontRight, foxleg* frontLeft, foxleg* backRight, foxleg* backLeft,  foxtail* tail);
    void display();
    /// The head will be moved upwards and downwards   up | down
    void moveHead(double angle);
    ///The leg will be moved forwards and backwards    front | back
    void moveLeg(FoxLeg leg, double angle);
    ///The tail will be moved sidewards   left | right
    void moveTail(double angle);

    void rotateItself(AxeDirection direction, double angle);
};

#endif // FOX_H
