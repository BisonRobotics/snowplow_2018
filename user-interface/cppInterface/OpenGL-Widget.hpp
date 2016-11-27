#ifndef __JJC__OPENGLWIDGET__HPP__
#define __JJC__OPENGLWIDGET__HPP__

#include <QGLWidget>
#include <QWidget>

class glWidgetConsole : public QGLWidget {
public:
    glWidgetConsole(QWidget* parent = 0);

    ~glWidgetConsole() { // destructor
        ;
    }

    QSize minimumSizeHint() const {
        return QSize(50, 50);
    }

    QSize sizeHint() const {
        return QSize(400, 400);
    }

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void mousePressEvent(QMouseEvent *event) {
        ;
    }

    void mouseMoveEvent(QMouseEvent *event) {
        ;
    }

private:
    QColor qtGreen;
    QColor qtPurple;
};

glWidgetConsole::glWidgetConsole(QWidget* parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {
    qtGreen  = QColor::fromCmykF(4.0,  0.0,  1.0, 0.0);
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
}

void glWidgetConsole::initializeGL() {
    qglClearColor(qtPurple.dark());
    glEnable(GL_DEPTH_TEST);
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
    glClear(GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}

#endif // __JJC__OPENGLWIDGET__HPP__
