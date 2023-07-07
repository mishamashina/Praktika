#ifndef SERIALPORTWRITER_H
#define SERIALPORTWRITER_H
#include <QByteArray>
#include <QObject>
#include <QSerialPort>
#include <QTextStream>
#include <QTimer>

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

class SerialPortWriter : public QObject
{
    Q_OBJECT
public:
    explicit SerialPortWriter(QSerialPort *serialPort, QObject *parent = nullptr);//нет родителя
    void write(const QByteArray &writeData);//ссылка на класс

    QSerialPort *m_serialPort = nullptr;
    QByteArray m_writeData;
    QTextStream m_standardOutput;
    qint64 m_bytesWritten = 0;
    QTimer m_timer;
private slots:
    void handleBytesWritten(qint64 bytes);
//    void handleTimeout();
//    void handleError(QSerialPort::SerialPortError error);

};

#endif // SERIALPORTWRITER_H
