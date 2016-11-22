#ifndef __JJC__SLIDERWHEEL__HPP__
#define __JJC__SLIDERWHEEL__HPP__

#include <QWidget>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTime>
#include <QTextEdit>
#include <QLCDNumber>

class SliderWheel : public QWidget {
public:
    SliderWheel(QWidget* parent = 0);
private:
    QSlider* lm_actual; // left motor, actual measured speed
    QSlider* lm_wanted; // left motor speed command
    QSlider* rm_wanted; // right motor speed command
    QSlider* rm_actual; // right motor, actual measured speed

    QLabel* lm_actual_lbl;
    QLabel* lm_wanted_lbl;
    QLabel* rm_wanted_lbl;
    QLabel* rm_actual_lbl;
};

SliderWheel::SliderWheel(QWidget* parent) : QWidget(parent) {
    QGridLayout* grid = new QGridLayout();

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

    // sliders expand to fill available space
    lm_actual->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    lm_wanted->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    rm_wanted->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    rm_actual->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    // add labels to grid
    grid->addWidget(lm_actual_lbl, 0, 0);
    grid->addWidget(lm_wanted_lbl, 0, 1);
    grid->addWidget(rm_wanted_lbl, 0, 2);
    grid->addWidget(rm_actual_lbl, 0, 3);

    // add sliders to grid
    grid->addWidget(lm_actual, 1, 0);
    grid->addWidget(lm_wanted, 1, 1);
    grid->addWidget(rm_wanted, 1, 2);
    grid->addWidget(rm_actual, 1, 3);

    setLayout(grid);
}

#endif // __JJC__SLIDERWHEEL__HPP__
