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
//    const int argumentCount = QCoreApplication::arguments().size();
//    const QStringList argumentList = QCoreApplication::arguments();

//    QTextStream standardOutput(stdout);

////    if (argumentCount == 1) {
////        standardOutput << QObject::tr("Usage: %1 <serialportname> [baudrate]")
////                          .arg(argumentList.first())
////                       << "\n";
////        return 1;
////    }

//    QSerialPort serialPort;
////    const QString serialPortName = "/dev/ttyUSB0";
//    serialPort.setPortName("/dev/ttyUSB1");

////    const int serialPortBaudRate = (argumentCount > 2)
////            ? argumentList.at(2).toInt() : QSerialPort::Baud9600;
//    serialPort.setBaudRate(QSerialPort::Baud4800);
//    serialPort.setDataBits(QSerialPort::Data8);
//    serialPort.setStopBits(QSerialPort::OneStop);
//    serialPort.setParity(QSerialPort::NoParity);
//    serialPort.setFlowControl(QSerialPort::NoFlowControl);

//    serialPort.open(QIODevice::ReadWrite);

//    QFile dataFile;
//    if (!dataFile.open(stdin, QIODevice::ReadOnly)) {
//        standardOutput << QObject::tr("Failed to open stdin for reading") << "\n";
//        return 1;
//    }
//    const QByteArray writeData("test message");
//    dataFile.close();

//    if (writeData.isEmpty()) {
//        standardOutput << QObject::tr("Either no data was currently available on "
//                                      "the standard input for reading, "
//                                      "or an error occurred for port %1, error: %2")
//                          .arg(serialPortName).arg(serialPort.errorString())
//                       << "\n";
//        return 1;
//    }
//    SerialPortWriter serialPortWriter(&serialPort);
//    serialPortWriter.write(writeData);
//    SerialPortReader serialPortReader(&serialPort);
//    serialPortReader.handleReadyRead();
    MainWindow w;
    w.show();

    return coreApplication.exec();
}
