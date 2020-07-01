#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDesktopWidget>
#include <QMainWindow>
#include <QTextTableFormat>
#include <QMessageBox>
#include <QScrollBar>
#include <QTextTable>
#include <QListWidget>

#include "chattcpsocket.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(ChatTcpSocket *pChatSocket,
                        QWidget *parent = nullptr);
    ~ChatWindow();

private slots:
    void showAbout();
    void recvMsg(const QString &data);
    void disconn();

private:
    Ui::ChatWindow *ui;

    ChatTcpSocket *chatSocket;

    QDesktopWidget* desktop;
    QTextTableFormat tableFormat;

    QString email;
    QString name;
    int groupid;
    QMap<QString, QString> membersMap;

    void sendMsg();
    void newUserOnline(const QString email, const QString name);
    void userOffline(const QString email, const QString name);
    void newUserMsg(const QString email, const QString name, const QString msg, const QDateTime time);
    void disGroupMembersList(const QList<serverjson::Member> members);
    void leaveChat();
};

#endif // CHATWINDOW_H
