
#include "OpenGL-Widget.h"
#include <iostream>


glWidgetConsole::glWidgetConsole(QWidget* parent) : //QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {
        QGLWidget(parent) {
    qtGreen  = QColor::fromCmykF(4.0,  0.0,  1.0, 0.0);
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer->start(50);
}

void glWidgetConsole::initializeGL() {
    qglClearColor(qtPurple.dark());
    glEnable(GL_DEPTH_TEST);
    makeCurrent();
}

void glWidgetConsole::resizeGL(int width, int height) {
    int side = qMin(width, height);
    glViewport((width-side)/2, (height-side)/2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.5, 0.5, -0.5, +0.5, 4.0, 15.0);
    glMatrixMode(GL_MODELVIEW);
}

void glWidgetConsole::paintGL() {
    static int numFrames = 0;
    //std::cout << "\tpaintGL called: " << numFrames << std::endl; // debug info
    if(!(numFrames % 20)) // approx 1/sec
        emit sendGLMessage(QString("[O_GL] GL Frame Update Recieved"), 255, 0, 0); // send to integrated debug console

    numFrames++;

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1, 0.1, 8000.0);
    gluLookAt(0,  4,   4,
              0,  0,   0,
              0,  1,   0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(xRot, 1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0, 0.0);
        glVertex2f(-0.5, -0.5);
        glVertex2f( 0.5, -0.5);
        glVertex2f( 0.5,  0.5);
        glVertex2f(-0.5,  0.5);
    glEnd();
    glEndList();
    glRotatef(xRot, 1.0, 0.0, 0.0);

    //xRot += 10.0;

    swapBuffers(); // buffer swap does implicit glFlush
}

void glWidgetConsole::updateGL() {
    paintGL();
}
