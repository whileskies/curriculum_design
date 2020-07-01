#ifndef CHATTCPSOCKET_H
#define CHATTCPSOCKET_H

#include <QHostAddress>
#include <QObject>
#include <QTcpSocket>

#include "clientjson.h"
#include "serverjson.h"

/*
 * TCP连接层
 * 功能：与服务器连接，网络数据的输入输出
 */
class ChatTcpSocket : public QObject
{
    Q_OBJECT
public:

    explicit ChatTcpSocket(QObject *parent = nullptr);

    QHostAddress getAdd() const;
    void setAdd(const QHostAddress &value);

    quint16 getPort() const;
    void setPort(const quint16 &value);

    QString getName() const;
    void setName(const QString &value);

    QString getEmail() const;
    void setEmail(const QString &value);

    int getGroupid() const;
    void setGroupid(const int groupid);

    bool connectToServer();

    void sendOnline();
    void sendMsg(const QString &email, const QString &msg);
    void startRecvMsg();
    void sendRequestMembersList();

    void disconnected();


signals:
    void recvMsg(const QString &data);
    void disconn();


private slots:
    void transferMsg();
    void disconnSlot();

private:
    QTcpSocket socket;
    QHostAddress add;
    quint16 port;
    QString name;
    QString email;
    int groupid;

    void sendMsgToServer(const QString &data);
};

#endif // CHATTCPSOCKET_H
