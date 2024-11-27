#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QBasicTimer>
#include <QOpenGLWidget>
#include <QMouseEvent>

class OpenGLWidget : public QOpenGLWidget
{
public:
    OpenGLWidget();
private:
    int anguloAgregar;
    int anguloY;
    QBasicTimer timer;
    void initializeGL();
    void paintGL();
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void timerEvent(QTimerEvent *);
};

#endif // OPENGLWIDGET_H
