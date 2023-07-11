#include "serialportreader.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QCoreApplication>
#include <QDebug>
#include <QCheckBox>

SerialPortReader::SerialPortReader(QSerialPort *serialPort, Ui::MainWindow * new_ui,   QObject *parent) :
    QObject(parent),
    m_serialPort(serialPort),
    m_standardOutput(stdout),
    ui(new_ui)
{
    connect(m_serialPort, &QSerialPort::readyRead, this, &SerialPortReader::handleReadyRead);//когда что-то приходит на порт мы читаем
}

void SerialPortReader::handleReadyRead()
{
//    ui->pushButton_2->setDown(false);
//    ui->pushButton_3->setDown(false);
    qDebug() << "ready read";
    m_readData.clear()  ;
    m_readData.append(m_serialPort->readAll());
    qDebug() << m_readData;
    if (m_readData.size() < 4) return;
    qDebug() << (ui->pushButton_2->isDown());
    qDebug() << (ui->pushButton_3->isDown());
    if ((uint8_t)m_readData.at(0) == 0xf1)
    {
//        if (!((ui->pushButton_2->isDown() && ((uint8_t)m_readData.at(1) == 1)) || (ui->pushButton_3->isDown() && ((uint8_t)m_readData.at(1) == 2))))
//        {
//            emit onFrequency(m_readData[0], m_readData[1] ,m_readData[3]);
//        }

        switch ((uint8_t)m_readData.at(1)) {
            case 0x1:
            {
                if (!(ui->pushButton_2->isDown()))
                {
//                    ui->pushButton_2->setDown(false);
                    emit onFrequency(m_readData[0], m_readData[1] ,m_readData[3]);
                }
            }
            case 0x2:
            {
                if (!(ui->pushButton_3->isDown()))
                {
                    emit onFrequency(m_readData[0], m_readData[1] ,m_readData[3]);
                }
            }
        }
    };
    if ((uint8_t)m_readData.at(0) == 0xf2)
    {
//        if (!((ui->pushButton_2->isDown() && ((uint8_t)m_readData.at(1) == 1)) || (ui->pushButton_3->isDown() && ((uint8_t)m_readData.at(1) == 2))))
//        {
//            emit offFrequency(m_readData[0], m_readData[1]);
//        }


        switch ((uint8_t)m_readData.at(1)) {
            case 0x1:
            {
                if (!(ui->pushButton_2->isDown()))
                {
                    emit offFrequency(m_readData[0], m_readData[1]);
                }
            }
            case 0x2:
            {
                if (!(ui->pushButton_3->isDown()))
                {
                    emit offFrequency(m_readData[0], m_readData[1]);
                }
            }
        }
    };
    if ((uint8_t)m_readData.at(0) == 0xf3)

    {
//        if (!((ui->pushButton_2->isDown() && ((uint8_t)m_readData.at(1) == 1)) || (ui->pushButton_3->isDown() && ((uint8_t)m_readData.at(1) == 2))))
//        {
//            emit controlReport(m_readData[0], m_readData[1]);
//        }

        switch ((uint8_t)m_readData.at(1)) {
            case 1:
            {
                if ((ui->pushButton_2->isDown()))
                {
                    emit controlReport(m_readData[0], m_readData[1]);
//                    qDebug() << (ui->pushButton_2->isDown());
                }
            }
            case 2:
            {
                if ((ui->pushButton_3->isDown()))
                {
                    emit controlReport(m_readData[0], m_readData[1]);
//                    qDebug() << (ui->pushButton_3->isDown());
                }
            }
        }
    };

};

