#include "openglwidget.h"

OpenGLWidget::OpenGLWidget() {}

void OpenGLWidget::initializeGL() {
    glClearColor(0,0,0,0);
    anguloAgregar = 1;
    timer.start(50, this);
}

void OpenGLWidget::paintGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLoadIdentity();

    float luzAmbiente[] = {0.2, 0.2, 0.2, 1};
    float luzDifusa[] = {1.0, 1.0, 1.0,1};
    float luzPosicion[] = {0, 1, 1, 1};

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_POSITION, luzPosicion);

    glRotated(anguloY, 0, 1 ,0);
    glRotated(15, 1, 0 ,0);
    glTranslatef(-0.25, -0.25, 0.25);
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);

    //Blanco
    glNormal3f(0, 0, 1);
    //glColor3f(1, 1, 1);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.5, 0.5, 0.0);
    glVertex3f(0.0, 0.5, 0.0);

    //Rojo
    glNormal3f(0, 0, -1);
    //glColor3f(1, 0, 0);
    glVertex3f(0.0, 0.0, -0.5);
    glVertex3f(0.0, 0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.0, -0.5);

    //Azul
    glNormal3f(1, 0, 0);
    //glColor3f(0, 0, 1);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.5, 0.0, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.0);

    //Naranja
    glNormal3f(-1, 0, 0);
    //glColor3f(1, 0.5, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
    glVertex3f(0.0, 0.5, -0.5);
    glVertex3f(0.0, 0.0, -0.5);

    //Verde
    glNormal3f(0, 1, 0);
    //glColor3f(0, 1, 0);
    glVertex3f(0.0, 0.5, 0.0);
    glVertex3f(0.5, 0.5, 0.0);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.0, 0.5, -0.5);

    //Amarillo
    glNormal3f(0, -1, 0);
    //glColor3f(1, 1, 0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, -0.5);
    glVertex3f(0.5, 0.0, -0.5);
    glVertex3f(0.5, 0.0, 0.0);

    glEnd();
}


void OpenGLWidget::mouseMoveEvent(QMouseEvent *_){
    update();
}


void OpenGLWidget::mousePressEvent(QMouseEvent *event){
    timer.start(50, this);

    if (event->button() == Qt::RightButton)
        anguloAgregar = 1;
    else
        anguloAgregar = -1;

    update();
}


void OpenGLWidget::mouseReleaseEvent(QMouseEvent *_){
    timer.stop();
}


void OpenGLWidget::timerEvent(QTimerEvent *_){
    anguloY += anguloAgregar;
    update();
}
