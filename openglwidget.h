#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QBasicTimer>
#include <QMouseEvent>
#include <QTimer>
#include <QKeyEvent>
#include "objeto3d.h"
#include "fox.h"

class OpenGLWidget : public QOpenGLWidget
{
public:
    OpenGLWidget();
    ~OpenGLWidget();
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
    QTimer* timerHead;
    QTimer* timerTail;
    QTimer* timerFoxRotation;
    int sentido;
    float focoX;
    float focoY;
    Objeto3D *objeto3D;
    QTimer* timerRotateX;
    QTimer* timerRotateY;
    QTimer* timerRotateZ;
    float rotationDirection = 1.0f;
    // Key tracking
    bool keyUpPressed = false;
    bool keyDownPressed = false;
    bool keyLeftPressed = false;
    bool keyRightPressed = false;
    bool keyPageUpPressed = false;
    bool keyPageDownPressed = false;
    fox* initialFox = nullptr;  // Store initial state
    void resetFox();  // New function to handle reset
    void initializeGL() override;
    void paintGL() override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void wheelEvent(QWheelEvent *) override;
protected:
    void timerEvent(QTimerEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
private slots:
    void moveHeadTimer();
    void moveFoxRotationTimer();
    void moveTailTimer();
    void rotateXTimer();
    void rotateYTimer();
    void rotateZTimer();
};

#endif // OPENGLWIDGET_H
