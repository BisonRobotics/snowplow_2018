#include <QApplication>
#include <QWidget>

#include "MainInterface.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    // for embedding other threaded applications:
    app.setAttribute(Qt::AA_X11InitThreads, true);

    MainInterface window;
    window.setWindowTitle("Snowplow Interface");
    //window.resize(640, 480); // x, y
    window.show();

    return app.exec();
}
