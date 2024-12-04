#include "openglwidget.h"
#include "utils.cpp"
#include <cmath>

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
    objeto3D = new Objeto3D();
    // Track mouse movement states
    lastMousePos = QPoint(0, 0);
    isLeftButtonPressed = false;
    isRightButtonPressed = false;
    ///

    Vertice o = Vertice(-0.2, -0.2, -0.2);
    CrearPrismaRectangular(objeto3D, o.x, o.y, o.z, 0.5, 0.5, 1, 221, 129, 52); // Body

    // Crear el cuerpo principal
    CrearPrismaRectangular(objeto3D, o.x, o.y, o.z, 0.5, 0.5, 1, 221, 129, 52); // Body

    // Dimensiones de las patas
    float anchoPata = 0.15;  // Ancho de la pata
    float altoPata = 0.3;   // Altura de la pata
    float profundidadPata = 0.15;  // Profundidad de la pata

    // Dimensiones de las pezuñas
    float anchoPatita = 0.15;
    float altoPatita = 0.05;
    float profundidadPatita = 0.15;

    // Color de las patas (marrón oscuro)
    int colorPataR = 101;
    int colorPataG = 67;
    int colorPataB = 33;

    // Pata 1 - Esquina inferior izquierda delantera
    CrearPrismaRectangular(objeto3D,
                           o.x,
                           o.y - altoPata,
                           o.z - 1 + profundidadPata,
                           anchoPata, altoPata, profundidadPata,
                           colorPataR, colorPataG, colorPataB);
    CrearPrismaRectangular(objeto3D,
                            o.x,
                            o.y - altoPata - altoPatita,
                            o.z - 1 + profundidadPata,
                            anchoPatita, altoPatita, profundidadPatita,
                            31,32,38);

    // Pata 2 - Esquina inferior derecha delantera
    CrearPrismaRectangular(objeto3D,
                           o.x + 0.5 - anchoPata,
                           o.y - altoPata,
                           o.z - 1 + profundidadPata,
                           anchoPata, altoPata, profundidadPata,
                           colorPataR, colorPataG, colorPataB);
    CrearPrismaRectangular(objeto3D,
                           o.x + 0.5 - anchoPata ,
                           o.y - altoPata - altoPatita,
                           o.z - 1 + profundidadPata,
                            anchoPatita, altoPatita, profundidadPatita,
                            31,32,38);


    // Pata 3 - Esquina inferior izquierda trasera
    CrearPrismaRectangular(objeto3D,
                           o.x,
                           o.y - altoPata,
                           o.z ,
                           anchoPata, altoPata, profundidadPata,
                           colorPataR, colorPataG, colorPataB);
    CrearPrismaRectangular(objeto3D,
                           o.x,
                           o.y - altoPata - altoPatita,
                           o.z ,
                           anchoPatita, altoPatita, profundidadPatita,
                           31,32,38);

    // Pata 4 - Esquina inferior derecha trasera
    CrearPrismaRectangular(objeto3D,
                           o.x + 0.5 - anchoPata,
                           o.y - altoPata,
                           o.z,
                           anchoPata, altoPata, profundidadPata,
                           colorPataR, colorPataG, colorPataB);
    CrearPrismaRectangular(objeto3D,
                           o.x + 0.5 - anchoPata,
                           o.y - altoPata - altoPatita,
                           o.z,
                           anchoPatita, altoPatita, profundidadPatita,
                           31,32,38);

    //Eje Z
    CrearPrismaRectangular(objeto3D, 0,0,0  ,  0.015, 0.015,3,  0,0,0,  0.1);
    CrearPrismaRectangular(objeto3D, 0,0,0  ,  0.015, 0.015,-3, 0,0,0, 0.1);
    //Eje y
    CrearPrismaRectangular(objeto3D, 0,0,0  ,  0.015, 3, 0.015,  0,0,0, 0.1);
    CrearPrismaRectangular(objeto3D, 0,0,0  ,  0.015, -3, 0.015, 0,0,0, 0.1);
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

    if (event->button() == Qt::RightButton) {
        isRightButtonPressed = true;
        setCursor(Qt::BlankCursor); // Hide cursor when panning
    }
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isLeftButtonPressed = false;
        unsetCursor();
    }

    if (event->button() == Qt::RightButton) {
        isRightButtonPressed = false;
        unsetCursor();
    }
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
    QPoint delta = event->pos() - lastMousePos;

    if (isLeftButtonPressed) {
        // Camera rotation
        cameraYaw += delta.x() * 0.5f;     // Horizontal rotation
        cameraPitch += delta.y() * 0.5f;   // Vertical rotation

        // Limit pitch to prevent camera flipping
        cameraPitch = qBound(-89.0f, cameraPitch, 89.0f);
    }

    if (isRightButtonPressed) {
        // Improved camera panning
        float moveSpeed = 0.02f;

        // Convert current rotation to radians
        float yawRad = qDegreesToRadians(cameraYaw);
        float pitchRad = qDegreesToRadians(cameraPitch);

        // Calculate right vector
        float rightX = std::cos(yawRad);
        float rightZ = std::sin(yawRad);
        float rightY = 0;

        // Calculate up vector (always world up)
        float upX = 0;
        float upY = 1;
        float upZ = 0;

        // Calculate forward vector
        float forwardX = std::sin(yawRad) * std::cos(pitchRad);
        float forwardY = -std::sin(pitchRad);
        float forwardZ = -std::cos(yawRad) * std::cos(pitchRad);

        // Pan horizontally (screen right/left)
        cameraX += delta.x() * moveSpeed * rightX;
        cameraY += delta.x() * moveSpeed * rightY;
        cameraZ += delta.x() * moveSpeed * rightZ;

        // Pan vertically (screen up/down)
        cameraX += delta.y() * moveSpeed * upX;
        cameraY += delta.y() * moveSpeed * upY;
        cameraZ += delta.y() * moveSpeed * upZ;
    }

    lastMousePos = event->pos();
    update();
}

void OpenGLWidget::wheelEvent(QWheelEvent *event) {
    // Zoom in/out using mouse wheel
    float zoomSpeed = 0.01f;
    cameraDistance -= event->angleDelta().y() * zoomSpeed;

    // Limit zoom range
    cameraDistance = qBound(1.0f, cameraDistance, 10.0f);

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
    float luzPosicion[] = {0, 0, 2.0f, 1};

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_POSITION, luzPosicion);

    // Apply camera transformations
    glTranslatef(-cameraX, -cameraY, -cameraZ);
    glTranslatef(0, 0, -cameraDistance);
    glRotatef(cameraPitch, 1, 0, 0);   // Pitch rotation
    glRotatef(cameraYaw, 0, 1, 0);     // Yaw rotation

    glColor3f(1, 0, 0);
    objeto3D->desplegar();
}
