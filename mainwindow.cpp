#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)   : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Имитаторы");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void ReceiverThread::startReceiver(const QString &portName, int waitTimeout, const QString &response)
{
    const QMutexLocker locker(&m_mutex);
    m_portName = portName;
    m_waitTimeout = waitTimeout;
    m_response = response;
    if (!isRunning())
        start();
    //The startReceiver() function stores the serial port name, timeout and response data
};

void ReceiverThread::run()
{
    bool currentPortNameChanged = false;

    m_mutex.lock();
    QString currentPortName;
    if (currentPortName != m_portName) {
        currentPortName = m_portName;
        currentPortNameChanged = true;
    }

    int currentWaitTimeout = m_waitTimeout;
    QString currentRespone = m_response;
    m_mutex.unlock();
};

void SenderThread::transaction(const QString &portName, int waitTimeout, const QString &request)
{
    const QMutexLocker locker(&m_mutex);
    m_portName = portName;
    m_waitTimeout = waitTimeout;
    m_request = request;
    if (!isRunning())
        start();
    else
        m_cond.wakeOne();
};

void SenderThread::run()
{
    bool currentPortNameChanged = false;

    m_mutex.lock();
    QString currentPortName;
    if (currentPortName != m_portName) {
        currentPortName = m_portName;
        currentPortNameChanged = true;
    }

    int currentWaitTimeout = m_waitTimeout;
    QString currentRequest = m_request;
    m_mutex.unlock();
};
