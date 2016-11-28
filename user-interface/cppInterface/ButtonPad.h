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
Q_OBJECT
public:
    ButtonPad(QWidget* parent = 0);
public slots:
    void toggleAI(void);
signals:
    void sendAIToggleMessage(const QString& text);
private:
    QPushButton* btn1;
    QPushButton* btn2;
    QPushButton* btn3;
    QPushButton* btn4;
    QPushButton* aiBtn;

    bool isAI = false; // start in manual control mode
};

#endif // __JJC__BUTTONPAD__HPP__
