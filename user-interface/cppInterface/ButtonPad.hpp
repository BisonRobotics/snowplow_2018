#ifndef __JJC__BUTTONPAD__HPP__
#define __JJC__BUTTONPAD__HPP__

#include <QWidget>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTime>
#include <QTextEdit>
#include <QLCDNumber>
#include <QPushButton>

class ButtonPad : public QWidget {
public:
    ButtonPad(QWidget* parent = 0);
private:
    QPushButton* btn1;
    QPushButton* btn2;
    QPushButton* btn3;
    QPushButton* btn4;
    QPushButton* aiBtn;
};

ButtonPad::ButtonPad(QWidget* parent) : QWidget(parent) {
    QGridLayout* grid = new QGridLayout();
    grid->setSpacing(2);

    // allocate QPushButtons
    btn1 = new QPushButton("Button 1", this);
    btn2 = new QPushButton("Button 2", this);
    btn3 = new QPushButton("Button 3", this);
    btn4 = new QPushButton("Button 4", this);

    // buttons will expand to fill available space
    btn1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btn2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btn3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btn4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // special button toggles AI/Manual control
    aiBtn = new QPushButton("Toggle AI", this);
    aiBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    grid->addWidget(aiBtn, 0, 2, 2, 1);

    // add pushbuttons to grid layout
    grid->addWidget(btn1, 0, 0);
    grid->addWidget(btn2, 0, 1);
    grid->addWidget(btn3, 1, 0);
    grid->addWidget(btn4, 1, 1);

    setLayout(grid);
}

#endif // __JJC__BUTTONPAD__HPP__
