#include "serialportreader.h"

#include <QCoreApplication>
#include <QDebug>
#include <QCheckBox>

SerialPortReader::SerialPortReader(QSerialPort *serialPort, QObject *parent) :
    QObject(parent),
    m_serialPort(serialPort),
    m_standardOutput(stdout)
{
    connect(m_serialPort, &QSerialPort::readyRead, this, &SerialPortReader::handleReadyRead);//когда что-то приходит на порт мы читаем
    /*connect(m_serialPort, &QSerialPort::errorOccurred, this, &SerialPortReader::handleError);*///если случилась ошибка вызывается слот обратотать ошибку
    //connect(&m_timer, &QTimer::timeout, this, &SerialPortReader::handleTimeout);

//    m_timer.start(5000);
}

void SerialPortReader::handleReadyRead()
{
    qDebug() << "ready read";
    m_readData.clear()  ;
//    qDebug() << "Размер массива ДО";
//    qDebug() << m_readData.size();
//    qDebug() << m_readData;
    m_readData.append(m_serialPort->readAll());
//    qDebug() << "Размер массива ПОСЛЕ";
//    qDebug() << m_readData.size();
    qDebug() << m_readData;

    if (m_readData[0] = 0xf1)
    {
        emit onFrequency(m_readData[1],m_readData[3]);
    };
    if (m_readData[0] = 0xf2)
    {
        emit offFrequency(m_readData[0]);
    }


//    if (!m_timer.isActive())
//        m_timer.start(5000);
}

//void SerialPortReader::handleTimeout()
//{
//    if (m_readData.isEmpty()) {
//        m_standardOutput << QObject::tr("No data was currently available "
//                                        "for reading from port %1")
//                            .arg(m_serialPort->portName())
//                         << "\n";
//    } else {
//        m_standardOutput << QObject::tr("Data successfully received from port %1")
//                            .arg(m_serialPort->portName())
//                         << "\n";
//        m_standardOutput << m_readData << "\n";
//    }

//    QCoreApplication::quit();
//}

//void SerialPortReader::handleError(QSerialPort::SerialPortError serialPortError)
//{
//    qDebug() << "ready read";
//    if (serialPortError == QSerialPort::ReadError) {
//        m_standardOutput << QObject::tr("An I/O error occurred while reading "
//                                        "the data from port %1, error: %2")
//                            .arg(m_serialPort->portName())
//                            .arg(m_serialPort->errorString())
//                         << "\n";
//        QCoreApplication::exit(1);
//    }
//}
