/*#include <QWidget>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTime>
#include <QTextEdit>
#include <QLCDNumber>
#include <QPushButton>
*/
#include "ButtonPad.h"

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
    connect(aiBtn, SIGNAL(clicked()), this, SLOT(toggleAI()));
    grid->addWidget(aiBtn, 0, 2, 2, 1);

    // add pushbuttons to grid layout
    grid->addWidget(btn1, 0, 0);
    grid->addWidget(btn2, 0, 1);
    grid->addWidget(btn3, 1, 0);
    grid->addWidget(btn4, 1, 1);

    setLayout(grid);
}

void ButtonPad::toggleAI(void) {
    isAI = !isAI;
    if(isAI) {
        emit sendAIToggleMessage(QString("<font style=\"color:#FF00FF\">[AI_t] AI toggled: on</font>"));
    } else {
        emit sendAIToggleMessage(QString("<font style=\"color:#FF00FF\">[AI_t] AI toggled: off</font>"));
    }
}
