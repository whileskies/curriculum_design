#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QDesktopWidget>
#include "chattcpsocket.h"
#include "chatwindow.h"
#include "serverjson.h"
#include "clientjson.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setChatSocket(ChatTcpSocket *chatSocket);
    bool checkFormInput();
    bool checkip(QString ip);
private slots:
    void connectServer();

    void recvMsg(const QString &data);

private:
    Ui::MainWindow *ui;
    ChatTcpSocket *chatSocket;
    ChatWindow *chatWin;
    QDesktopWidget* desktop;
};

#endif // MAINWINDOW_H
