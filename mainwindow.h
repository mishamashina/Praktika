#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//ПОЛУЧАТЕЛЬ
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

//ОТПРАВИТЕЛЬ
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


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
