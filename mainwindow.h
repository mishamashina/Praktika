#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "serialportreader.h"
#include "serialportwriter.h"
#include <QMainWindow>
#include <QSerialPort>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    SerialPortReader* reader;
    SerialPortWriter* writer;
    QSerialPort* serialPort0;
    Ui::MainWindow *ui;

public slots:
    void onFrequency(int tc, int num_im, int num_freq);
    void offFrequency(int tc, int num_im);
    void controlReport(int tc, int num_im);
    void Clicked();
    void Clicked_Butt2();
    void Clicked_Butt3();
//    void noClicked();

};
#endif // MAINWINDOW_H
