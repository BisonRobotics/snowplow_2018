/*
    Author: Joey Cluett
    Date Created: 11-2-2016

    Purpose:
        This file contains the main source code for a Qt4-
        based GUI for the 2017 snowplow, THUNDAR 3.0
*/

#include <QApplication>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QHBoxLayout>

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Enter your age");

    QSpinBox spinbox;
    QSlider  slider(Qt::Horizontal);
    spinbox.setRange(0, 130);
    slider.setRange(0, 130);

    QObject::connect(&spinbox, SIGNAL(valueChanged(int)),
                     &slider,  SIGNAL(setValue(int)));

    QObject::connect(&slider,  SIGNAL(valueChanged(int)),
                     &spinbox, SIGNAL(setValue(int)));

    spinbox.setValue(35);

    QHBoxLayout layout;
    layout.addWidget(&spinbox);
    layout.addWidget(&slider);

    window.setLayout(&layout);

    window.show();

    // run the application
    return app.exec();
}


























