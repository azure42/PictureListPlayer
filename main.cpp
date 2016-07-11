#include "mainwindow.h"
#include <QApplication>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    system("rmdir /s /q d:\\disposal_picture");
    MainWindow w;
    w.show();

    return a.exec();
}
