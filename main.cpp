#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    В строке 7 создается объект класса QApplication, который управляет ресурсами приложения.
//    Конструктору QApplication передаются аргументы argc и argv, поскольку Qt имеет возможность
//    обрабатывать аргументы командной строки.
    MainWindow w;
    w.show();
    SenderThread serial;
    serial.transaction("ttyUSB0", 3000, "Прием");
    ReceiverThread serial1;
    serial1.startReceiver("ttyUSB1", 3000, "Слышу");
    return a.exec();
}
//В строке 13 выполняется передача управления библиотеке Qt. С этого момента программа переходит
//в режим ожидания, когда она ничего не делает, а просто ждет действий пользователя, например,
//нажатие на клавишу или кнопку мыши.
