#include "openglwidget.h"

OpenGLWidget::OpenGLWidget() {
    angulo=15;
    sentido=1;
    focoX = 0.0f;
    focoY = 1.0f;
    setMouseTracking(true);
    objeto3D=new Objeto3D();
    Superficie* s=new Superficie(1,0,0);
    s->agregar(new Vertice(0,0,0));
    s->agregar(new Vertice(0.5,0,0));
    s->agregar(new Vertice(0.5,0.5,0));
    s->agregar(new Vertice(0,0.5,0));
    objeto3D->agregar(s);
    s = new Superficie(1,0,0);
    s->agregar(new Vertice(0.5, 0, 0));
    s->agregar(new Vertice(0.5, 0, -0.5));
    s->agregar(new Vertice(0.5, 0.5, -0.5));
    s->agregar(new Vertice(0.5, 0.5, 0));
    objeto3D->agregar(s);
    s = new Superficie(1,0,0);
    s->agregar(new Vertice(0.5, 0, -0.5));
    s->agregar(new Vertice(0, 0, -0.5));
    s->agregar(new Vertice(0, 0.5, -0.5));
    s->agregar(new Vertice(0.5, 0.5, -0.5));
    objeto3D->agregar(s);
    s = new Superficie(1,0,0);
    s->agregar(new Vertice(0, 0, -0.5));
    s->agregar(new Vertice(0, 0, 0));
    s->agregar(new Vertice(0, 0.5, 0));
    s->agregar(new Vertice(0, 0.5, -0.5));
    objeto3D->agregar(s);
    s = new Superficie(1,0,0);
    s->agregar(new Vertice(0, 0.5, 0));
    s->agregar(new Vertice(0.5, 0.5, 0));
    s->agregar(new Vertice(0.5, 0.5, -0.5));
    s->agregar(new Vertice(0, 0.5, -0.5));
    objeto3D->agregar(s);
    s = new Superficie(1,0,0);
    s->agregar(new Vertice(0, 0, 0));
    s->agregar(new Vertice(0, 0, -0.5));
    s->agregar(new Vertice(0.5, 0, -0.5));
    s->agregar(new Vertice(0.5, 0, 0));
    objeto3D->agregar(s);
}

void OpenGLWidget::initializeGL() {
    glClearColor(1,1,1,0);
}

void OpenGLWidget::timerEvent(QTimerEvent *) {
    angulo+=sentido;
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
}
void OpenGLWidget::mouseReleaseEvent(QMouseEvent *){
    timer.stop();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *e) {

    int ancho = width();
    int alto = height();

    focoX = (2.0f * e->position().x() / ancho) - 1.0f;
    focoY = 1.0f - (2.0f * e->position().y() / alto);

    update();
}

void OpenGLWidget::paintGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLoadIdentity();

    // Configura la luz con las coordenadas dinámicas
    float luzAmbiente[] = {0.2, 0.2, 0.2, 1};
    float luzDifusa[] = {1.0, 1.0, 1.0, 1};
    float luzPosicion[] = {focoX, focoY, 2.0f, 1};
    float luz_aten[] = {0.2};

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_POSITION, luzPosicion);
    glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, luz_aten);

    glNormal3f(0, 0, 1);
    glColor3f(1, 0, 0);

    glTranslatef(0.25, 0.25, -3.5);
    glRotated(angulo, 0, 1, 0);
    glRotated(15, 1, 0, 0);
    glTranslatef(-0.25, -0.25, 0.25);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0,1.0,-1.0,1.0,2.0,10.0);
    glMatrixMode(GL_MODELVIEW);

    QSize tam=size();
    //glViewport(tam.width()/2,tam.height()/2,tam.width()/2,tam.height()/2);

    objeto3D->desplegar();

    Objeto3D* copia=objeto3D->copia();
    copia->transformar(new Matriz3D(1,0,0,1,0,1,0,0,0,0,1,0));
    float ang=(angulo*5*3.14159)/180.0;
    copia->rotar(ang,new Linea(1.25,0.25,0.0,1.25,0.25,-0.5));
    copia->desplegar();
}
