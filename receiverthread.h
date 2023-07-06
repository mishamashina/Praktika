#ifndef RECEIVERTHREAD_H
#define RECEIVERTHREAD_H
#include <QSerialPort>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class ReceiverThread : public QThread//Класс QThread обеспечивает способ управления потоками
{
    Q_OBJECT

public:

    explicit ReceiverThread(QObject *parent = nullptr);
    ~ReceiverThread();

    void startReceiver(const QString &portName, int waitTimeout, const QString &response);

signals:
    void request(const QString &s);
    void error(const QString &s);
    void timeout(const QString &s);
private:
    void run() override;

    QString m_portName;
    QString m_response;
    int m_waitTimeout = 0;
    QMutex m_mutex;//Сериализация — процесс перевода структуры данных в битовую последовательность
    bool m_quit = false;
};

#endif // RECEIVERTHREAD_H
