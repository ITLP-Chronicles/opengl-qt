#include "openglwidget.h"

OpenGLWidget::OpenGLWidget() {}

void OpenGLWidget::initializeGL() {
    angulo = 1;

    glEnable(GL_COLOR_MATERIAL);
    glClearColor(1,1,1,0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    timer.start(50,this);
}

void OpenGLWidget::timerEvent(QTimerEvent *){
    angulo++;
    update();
}

void OpenGLWidget::mousePressEvent(QMouseEvent *e){
    timer.start(50, this);
    if(e->button() == Qt::RightButton){
        sentido = 1;
    }
    else if(e->button()==Qt::LeftButton){
        sentido = -1;
    }
    angulo += sentido;
}
void OpenGLWidget::mouseReleaseEvent(QMouseEvent *e){
    timer.stop();
}

void OpenGLWidget::paintGL() {
    glEnable(GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLoadIdentity();


    glNormal3f(0, 0, 1);
    glColor3f(1, 0, 0);

    glLoadIdentity();

    glTranslatef(0.25, 0.25, -0.25);
    glRotatef(10, 1.0, 0, 0);
    glRotatef(angulo, 0, 1.0, 0);
    glTranslatef(-0.25, -0.25, 0.25);
    float luzAmbiente[] = {0.2, 0.2, 0.2, 1};
    float luzDifusa[] = {1.0, 1.0, 1.0, 1};
    float luzPosicion[] = {0, 1, 1, 1};

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_POSITION, luzPosicion);

    glBegin(GL_QUADS);

    glColor3f(1, 0, 0);

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
