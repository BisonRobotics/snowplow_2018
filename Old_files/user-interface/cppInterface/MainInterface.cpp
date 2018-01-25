#include <QWidget>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTime>
#include <QTextEdit>
#include <QLCDNumber>
#include <QTabWidget>

#include "MainInterface.h"

MainInterface::MainInterface(QWidget* parent) : QWidget(parent) {

    QTabWidget* tabs = new QTabWidget(this); // top-level widget

    bpad     = new ButtonPad();
    sliders  = new SliderWheel();
    debug    = new DebugConsole();
    opengl   = new glWidgetConsole();

    connect(opengl, SIGNAL(sendGLMessage(QString, int, int, int)),       debug, SLOT(append(QString, int, int, int))); // debug msgs from OpenGL-Widget
    connect(bpad,   SIGNAL(sendAIToggleMessage(QString, int, int, int)), debug, SLOT(append(QString, int, int, int))); // debug msgs from ButtonPad

    bpad->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tabs->setFixedSize(800, 500);

    tabs->addTab(bpad,    "Button Pad");
    tabs->addTab(sliders, "Motors");
    tabs->addTab(debug,   "Debug Console");
    tabs->addTab(opengl,  "OpenGL Console");
}
