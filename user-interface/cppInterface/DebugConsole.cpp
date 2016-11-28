
#include "DebugConsole.h"

DebugConsole::DebugConsole(QWidget* parent) : QWidget(parent) {
    QGridLayout* grid = new QGridLayout();

    // allocate space for widgets
    fileDump      = new QLabel("Filename: ", this);
    filename      = new QLineEdit(this);
    debug         = new QTextEdit(this);
    startfiledump = new QPushButton("Begin file dump", this);
    cleardebug    = new QPushButton("Clear debug window", this);

    connect(cleardebug, SIGNAL(clicked()), this, SLOT(clearDebugWindow())); // local signal

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

void DebugConsole::append(const QString& text) {
    debug->textCursor().insertHtml(text);
    debug->textCursor().insertText(QString('\n'));
    debug->textCursor().movePosition(QTextCursor::End);
    debug->setTextCursor(debug->textCursor());
}

void DebugConsole::clearDebugWindow(void) {
    debug->clear();
    append(QString("<font style=\"color:#00FFFF\">[debug] debug window cleared </font>"));
}
