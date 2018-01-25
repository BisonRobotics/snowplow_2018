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
Q_OBJECT
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

    QLCDNumber* ul;
    QLCDNumber* ll;
    QLCDNumber* ur;
    QLCDNumber* lr;
};

#endif // __JJC__SLIDERWHEEL__HPP__
