#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "serialportreader.h"
#include <QByteArray>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)   : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Имитаторы");
    serialPort0 = new QSerialPort(this);//выделили память для объекта класса QSerialPort. доступ к нему через указатель

    serialPort0->setPortName("/dev/ttyUSB0");//разыменовка
    serialPort0->setBaudRate(QSerialPort::Baud4800);
    serialPort0->setDataBits(QSerialPort::Data8);
    serialPort0->setStopBits(QSerialPort::OneStop);
    serialPort0->setParity(QSerialPort::NoParity);
    serialPort0->setFlowControl(QSerialPort::NoFlowControl);

    serialPort0->open(QIODevice::ReadWrite);

    QByteArray writeData;
    writeData.resize(4);
    writeData[0] = 0xf3;
    writeData[1] = 0x01;
    writeData[2] = 0x01;
    writeData[3] = 0x04;

    writer = new SerialPortWriter(serialPort0);
    writer->write(writeData);

    serialPort1 = new QSerialPort(this);

    serialPort1->setPortName("/dev/ttyUSB1");//разыменовка
    serialPort1->setBaudRate(QSerialPort::Baud4800);
    serialPort1->setDataBits(QSerialPort::Data8);
    serialPort1->setStopBits(QSerialPort::OneStop);
    serialPort1->setParity(QSerialPort::NoParity);
    serialPort1->setFlowControl(QSerialPort::NoFlowControl);

    serialPort1->open(QIODevice::ReadWrite);

    reader = new SerialPortReader(serialPort1);
    reader->handleReadyRead();

    connect(reader,&SerialPortReader::onFrequency, this, &MainWindow::onFrequency);
    connect(reader, &SerialPortReader::offFrequency, this, &MainWindow::offFrequency);
    connect(reader, &SerialPortReader::controlReport, this, &MainWindow::controlReport);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onFrequency(int num_im, int num_freq) {
    qDebug()<<"Зашел"<<QString::number(num_im);
    switch(num_im) {
        case 1:
//        ui->label_13->clear();
        ui->label_13->setText("Излучение: № " + QString::number(num_freq));
        break;
    }
}

void MainWindow::offFrequency(int num_im)
{
    switch(num_im) {
        case 1:
//        ui->label_13->clear();
        ui->label_13->setText("Излучение: выкл");
        break;
    }
}
void MainWindow::controlReport(int num_ui)
{
    unsigned char flag =0;
    switch(num_ui)
    {
        case 1:
        if ( ui->checkBox->checkState()){
            flag |= 1 << 0;
        }
        else
        {
            flag &= ~(1 << (1));
        }

        if ( ui->checkBox_2->checkState()){
            flag |= 1 << (2);
        }
        else
        {
            flag &= ~(1 << (2));
        }

        if ( ui->checkBox_3->checkState()){
            flag |= 1 << (3);
        }
        else
        {
            flag &= ~(1 << (3));
        }



    }
    QByteArray writeData;
    writeData.resize(4);
    writeData[0] = 0xf3;
    writeData[1] = num_ui;
    writeData[2] = 0x55;
    writeData[3] = flag;

    writer->write(writeData);
}
