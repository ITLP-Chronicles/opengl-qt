#include "openglwidget.h"

OpenGLWidget::OpenGLWidget() {}

void OpenGLWidget::initializeGL() {
    glClearColor(1,1,1,0);
}

void OpenGLWidget::paintGL() {
    glLoadIdentity();

    glRotatef(10, 1.0, 1.0, 0);
    // Cara roja
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    // Cara verde
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glEnd();

    // Cara azul
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    // Cara amarilla
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glEnd();

    // Cara naranja
    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glEnd();

    // Cara blanca
    glColor3f(0.9, 0.9, 0.9);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glEnd();

    /*
    glTranslatef(0.25,0.25,0.0);
    glScalef(-0.5,-0.5,0);
    glRotatef(45, 0.0, 0.0, 1.0);
    glTranslatef(-0.25,-0.25,0.0);
    */

}
