#include "serialportwriter.h"
#include <QCoreApplication>
#include <QDebug>

SerialPortWriter::SerialPortWriter(QSerialPort *serialPort, QObject *parent) :
    QObject(parent),
    m_serialPort(serialPort),
    m_standardOutput(stdout)
{
    m_timer.setSingleShot(true);
    connect(m_serialPort, &QSerialPort::bytesWritten,
            this, &SerialPortWriter::handleBytesWritten);
//    connect(m_serialPort, &QSerialPort::errorOccurred,
//            this, &SerialPortWriter::handleError);
//    connect(&m_timer, &QTimer::timeout, this, &SerialPortWriter::handleTimeout);
}

void SerialPortWriter::handleBytesWritten(qint64 bytes)
{
    m_bytesWritten += bytes;
    if (m_bytesWritten == m_writeData.size()) {
        m_bytesWritten = 0;
        m_standardOutput << QObject::tr("Data successfully sent to port %1")
                            .arg(m_serialPort->portName()) << "\n";
        //QCoreApplication::quit();
    }
}

//void SerialPortWriter::handleTimeout()
//{
//    m_standardOutput << QObject::tr("Operation timed out for port %1, error: %2")
//                        .arg(m_serialPort->portName())
//                        .arg(m_serialPort->errorString())
//                     << "\n";
//    //QCoreApplication::exit(1);
//}

//void SerialPortWriter::handleError(QSerialPort::SerialPortError serialPortError)
//{
//    if (serialPortError == QSerialPort::WriteError) {
//        m_standardOutput << QObject::tr("An I/O error occurred while writing"
//                                        " the data to port %1, error: %2")
//                            .arg(m_serialPort->portName())
//                            .arg(m_serialPort->errorString())
//                         << "\n";
//        QCoreApplication::exit(1);
//    }
//}

void SerialPortWriter::write(const QByteArray &writeData)
{
    m_writeData = writeData;

    const qint64 bytesWritten = m_serialPort->write(writeData);
    qDebug()<<QString::number(bytesWritten);

}
