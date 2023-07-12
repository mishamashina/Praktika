#include "serialportreader.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QCoreApplication>
#include <QDebug>
#include <QCheckBox>

SerialPortReader::SerialPortReader(QSerialPort *serialPort, QObject *parent) :
    QObject(parent),
    m_serialPort(serialPort),
    m_standardOutput(stdout)
{
    connect(m_serialPort, &QSerialPort::readyRead, this, &SerialPortReader::handleReadyRead);//когда что-то приходит на порт мы читаем
}

void SerialPortReader::handleReadyRead()
{

    m_readData.clear()  ;
    m_readData.append(m_serialPort->readAll());
    qDebug() << m_readData;
    if (m_readData.size() < 4) return;

    if ((uint8_t)m_readData.at(0) == 0xf1)
    {
        emit onFrequency(m_readData[0], m_readData[1] ,m_readData[3]);
    };
    if ((uint8_t)m_readData.at(0) == 0xf2)
    {
         emit offFrequency(m_readData[0], m_readData[1]);

    };
    if ((uint8_t)m_readData.at(0) == 0xf3)

    {
        emit controlReport(m_readData[0], m_readData[1]);
    };

};

