
#include "DebugConsole.h"

DebugConsole::DebugConsole(QWidget* parent) : QWidget(parent) {
    QGridLayout* grid = new QGridLayout();

    // allocate space for widgets
    fileDump      = new QLabel("Filename: ", this);
    filename      = new QLineEdit(this);
    debug         = new QTextEdit(this);
    startfiledump = new QPushButton("Begin file dump", this);
    cleardebug    = new QPushButton("Clear debug window", this);

    connect(cleardebug,    SIGNAL(clicked()), this, SLOT(clearDebugWindow())); // local signal
    connect(startfiledump, SIGNAL(clicked()), this, SLOT(fileDumpMsg())); // local signal

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

void DebugConsole::fileDumpMsg(void) {
    append(QString("<font style=\"color:#0000FF\">[f_dump] file dump initiated </font>"));
    QString contents = debug->toHtml();
    QString file     = filename->text();
    if(file.isEmpty()) {
        append(QString("<font style=\"color:#0000FF\">[f_dump] no file name given </font>"));
        return;
    }
    QFile doc(file);
    doc.write(contents);
}



/*
11-28-16

permutations and combinations
    S is a set containing n elements
Permutation of k objects from S
    Ordered arrangement of k objects from S with no repetitions allowed

    S = {a, b, c}, n=|S|=3
        2 objects from S    1 object from S     3 objects from S
            a, b                a                   a, b, c
            b, a                b                   a, c, b
            b, c                c                   b, a, c
            c, b                                    b, c, a
            a, c                                    c, a, b
            c, a                                    c, b, a


    P(n, k) = # of permutations of k objects from n
            = n(n-1)..(n-k+1)
            = n(n-1)...(n-k+1)(n-k)(n-k-1)(n-k-2)...2 1          n!
             -------------------------------------------   =   --------
                              (n-k)(n-k-1)(n-k-2)...2 1          (n-k)!

Combination of k objects from S
    Unordered collection of k objects from S with no repetitions allowed

    S={a, b, c}, n = |S| = 3
        2 objects from S
            a, b
            b, c
            a, c

        1 object from S
            a
            b
            c

        3 objects from S
            a, b, c     // no repetitions

    P(n, n) = n!        P(k, k) = k!

    C(n, m) = ( n ) = # of combinations of k object from n
              ( k )

    C(n, k)k! = P(n, k)

                P(n, k)           n!
    C(n, k) = -----------  =  ----------
                   k!          k!(n-k)!

            = n(n-1)(n-2)...(n-k+1)
             -----------------------
              1  2    3        k

                  n!         n(n-1)(n-2)...*2*1
    P(n, k) = ---------- = ----------------------
                (n-k)!        (n-1)(n-2)...*2*1

Example:
    how many committees can you form with 4 or 5 members from a group of 435 persons

    {{435}, {4}}

    435 * 434 * 433 * 432
    ---------------------
     1     2     3     4

     {{435}, {5}}

     435 * 434 * 433 * 432 * 431
     ---------------------------
      1     2     3     4     5

Example:
    how many bit strings of length 10 can you form with exactly 4 1's

        10 * 9 * 8 * 7
     = ---------------- = 210
         1 * 2 * 3 * 4

    210

Example:
    how many bit strings containing exactly fifteen zeroes and six ones, if every one must be followed by a zero

    {{15}, {6}} = {{15}, {9}}

*/











