#include "openglwidget.h"
#include "utils.h"
#include "fox.h"
#include "vertice.h"
#include <cmath>
fox* foxxy = nullptr;



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
    connect(timerTail, &QTimer::timeout, this, moveTailTimer);
    connect(timerHead, &QTimer::timeout, this, &OpenGLWidget::moveHeadTimer);
    connect(timerFoxRotation, &QTimer::timeout, this, &OpenGLWidget::moveFoxRotationTimer);
    ///

    Vertice* o = new Vertice(-0.25f, -0.25f, 0.5f);

    // Crear las líneas para los ejes de rotación
    Linea* ejeCabeza = new Linea(o, new Vertice(o->x, o->y + 0.5f, o->z)); // Eje de rotación para la cabeza
    Linea* ejeCuerpo = new Linea(o, new Vertice(o->x, o->y + 1.0f, o->z));  // Eje de rotación para el cuerpo
    Linea* ejePataFrontLeft = new Linea(
        new Vertice(o->x - 0.1f, o->y, o->z - 1.0f),          // Punto izquierdo
        new Vertice(o->x + 0.1f, o->y, o->z - 1.0f)           // Punto derecho
    );
    Linea* ejePataFrontRight = new Linea(
        new Vertice(o->x + 0.5f - 0.25f, o->y, o->z - 1.0f),  // Punto izquierdo
        new Vertice(o->x + 0.5f + 0.05f, o->y, o->z - 1.0f)   // Punto derecho
    );
    Linea* ejePataBackLeft = new Linea(
        new Vertice(o->x - 0.1f, o->y, o->z),                 // Punto izquierdo
        new Vertice(o->x + 0.1f, o->y, o->z)                  // Punto derecho
    );
    Linea* ejePataBackRight = new Linea(
        new Vertice(o->x + 0.5f - 0.25f, o->y, o->z),         // Punto izquierdo
        new Vertice(o->x + 0.5f + 0.05f, o->y, o->z)          // Punto derecho
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
    // Realizar una rotación y mostrar
    foxxy->display();
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
    }}

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

    // Apply camera transformations
    glTranslatef(-cameraX, -cameraY, -cameraZ);
    glTranslatef(0, 0, -cameraDistance);
    glRotatef(cameraPitch, 1, 0, 0);   // Pitch rotation
    glRotatef(cameraYaw, 0, 1, 0);     // Yaw rotation

    // Configure lighting
    float luzAmbiente[] = {0.5, 0.5, 0.5, 1};
    float luzDifusa[] = {0.6, 0.6, 0.6, 1};
    float luzPosicion[] = {lightX, lightY + 1.0f, 4.0, 1};

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);

    // Set light position after transformations
    glLightfv(GL_LIGHT0, GL_POSITION, luzPosicion); // Affected by transformations

    // Render object
    glColor3f(1, 0, 0);
    foxxy->display();
    // if (foxxy) {
    //     foxxy->rotateItself(X, rotationAngle);  // This will handle the display
    // }
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event) {
    qDebug() << "Widget has focus:" << this->hasFocus();
    
    if (event->key() == Qt::Key_A) {
        timer.start(30, this);
    }
    if (event->key() == Qt::Key_S) {
        timerHead->start(30);
    }
    if (event->key() == Qt::Key_D) {
        timerTail->start(30);
    }
    if (event->key() == Qt::Key_F) {
        timerFoxRotation->start(30);
    }

    QWidget::keyPressEvent(event);
}

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
    }
    QWidget::keyReleaseEvent(event);
}

void OpenGLWidget::moveHeadTimer() {
    static float headAngle = 0.0f;
    static float headDirection = 1.0f;
    
    // Smooth pendulum movement using smaller angle increments
    headAngle += headDirection * 0.5f;
    
    // Limit head rotation to a smaller range (±10 degrees)
    if (headAngle >= 10.0f || headAngle <= -10.0f) {
        headDirection *= -1.0f;
    }
    
    // Move the head up and down
    if (foxxy) {
        foxxy->moveHead(headAngle);
        qDebug() << "Moviendo!!";

    }
    
    update();
}

void OpenGLWidget::moveFoxRotationTimer() {
    // Usar un ángulo fijo por frame en lugar de acumulativo
    float rotationSpeed = 2.0f;  // grados por frame
    
    if (foxxy) {
        foxxy->rotateItself(X, rotationSpeed);
    }
    
    update();
}
