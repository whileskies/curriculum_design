#include "chatwindow.h"
#include "mainwindow.h"
#include "clientjson.h"
#include <QApplication>

#include <iostream>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ChatTcpSocket chatSocket;
    MainWindow w;
    w.setChatSocket(&chatSocket);
    w.show();

    return a.exec();
}
