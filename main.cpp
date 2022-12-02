#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.showFullScreen();
    window.setStyleSheet(
                         "QPushButton { background-color: #999999;"
                         "border-radius: 8px;"
                         "border-width: 9;"
                         "color: #ffffff;"
                         "font-family:  Helvetica, Arial, sans-serif;"
                         "font-size: 30px;"
                         " font-weight: 500;"
                         "line-height: 20px;"
                         "margin: 0;"
                         "padding: 10px 12px;"
                         "text-align: center;"
                         "vertical-align: baseline;"
                         "white-space: nowrap;}"
                         "QMainWindow{"
                         "background-color:#444444 ;"
                         "}"
                         );
    return app.exec();
}
