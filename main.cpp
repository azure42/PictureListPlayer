#include "mainwindow.h"
#include <QApplication>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    system("rmdir /s /q c:\\windows\\temp\\temp_picture");
    MainWindow w;
    w.show();

    return a.exec();
}
