#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QBasicTimer>
#include <QMouseEvent>
#include "objeto3d.h"

class OpenGLWidget : public QOpenGLWidget
{
public:
    OpenGLWidget();
private:
    int angulo;
    QBasicTimer timer;
    int sentido;
    float focoX;
    float focoY;
    Objeto3D* objeto3D;
    void initializeGL();
    void paintGL();
    void mouseMoveEvent(QMouseEvent *);
    void timerEvent(QTimerEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // OPENGLWIDGET_H
