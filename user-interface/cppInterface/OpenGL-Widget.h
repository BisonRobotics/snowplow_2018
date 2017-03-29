#ifndef __JJC__OPENGLWIDGET__HPP__
#define __JJC__OPENGLWIDGET__HPP__

#include <QtOpenGL/QGLWidget>
#include <QWidget>
#include <QTimer>
#include <QObject>

#include <iostream>

#include <GL/glu.h>

class glWidgetConsole : public QGLWidget {
Q_OBJECT
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

public slots:
    void updateGL(void);

signals:
    void sendGLMessage(const QString& text, int r, int g, int b);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void mousePressEvent(QMouseEvent *event) {
        std::cout << "Mouse press event" << std::endl;
        xRot += 10.0f;
        paintGL();
    }

    void mouseMoveEvent(QMouseEvent *event) {
        std::cout << "Mouse move event" << std::endl;
    }


private:
    QColor qtGreen;
    QColor qtPurple;
    GLfloat xRot = 0.0f;
};



#endif // __JJC__OPENGLWIDGET__HPP__
