#include "chattcpsocket.h"

ChatTcpSocket::ChatTcpSocket(QObject *parent) : QObject(parent) {

}

QHostAddress ChatTcpSocket::getAdd() const {
    return add;
}

void ChatTcpSocket::setAdd(const QHostAddress &value) {
    add = value;
}

quint16 ChatTcpSocket::getPort() const
{
    return port;
}

void ChatTcpSocket::setPort(const quint16 &value) {
    port = value;
}

QString ChatTcpSocket::getName() const {
    return name;
}

void ChatTcpSocket::setName(const QString &value) {
    name = value;
}

QString ChatTcpSocket::getEmail() const {
    return email;
}

void ChatTcpSocket::setEmail(const QString &value) {
    email = value;
}

int ChatTcpSocket::getGroupid() const {
    return groupid;
}

void ChatTcpSocket::setGroupid(const int groupid) {
    this->groupid = groupid;
}

//连接服务器，返回是否成功
bool ChatTcpSocket::connectToServer() {
    socket.connectToHost(add, port);

    return socket.waitForConnected(3000);
}

//发送上线信息
void ChatTcpSocket::sendOnline() {
    clientjson::Online on(clientjson::ONLINE_CODE, email, name, groupid);
    sendMsgToServer(on.toJson());
}

//用户发送信息
void ChatTcpSocket::sendMsg(const QString &email, const QString &msg) {
    clientjson::SendMsg m(clientjson::SENDMSG_CODE, email, msg);
    sendMsgToServer(m.toJson());
}

//开始接收消息
void ChatTcpSocket::startRecvMsg() {
    connect(&socket, &QTcpSocket::readyRead, this, &ChatTcpSocket::transferMsg);
    connect(&socket, &QTcpSocket::disconnected, this, &ChatTcpSocket::disconnSlot);
}

//请求成员列表
void ChatTcpSocket::sendRequestMembersList() {
    clientjson::GroupMembersList g(clientjson::GROUP_MEMBERS_LIST_CODE, email);
    sendMsgToServer(g.toJson());
}

//接收到消息时发送信号
void ChatTcpSocket::transferMsg() {
    QByteArray netdata = socket.readLine();

    emit recvMsg(QString(netdata));
}


//向服务器发送数据
void ChatTcpSocket::sendMsgToServer(const QString &data) {
    QByteArray ba = data.toUtf8();
    socket.write(ba.data());
    socket.flush();
}

 void ChatTcpSocket::disconnected() {
     socket.close();
 }

 void ChatTcpSocket::disconnSlot() {
    emit disconn();
 }




