/*
#include <QWidget>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTime>
#include <QTextEdit>
#include <QLCDNumber>
*/
#include "SliderWheel.h"

SliderWheel::SliderWheel(QWidget* parent) : QWidget(parent) {
    // allocate space for lcd's
    ul = new QLCDNumber(4);
    ll = new QLCDNumber(4);
    ur = new QLCDNumber(4);
    lr = new QLCDNumber(4);

    // all of these values will be in percent
    lm_actual = new QSlider(Qt::Vertical, this);
    lm_wanted = new QSlider(Qt::Vertical, this);
    rm_wanted = new QSlider(Qt::Vertical, this);
    rm_actual = new QSlider(Qt::Vertical, this);

    // allocate space for labels
    lm_actual_lbl = new QLabel("Left motor\nMeasured", this);
    lm_wanted_lbl = new QLabel("Left motor\nCalculated", this);
    rm_wanted_lbl = new QLabel("Right motor\nCalculated", this);
    rm_actual_lbl = new QLabel("Right motor\nMeasured", this);

    // set tick positions on sliders
    lm_actual->setTickPosition(QSlider::TicksRight);
    lm_wanted->setTickPosition(QSlider::TicksLeft);
    rm_wanted->setTickPosition(QSlider::TicksRight);
    rm_actual->setTickPosition(QSlider::TicksLeft);

    // sliders expand vertically to fill available space
    lm_actual->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    lm_wanted->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    rm_wanted->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    rm_actual->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    // lcds expand
    ul->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ll->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ur->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lr->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // each label and its slider have their own vbox
    QVBoxLayout* vb1 = new QVBoxLayout();
    QVBoxLayout* vb2 = new QVBoxLayout();
    QVBoxLayout* vb3 = new QVBoxLayout();
    QVBoxLayout* vb4 = new QVBoxLayout();

    // build up each vbox
    vb1->addWidget(lm_actual_lbl);
    vb1->addWidget(lm_actual);

    vb2->addWidget(lm_wanted_lbl);
    vb2->addWidget(lm_wanted);

    vb3->addWidget(rm_wanted_lbl);
    vb3->addWidget(rm_wanted);

    vb4->addWidget(rm_actual_lbl);
    vb4->addWidget(rm_actual);

    QHBoxLayout* sliders = new QHBoxLayout();
    sliders->addLayout(vb1);
    sliders->addLayout(vb2);
    sliders->addLayout(vb3);
    sliders->addLayout(vb4);

    QVBoxLayout* misc = new QVBoxLayout();
    misc->addWidget(new QLabel("Calculated Speed (meters/second)", this));
    misc->addWidget(ul);
    misc->addWidget(new QLabel("Actual Speed (meters/second)", this));
    misc->addWidget(ll);

    sliders->addLayout(misc);

    setLayout(sliders);

}
