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
    float cameraDistance;
    float cameraYaw;
    float cameraPitch;
    QPoint lastMousePos;
    bool isLeftButtonPressed;
    bool isRightButtonPressed;
    float cameraX, cameraY, cameraZ;

    int angulo;
    QBasicTimer timer;
    int sentido;
    float focoX;
    float focoY;
    Objeto3D* objeto3D;
    void initializeGL();
    void paintGL();
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
};

#endif // OPENGLWIDGET_H
