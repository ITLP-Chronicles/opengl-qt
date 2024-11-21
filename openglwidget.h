#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>

class OpenGLWidget : public QOpenGLWidget
{
public:
    OpenGLWidget();
private:
    void initializeGL();
    void paintGL();
};

#endif // OPENGLWIDGET_H
