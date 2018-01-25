#ifndef __JJC__MAININTERFACE__HPP__
#define __JJC__MAININTERFACE__HPP__

#include <QWidget>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTime>
#include <QTextEdit>
#include <QLCDNumber>
#include <QTabWidget>

#include "ButtonPad.h"
#include "SliderWheel.h"
#include "DebugConsole.h"
#include "OpenGL-Widget.h"

class MainInterface : public QWidget {
Q_OBJECT
public:
    MainInterface(QWidget* parent = 0);
private:
    ButtonPad*        bpad;
    SliderWheel*      sliders;
    DebugConsole*     debug;
    glWidgetConsole*  opengl;
};

#endif // __JJC__MAININTERFACE__HPP__







