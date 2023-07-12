#include "mainwindow.h"
#include "serialportwriter.h"
#include <QApplication>
#include <QCoreApplication>
#include <QFile>
#include <QSerialPort>
#include <QStringList>
#include <QTextStream>
#include "serialportreader.h"
int main(int argc, char *argv[])
{
    QApplication coreApplication(argc, argv);

    MainWindow w;
    w.show();

    return coreApplication.exec();
}
