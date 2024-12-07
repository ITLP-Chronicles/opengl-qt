#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QBasicTimer>
#include <QMouseEvent>
#include <QTimer>
#include <QKeyEvent>
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
    float lightX = 0.0f;
    float lightY = 0.0f;
    float lightZ = 2.0f;

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
protected:
    void timerEvent(QTimerEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // OPENGLWIDGET_H
