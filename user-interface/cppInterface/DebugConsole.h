#ifndef __JCC__DEBUGCONSOLE__HPP__
#define __JJC__DEBUGCONSOLE__HPP__

#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTime>
#include <QTextEdit>
#include <QLCDNumber>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit> // for outputting debug info

class DebugConsole : public QWidget {
Q_OBJECT
public:
    DebugConsole(QWidget* parent = 0);
public slots:
    void append(const QString& text);
    void clearDebugWindow(void);
    void fileDumpMsg(void);
private:
    QLabel* fileDump;
    QLineEdit* filename;
    QTextEdit* debug;

    QPushButton* startfiledump;
    QPushButton* cleardebug;
};


#endif // __JCC__DEBUGCONSOLE__HPP__
