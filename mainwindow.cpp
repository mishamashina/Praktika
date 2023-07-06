#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "serialportreader.h"
MainWindow::MainWindow(QWidget *parent)   : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Имитаторы");
    serialPort = new QSerialPort(this);//выделили память для объекта класса QSerialPort. доступ к нему через указатель

    serialPort->setPortName("/dev/ttyUSB1");//разыменовка
    serialPort->setBaudRate(QSerialPort::Baud4800);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    serialPort->open(QIODevice::ReadWrite);

    const QByteArray writeData("test message");

//    SerialPortReader serialPortReader(serialPort);
//    serialPortReader.handleReadyRead();

    writer = new SerialPortWriter(serialPort);
    writer->write(writeData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

