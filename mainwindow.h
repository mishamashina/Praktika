#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "serialportreader.h"
#include "serialportwriter.h"
#include <QMainWindow>
#include <QSerialPort>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    SerialPortReader* reader;
    SerialPortWriter* writer;
    QSerialPort* serialPort;

};
#endif // MAINWINDOW_H
