#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QBasicTimer>
#include <QMouseEvent>

class OpenGLWidget : public QOpenGLWidget
{
public:
    OpenGLWidget();
private:
    int angulo;
    int sentido;

    float mouseX;
    float mouseY;
    QBasicTimer timer;
    void initializeGL();
    void paintGL();
    void timerEvent(QTimerEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
};

#endif // OPENGLWIDGET_H
