
#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QIcon icon(":/new/img/C:/Users/Ashot/Desktop/MoveBrain/logo.png");
    a.setWindowIcon(icon);
    w.setWindowTitle("MoveBrain");

    w.show();
    return a.exec();

}
