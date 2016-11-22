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

#include "ButtonPad.hpp"
#include "SliderWheel.hpp"
#include "DebugConsole.hpp"

class MainInterface : public QWidget {
public:
    MainInterface(QWidget* parent = 0);
private:
    ButtonPad*    bpad;
    SliderWheel*  sliders;
    DebugConsole* debug;
};

MainInterface::MainInterface(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* vbox = new QVBoxLayout();
    QHBoxLayout* hbox = new QHBoxLayout(this); // top-level layout

    bpad    = new ButtonPad();
    sliders = new SliderWheel();
    debug   = new DebugConsole();

    vbox->addWidget(bpad);
    vbox->addWidget(debug);

    hbox->addLayout(vbox);
    hbox->addWidget(sliders);
}

#endif // __JJC__MAININTERFACE__HPP__







