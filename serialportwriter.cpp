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
}

void SerialPortWriter::handleBytesWritten(qint64 bytes)
{
    m_bytesWritten += bytes;
    if (m_bytesWritten == m_writeData.size()) {
        m_bytesWritten = 0;
        m_standardOutput << QObject::tr("Data successfully sent to port %1")
                            .arg(m_serialPort->portName()) << "\n";
    }
}


void SerialPortWriter::write(const QByteArray &writeData)
{
    m_writeData = writeData;

    const qint64 bytesWritten = m_serialPort->write(writeData);
    qDebug()<<QString::number(bytesWritten);

}
