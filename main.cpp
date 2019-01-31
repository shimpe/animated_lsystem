#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowState(Qt::WindowFullScreen); // quit the program using alt+f4
    w.show();

    w.setRenderLive();
    w.startAnimation(25,0,10000);

    /*
    w.setRenderToFile("/home/shimpe/development/c++/build-lsystem-Debug-Release/render/starrynecklace");
    w.startAnimation(25,0,25*60*5);
    */

    return a.exec();
}
