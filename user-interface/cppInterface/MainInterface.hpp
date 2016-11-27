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

#include "ButtonPad.hpp"
#include "SliderWheel.hpp"
#include "DebugConsole.hpp"
#include "OpenGL-Widget.hpp"

class MainInterface : public QWidget {
public:
    MainInterface(QWidget* parent = 0);
private:
    ButtonPad*        bpad;
    SliderWheel*      sliders;
    DebugConsole*     debug;
    glWidgetConsole*  opengl;
};

MainInterface::MainInterface(QWidget* parent) : QWidget(parent) {

    QTabWidget* tabs = new QTabWidget(this); // top-level widget

    bpad     = new ButtonPad();
    sliders  = new SliderWheel();
    debug    = new DebugConsole();
    opengl   = new glWidgetConsole();

    bpad->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tabs->setFixedSize(640, 480);

    tabs->addTab(bpad,    "Button Pad");
    tabs->addTab(sliders, "Motors");
    tabs->addTab(debug,   "Debug Console");
    tabs->addTab(opengl,  "OpenGL Console");
}

#endif // __JJC__MAININTERFACE__HPP__







