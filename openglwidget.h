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
    QBasicTimer timer;
    void initializeGL();
    void paintGL();
    void timerEvent(QTimerEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *e);
};

#endif // OPENGLWIDGET_H
