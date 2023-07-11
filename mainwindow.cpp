#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "serialportreader.h"
#include <QByteArray>
#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)   : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Имитаторы");
    serialPort0 = new QSerialPort(this);//выделили память для объекта класса QSerialPort. доступ к нему через указатель

    serialPort0->setPortName("/dev/ttyUSB0");//разыменовка

    serialPort0->setBaudRate(QSerialPort::Baud4800);
    ui->comboBox_2->setCurrentIndex(3);
    serialPort0->setDataBits(QSerialPort::Data8);
    ui->comboBox_3->setCurrentIndex(2);
    serialPort0->setStopBits(QSerialPort::OneStop);
    ui->comboBox_5->setCurrentIndex(0);
    serialPort0->setParity(QSerialPort::NoParity);
    ui->comboBox_4->setCurrentIndex(1);
    serialPort0->setFlowControl(QSerialPort::NoFlowControl);
    ui->comboBox_6->setCurrentIndex(1);

//    ui->pushButton_2->clicked(serialPort0->clo);

    serialPort0->open(QIODevice::ReadWrite);

    writer = new SerialPortWriter(serialPort0);

    reader = new SerialPortReader(serialPort0,ui);
    reader->handleReadyRead();

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::Clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::Clicked_Butt2);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::Clicked_Butt3);

    connect(reader, &SerialPortReader::onFrequency, this, &MainWindow::onFrequency);
    connect(reader, &SerialPortReader::offFrequency, this, &MainWindow::offFrequency);
    connect(reader, &SerialPortReader::controlReport, this, &MainWindow::controlReport);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Clicked()
{
    serialPort0->close();
}

void MainWindow::Clicked_Butt2()
{
    ui->pushButton_2->setText("RS вкл");
//    ui->pushButton_2->setDown(true);
}
void MainWindow::Clicked_Butt3()
{
    ui->pushButton_3->setText("RS вкл");
//    ui->pushButton_3->setDown(true);

}



void MainWindow::onFrequency(int tc, int num_im, int num_freq) {
    qDebug()<<"Зашел"<<QString::number(num_im);
    switch(num_im) {
        case 1:
        {
            ui->label_12->setText("Излучение: № " + QString::number(num_freq));
            break;
        }
        case 2:
        {
            ui->label_11->setText("Излучение: № " + QString::number(num_freq));
            break;
        }

    }
    QByteArray writeData;
    writeData.resize(4);
    writeData[0] = tc;
    writeData[1] = num_im;
    writeData[2] = 0x01;
    writeData[3] = num_freq;

    writer->write(writeData);
}

void MainWindow::offFrequency(int tc, int num_im)
{
    switch(num_im) {
        case 1:
        {
            ui->label_12->setText("Излучение: выкл");
            break;
        }
        case 2:
        {
            ui->label_11->setText("Излучение: выкл");
            break;
        }

    }
    QByteArray writeData;
    writeData.resize(4);
    writeData[0] = tc;
    writeData[1] = num_im;
    writeData[2] = 0x00;
    writeData[3] = 0x00;

    writer->write(writeData);
}
void MainWindow::controlReport(int tc, int num_ui)
{
    unsigned char flag =0;
    switch(num_ui)
    {
        case 1:
        {
            QList<QCheckBox *> group_8 = ui->groupBox_8->findChildren<QCheckBox *>();
            qDebug() <<"Count:"<<group_8.size();
            for(int i = 0; i < group_8.size(); ++i)
            {
                if(group_8.at(i)->checkState())
                {
                    if (i==7)
                    {
                        flag &= ~(1 << (i));
                        continue;
                    }
                    flag |= 1 << i;
                    qDebug() << "Use" << group_8.at(i)->text()<< i;//or what you need
                }
                else
                {
                    if (i == 7)
                    {
                        flag |= 1 << i;
                        continue;
                    }
                    flag &= ~(1 << (i));
                }
            }
            break;
        }

        case 2:
        {
            QList<QCheckBox *> group_9 = ui->groupBox_9->findChildren<QCheckBox *>();
            qDebug() <<"Count:"<<group_9.size();
            for(int i = 0; i < group_9.size(); ++i)
            {
                if(group_9.at(i)->checkState())
                {
                    if (i==7)
                    {
                        flag &= ~(1 << (i));
                        continue;
                    }
                    flag |= 1 << i;
                    qDebug() << "Use" << group_9.at(i)->text()<< i;//or what you need
                }
                else
                {
                    if (i == 7)
                    {
                        flag |= 1 << i;
                        continue;
                    }
                    flag &= ~(1 << (i));
                }
            }
            break;
        }

    }
    QByteArray writeData;
    writeData.resize(4);
    writeData[0] = tc;
    writeData[1] = num_ui;
    writeData[2] = 0x55;
    writeData[3] = flag;

    writer->write(writeData);
}
