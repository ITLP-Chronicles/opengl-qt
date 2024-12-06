#include "openglwidget.h"
#include "utils.h"
#include "fox.h"
#include "vertice.h"
#include <cmath>
fox* foxxy = nullptr;
OpenGLWidget::OpenGLWidget() {
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
    ///
    //Graficar(objeto3D);
    Vertice* o = new Vertice(-0.25f, -0.25f, 0.5f);
    foxhead* head = new foxhead(o);
    foxbody* body = new foxbody(o);

    // Dimensiones de las patas
    float anchoPata = 0.15;  // Ancho de la pata
    float altoPata = 0.3;   // Altura de la pata
    float profundidadPata = 0.15;  // Profundidad de la pata

    foxleg* frontRight = new foxleg(o);
    foxleg* frontLeft = new foxleg(new Vertice(o->x,o->y - altoPata,o->z - 1 + profundidadPata));
    foxleg* backRight = new foxleg(o);
    foxleg* backLeft = new foxleg(o);
    foxtail* tail = new foxtail(o);
    foxxy = new fox(head, body, frontRight, frontLeft, backRight, backLeft, tail);
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

    // Configure lighting
    float luzAmbiente[] = {0.2, 0.2, 0.2, 1};
    float luzDifusa[] = {1.0, 1.0, 1.0, 1};
    float luzPosicion[] = {lightX, lightY, 2.0f, 1};;

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_POSITION, luzPosicion);

    // Apply camera transformations
    glTranslatef(-cameraX, -cameraY, -cameraZ);
    glTranslatef(0, 0, -cameraDistance);
    glRotatef(cameraPitch, 1, 0, 0);   // Pitch rotation
    glRotatef(cameraYaw, 0, 1, 0);     // Yaw rotation

    glColor3f(1, 0, 0);
    foxxy->display();
}
