#include "openglwidget.h"
#include "utils.h"
#include "fox.h"
#include "vertice.h"
#include <cmath>
fox* foxxy = nullptr;


float rotateX = 0;
float rotateY = 0;
float rotateZ = 0;

float preCameraYaw = 0.0f;
float preCameraPitch = 15.0f;

void moveTailTimer(){
    qDebug() << "moveTailTimer";
}

OpenGLWidget::OpenGLWidget() {
    setFocusPolicy(Qt::StrongFocus);  // Allow widget to receive keyboard focus
    setFocus();                        // Set initial focus to this widget
    
    /// Values Default
    // Initial camera parameters
    cameraDistance = 3.5f;
    cameraYaw = 0.0f;
    cameraPitch = 15.0f;
    // Camera position and movement
    cameraX = 0.0f;
    cameraY = 0.0f;
    cameraZ = 0.0f;
    setMouseTracking(true);
    // Initialize 3D object
    //objeto3D = new Objeto3D();
    // Track mouse movement states
    lastMousePos = QPoint(0, 0);
    isLeftButtonPressed = false;
    isRightButtonPressed = false;
    lightX = 0.0f;
    lightY = 0.0f;
    this->timerTail = new QTimer(this);
    this->timerHead = new QTimer(this);
    this->timerFoxRotation = new QTimer(this);
    this->timerRotateX = new QTimer(this);
    this->timerRotateY = new QTimer(this);
    this->timerRotateZ = new QTimer(this);
    connect(timerTail, &QTimer::timeout, this, &OpenGLWidget::moveTailTimer);
    connect(timerHead, &QTimer::timeout, this, &OpenGLWidget::moveHeadTimer);
    connect(timerFoxRotation, &QTimer::timeout, this, &OpenGLWidget::moveFoxRotationTimer);
    connect(timerRotateX, &QTimer::timeout, this, &OpenGLWidget::rotateXTimer);
    connect(timerRotateY, &QTimer::timeout, this, &OpenGLWidget::rotateYTimer);
    connect(timerRotateZ, &QTimer::timeout, this, &OpenGLWidget::rotateZTimer);

    ///

    Vertice* o = new Vertice(-0.25f, -0.25f, 0.5f);

    // Crear las líneas para los ejes de rotación
    Linea* ejeCabeza = new Linea(o, new Vertice(o->x, o->y + 0.5f, o->z)); // Eje de rotación para la cabeza
    Linea* ejeCuerpo = new Linea(o, new Vertice(o->x, o->y + 1.0f, o->z));  // Eje de rotación para el cuerpo
    Linea* ejePataFrontLeft = new Linea(
        new Vertice(o->x - 0.1f, o->y, o->z - 1.0f + 0.075f),          // Punto izquierdo
        new Vertice(o->x + 0.1f, o->y, o->z - 1.0f + 0.075f)           // Punto derecho
        );
    Linea* ejePataFrontRight = new Linea(
        new Vertice(o->x + 0.5f - 0.25f, o->y, o->z - 1.0f + 0.075f),  // Punto izquierdo
        new Vertice(o->x + 0.5f + 0.05f, o->y, o->z - 1.0f + 0.075f)   // Punto derecho
        );
    Linea* ejePataBackLeft = new Linea(
        new Vertice(o->x - 0.1f, o->y, o->z - 0.075f),                 // Punto izquierdo
        new Vertice(o->x + 0.1f, o->y, o->z - 0.075f)                  // Punto derecho
        );
    Linea* ejePataBackRight = new Linea(
        new Vertice(o->x + 0.5f - 0.25f, o->y, o->z - 0.075f),         // Punto izquierdo
        new Vertice(o->x + 0.5f + 0.05f, o->y, o->z - 0.075f)          // Punto derecho
        );
    Linea* ejeCola = new Linea(o, new Vertice(o->x, o->y + 1.0f, o->z)); // Eje de rotación para la cola

    // Crear las partes del zorro pasando las líneas como último parámetro
    foxhead* head = new foxhead(o, ejeCabeza);
    foxbody* body = new foxbody(o, ejeCuerpo);

    foxleg* frontLeft = new foxleg(o, 0, -1 + 0.15f, ejePataFrontLeft);
    foxleg* frontRight = new foxleg(o, 0.5 - 0.15, -1 + 0.15f, ejePataFrontRight);
    foxleg* backLeft = new foxleg(o, 0, 0, ejePataBackLeft);
    foxleg* backRight = new foxleg(o, 0.5 - 0.15, 0, ejePataBackRight);

    foxtail* tail = new foxtail(o, ejeCola);

    // Crear el zorro
    foxxy = new fox(head, body, frontRight, frontLeft, backRight, backLeft, tail);
    
    // Store initial state
    initialFox = new fox(
        new foxhead(o, ejeCabeza->copia()),
        new foxbody(o, ejeCuerpo->copia()),
        new foxleg(o, 0.5f - 0.15f, -1.0f + 0.15f, ejePataFrontRight->copia()),
        new foxleg(o, 0, -1.0f + 0.15f, ejePataFrontLeft->copia()),
        new foxleg(o, 0.5f - 0.15f, 0, ejePataBackRight->copia()),
        new foxleg(o, 0, 0, ejePataBackLeft->copia()),
        new foxtail(o, ejeCola->copia())
    );

    resetFox();
}

void OpenGLWidget::initializeGL() {
    glClearColor(1, 1, 1, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event) {
    lastMousePos = event->pos();

    if (event->button() == Qt::LeftButton) {
        isLeftButtonPressed = true;
        setCursor(Qt::BlankCursor); // Hide cursor when rotating
    }
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isLeftButtonPressed = false;
        unsetCursor();
    }
    //cameraYaw = 0;
    //cameraPitch = 15.0;
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
    QPoint delta = event->pos() - lastMousePos;

    // Movimiento de la luz basado en el movimiento del mouse
    lightX += delta.x() * 0.01f;  // Ajusta estos valores para controlar la sensibilidad
    lightY -= delta.y() * 0.01f;  // Resta para que el movimiento sea más intuitivo

    if (isLeftButtonPressed) {
        // Camera rotation
        cameraYaw += delta.x() * 0.5f;     // Horizontal rotation
        cameraPitch += delta.y() * 0.5f;   // Vertical rotation

        // Limit pitch to prevent camera flipping
        cameraPitch = qBound(-89.0f, cameraPitch, 89.0f);
    }

    lastMousePos = event->pos();
    update();
}

void OpenGLWidget::wheelEvent(QWheelEvent *event) {
    // Zoom in/out using mouse wheel
    float zoomSpeed = 0.01f;
    cameraDistance -= event->angleDelta().y() * zoomSpeed;

    // Limit zoom range
    cameraDistance = qBound(1.0f, cameraDistance, 20.0f);

    update();
}

void OpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 2.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Aplicar las transformaciones de la cámara


    glTranslatef(-cameraX, -cameraY, -cameraZ);
    glTranslatef(0, 0, -cameraDistance);

    glRotatef(cameraPitch, 1, 0, 0);   // Rotación de Pitch
    glRotatef(cameraYaw, 0, 1, 0);     // Rotación de Yaw


    //foxxy->rotateItself(X, cameraPitch);
    //foxxy->rotateItself(Y, cameraYaw);

    preCameraYaw = cameraYaw;
    preCameraPitch = cameraPitch;

    // Guardar el estado de la matriz para aplicar la rotación del objeto sin que se vea afectada por la cámara
    //glPushMatrix();  // Guardamos la matriz actual de transformaciones

    // Aplicar las rotaciones del objeto en sus ejes locales
    //glRotatef(rotateX, 1.0f, 0.0f, 0.0f); // Rotación sobre el eje X del objeto
    //glRotatef(rotateY, 0.0f, 1.0f, 0.0f); // Rotación sobre el eje Y del objeto
    //glRotatef(rotateZ, 0.0f, 0.0f, 1.0f); // Rotación sobre el eje Z del objeto

    // Renderizar el objeto con la rotación aplicada
    glColor3f(1, 0, 0);

    foxxy->display();

    QSize tam = size();

    glViewport(10*tam.width()/9,tam.height()/3,tam.width()/3,tam.height()/3);

    fox* foxxyFromUnder = foxxy->copy();
    foxxyFromUnder->rotateItself(X, 90);
    foxxyFromUnder->display();

    glViewport(10*tam.width()/9,2*tam.height()/3,tam.width()/3,tam.height()/3);

    fox* foxxyFromRight = foxxy->copy();
    foxxyFromRight->rotateItself(Y, 90);
    foxxyFromRight->display();

    glViewport(10*tam.width()/9,3*tam.height()/3,tam.width()/3,tam.height()/3);

    fox* foxxyFromLeft = foxxy->copy();
    foxxyFromLeft->rotateItself(Y, -90);
    foxxyFromLeft->display();

    // Restaurar el estado de la matriz original
    glPopMatrix();  // Restauramos la matriz a su estado anterior

    delete foxxyFromUnder;
    delete foxxyFromRight;
    delete foxxyFromLeft;
}


void OpenGLWidget::keyPressEvent(QKeyEvent *event) {
    if (!event->isAutoRepeat()) {  // Only handle initial key press
        switch(event->key()) {
            case Qt::Key_Up:
                keyUpPressed = true;
                break;
            case Qt::Key_Down:
                keyDownPressed = true;
                break;
            case Qt::Key_Left:
                keyLeftPressed = true;
                break;
            case Qt::Key_Right:
                keyRightPressed = true;
                break;
            case Qt::Key_Shift:
                keyPageUpPressed = true;
                break;
            case Qt::Key_Backspace:
                keyPageDownPressed = true;
                break;
            case Qt::Key_F:
                resetFox();
                break;
        }
    }
    
    // Start timers based on pressed keys
    if (keyUpPressed || keyDownPressed) {
        timerRotateX->start(30);
    }
    if (keyLeftPressed || keyRightPressed) {
        timerRotateY->start(30);
    }
    if (keyPageUpPressed || keyPageDownPressed) {
        timerRotateZ->start(30);
    }
    
    // Keep existing key handlers
    if (event->key() == Qt::Key_A) {
        timer.start(30, this);
    }
    if (event->key() == Qt::Key_S) {
        timerHead->start(30);
    }
    if (event->key() == Qt::Key_D) {
        timerTail->start(30);
    }

    QWidget::keyPressEvent(event);
}

/// MOVER PATAS
void OpenGLWidget::timerEvent(QTimerEvent *event) {
    static float angle = 0.0f;
    static float direction = 1.0f;
    
    // Movimiento pendular suave usando seno
    angle += direction * 1.0f;  // Reducido de 2.0f a 1.0f para un movimiento más suave
    
    // Limitar el ángulo a un rango más pequeño (±15 grados en lugar de ±30)
    if (angle >= 6.0f || angle <= -6.0f) {
        direction *= -1.0f;
    }
    
    // Mover las patas opuestas en fase contraria
    foxxy->moveLeg(FoxLeg::FrontLeft, angle);
    foxxy->moveLeg(FoxLeg::BackRight, angle);
    foxxy->moveLeg(FoxLeg::FrontRight, -angle);
    foxxy->moveLeg(FoxLeg::BackLeft, -angle);
    
    update();
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event) {
    if (!event->isAutoRepeat()) {  // Only handle actual key releases
        switch(event->key()) {
            case Qt::Key_Up:
                keyUpPressed = false;
                break;
            case Qt::Key_Down:
                keyDownPressed = false;
                break;
            case Qt::Key_Left:
                keyLeftPressed = false;
                break;
            case Qt::Key_Right:
                keyRightPressed = false;
                break;
            case Qt::Key_Shift:
                keyPageUpPressed = false;
                break;
            case Qt::Key_Backspace:
                keyPageDownPressed = false;
                break;
        }
    }
    
    // Stop timers if no keys in that axis are pressed
    if (!keyUpPressed && !keyDownPressed) {
        timerRotateX->stop();
    }
    if (!keyLeftPressed && !keyRightPressed) {
        timerRotateY->stop();
    }
    if (!keyPageUpPressed && !keyPageDownPressed) {
        timerRotateZ->stop();
    }
    
    // Keep existing release handlers
    if (event->key() == Qt::Key_A) {
        timer.stop();
    }
    if (event->key() == Qt::Key_S) {
        timerHead->stop();
    }
    if (event->key() == Qt::Key_D) {
        timerTail->stop();
    }
    if (event->key() == Qt::Key_F) {
        timerFoxRotation->stop();
        rotateX = 0;
        rotateY = 0;
        rotateZ = 0;
    }
    
    QWidget::keyReleaseEvent(event);
}

void OpenGLWidget::moveHeadTimer() {
    static float time = 0.0f;
    
    // Increment time for smooth animation
    time += 0.3f;  // Smaller time increment for smoother movement
    
    // Reduced maximum angle from 2.0f to 0.8f for an even more subtle movement
    float headAngle = 1.0f * sin(time);
    
    if (foxxy) {
        foxxy->moveHead(headAngle);
    }
    
    update();
}

void OpenGLWidget::moveFoxRotationTimer() {
    // Usar un ángulo fijo por frame en lugar de acumulativo
    float rotationSpeed = 2.0f;  // grados por frame

    if (foxxy) {
        //foxxy->rotateItself(X, rotationSpeed);
    }

    update();
}

void OpenGLWidget::moveTailTimer() {
    static float time = 0.0f;
    
    // Increment time for smooth animation
    time += 0.2f;  // Controls the speed of the tail wagging
    
    // Use sine function for smooth back-and-forth movement
    // Multiply by a small number (0.8f) to keep the movement subtle
    float tailAngle = 0.8f * sin(time);
    
    if (foxxy) {
        foxxy->moveTail(tailAngle);
    }
    
    update();
}

void OpenGLWidget::rotateXTimer() {
    if (foxxy) {
        float direction = 0.0f;
        if (keyUpPressed) {
            foxxy->rotateItself(X, -2.0f);
            //rotateX -= 2.0f;
        }
        if (keyDownPressed){
            foxxy->rotateItself(X,  2.0f);
            //rotateX += 2.0f;
        }
        if (direction != 0.0f) {
            //foxxy->rotateItself(X, direction * 2.0f);
        }
    }
    update();
}

void OpenGLWidget::rotateYTimer() {
    if (foxxy) {
        float direction = 0.0f;
        if (keyRightPressed) /*rotateY += 2.0f;*/ foxxy->rotateItself(Y, 2.0f);
        if (keyLeftPressed) /*rotateY -= 2.0f;*/ foxxy->rotateItself(Y, -2.0f);
        if (direction != 0.0f) {
            //foxxy->rotateItself(Y, direction * 2.0f);
        }
    }
    update();
}

void OpenGLWidget::rotateZTimer() {
    if (foxxy) {
        float direction = 0.0f;
        if (keyPageUpPressed) /*rotateZ += 2.0f;*/ foxxy->rotateItself(Z, 2.0f);
        if (keyPageDownPressed) /*rotateZ -= 2.0f;*/ foxxy->rotateItself(Z, -2.0f);
        if (direction != 0.0f) {
            //foxxy->rotateItself(Z, direction * 2.0f);
        }
    }
    update();
}

void OpenGLWidget::resetFox() {
    if (foxxy && initialFox) {

        foxxy->ejeX = new Linea(0,0,0,1,0,0);
        foxxy->ejeY = new Linea(0,0,0,0,1,0);
        foxxy->ejeZ = new Linea(0,0,0,0,0,1);

        // Copy initial state to current fox
        foxxy->head->superficies = initialFox->head->copia()->superficies;
        foxxy->body->superficies = initialFox->body->copia()->superficies;
        foxxy->frontRight->superficies = initialFox->frontRight->copia()->superficies;
        foxxy->frontLeft->superficies = initialFox->frontLeft->copia()->superficies;
        foxxy->backRight->superficies = initialFox->backRight->copia()->superficies;
        foxxy->backLeft->superficies = initialFox->backLeft->copia()->superficies;
        foxxy->tail->superficies = initialFox->tail->copia()->superficies;
        
        // Reset rotation axes
        foxxy->head->rotationAxe = initialFox->head->rotationAxe->copia();
        foxxy->body->rotationAxe = initialFox->body->rotationAxe->copia();
        foxxy->frontRight->rotationAxe = initialFox->frontRight->rotationAxe->copia();
        foxxy->frontLeft->rotationAxe = initialFox->frontLeft->rotationAxe->copia();
        foxxy->backRight->rotationAxe = initialFox->backRight->rotationAxe->copia();
        foxxy->backLeft->rotationAxe = initialFox->backLeft->rotationAxe->copia();
        foxxy->tail->rotationAxe = initialFox->tail->rotationAxe->copia();
    }
    update();
}

OpenGLWidget::~OpenGLWidget() {
    delete initialFox;
}
