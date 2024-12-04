#include "openglwidget.h"
#include "utils.cpp"

OpenGLWidget::OpenGLWidget() {
    // Initial camera parameters
    cameraDistance = 3.5f;
    cameraYaw = 0.0f;
    cameraPitch = 15.0f;

    setMouseTracking(true);

    // Initialize 3D object
    objeto3D = new Objeto3D();
    Vertice o = Vertice(-0.2, -0.2, -0.2);
    CrearPrismaRectangular(objeto3D, o.x, o.y, o.z, 0.5, 0.5, 1); // Body

    // Track mouse movement states
    lastMousePos = QPoint(0, 0);
    isLeftButtonPressed = false;
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
        unsetCursor(); // Restore default cursor
    }
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
    if (isLeftButtonPressed) {
        // Calculate mouse movement delta
        QPoint delta = event->pos() - lastMousePos;

        // Adjust camera rotation based on mouse movement
        cameraYaw += delta.x() * 0.5f;     // Horizontal rotation
        cameraPitch += delta.y() * 0.5f;   // Vertical rotation

        // Limit pitch to prevent camera flipping
        cameraPitch = qBound(-89.0f, cameraPitch, 89.0f);

        lastMousePos = event->pos();
        update();
    }
}

void OpenGLWidget::wheelEvent(QWheelEvent *event) {
    // Zoom in/out using mouse wheel
    cameraDistance -= event->angleDelta().y() * 0.01f;

    // Limit zoom range
    cameraDistance = qBound(1.0f, cameraDistance, 10.0f);

    update();
}

void OpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 2.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Configure lighting with dynamic coordinates
    float luzAmbiente[] = {0.2, 0.2, 0.2, 1};
    float luzDifusa[] = {1.0, 1.0, 1.0, 1};
    float luzPosicion[] = {0, 0, 2.0f, 1};

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_POSITION, luzPosicion);

    // Apply camera transformations
    glTranslatef(0, 0, -cameraDistance);
    glRotatef(cameraPitch, 1, 0, 0);   // Pitch rotation
    glRotatef(cameraYaw, 0, 1, 0);     // Yaw rotation

    glColor3f(1, 0, 0);
    objeto3D->desplegar();
}
