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
public:
    DebugConsole(QWidget* parent = 0);
private:
    QLabel* fileDump;
    QLineEdit* filename;
    QTextEdit* debug;

    QPushButton* startfiledump;
    QPushButton* cleardebug;
};

DebugConsole::DebugConsole(QWidget* parent) : QWidget(parent) {
    QGridLayout* grid = new QGridLayout();

    // allocate space for widgets
    fileDump      = new QLabel("Filename: ", this);
    filename      = new QLineEdit(this);
    debug         = new QTextEdit(this);
    startfiledump = new QPushButton("Begin file dump", this);
    cleardebug    = new QPushButton("Clear debug window", this);

    // QTextEdit window will be read-only
    debug->setReadOnly(true);

    // certain widgets behave a lil differently
    fileDump     ->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    startfiledump->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    cleardebug   ->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    // debug window takes all available space in its layout
    debug->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // add widgets to grid layout
    grid->addWidget(fileDump,      0, 0);
    grid->addWidget(filename,      0, 1, 1, 3);
    grid->addWidget(startfiledump, 0, 4);

    grid->addWidget(debug,         1, 0, 3, 4);
    grid->addWidget(cleardebug,    2, 4);

    setLayout(grid);

}

#endif // __JCC__DEBUGCONSOLE__HPP__
