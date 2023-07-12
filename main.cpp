#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QFile>
#include <QSerialPort>
#include <QStringList>
#include <QTextStream>
int main(int argc, char *argv[])
{
    QApplication coreApplication(argc, argv);

    MainWindow w;
    w.show();

    return coreApplication.exec();
}
