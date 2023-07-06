#ifndef SENDERTHREAD_H
#define SENDERTHREAD_H
#include <QSerialPort>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class SenderThread : public QThread
{
    Q_OBJECT

public:
    explicit SenderThread(QObject *parent = nullptr);
    ~SenderThread();

    void transaction(const QString &portName, int waitTimeout, const QString &request);

signals:
    void response(const QString &s);
    void error(const QString &s);
    void timeout(const QString &s);

private:
    void run() override;

    QString m_portName;
    QString m_request;
    int m_waitTimeout = 0;
    QMutex m_mutex;
    QWaitCondition m_cond;
    bool m_quit = false;
};

#endif // SENDERTHREAD_H
