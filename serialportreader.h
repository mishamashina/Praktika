#ifndef SERIALPORTREADER_H
#define SERIALPORTREADER_H

#include <QByteArray>
#include <QSerialPort>
#include <QTextStream>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class SerialPortReader : public QObject
{
    Q_OBJECT

public:
    explicit SerialPortReader(QSerialPort *serialPort, QObject *parent = nullptr);
    QSerialPort *m_serialPort = nullptr;
    QByteArray m_readData;
    QTextStream m_standardOutput;
    QTimer m_timer;
    Ui::MainWindow *ui;

public slots:
    void handleReadyRead();
//    void handleTimeout();
//    void handleError(QSerialPort::SerialPortError error);
signals:
    void onFrequency(int tc, int num_im, int num_freq);
    void offFrequency(int tc, int num_im);
    void controlReport(int tc, int num_im);

private:
};
#endif // SERIALPORTREADER_H
