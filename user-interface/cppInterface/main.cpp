#include <QApplication>
#include <QWidget>

//#include "ButtonPad.hpp"
//#include "SliderWheel.hpp"
//#include "DebugConsole.hpp"
#include "MainInterface.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainInterface window;
    window.setWindowTitle("Snowplow Interface");
    window.resize(640, 480); // x, y
    window.show();

    return app.exec();
}
