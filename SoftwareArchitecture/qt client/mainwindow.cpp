
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);

    desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::connectServer);

    ui->startButton->setShortcut(Qt::Key_Enter);
    ui->startButton->setShortcut(Qt::Key_Return);

    ui->ipText->setText("39.96.65.11");
    ui->portText->setText("9000");
    //ui->nameText->setText("高天");
    //ui->emailText->setText("gt110@qq.com");
    ui->groupText->setText("1");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setChatSocket(ChatTcpSocket *chatSocket) {
    this->chatSocket = chatSocket;
    //接收到消息的信号槽
    connect(chatSocket, &ChatTcpSocket::recvMsg, this, &MainWindow::recvMsg);
}

//校验IP地址格式
bool MainWindow::checkip(QString ip) {
    QRegExp rx("^(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\."
               "(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])$");
     if( !rx.exactMatch(ip) )
     {
           return false;
     }
     return true;
}

//校验文本框输入
bool MainWindow::checkFormInput() {
    if (ui->ipText->text().trimmed().isEmpty()) {
        QMessageBox::information(this, tr("提示"), tr("ip不能为空"));
        return false;
    }
    if (!checkip(ui->ipText->text().trimmed())) {
        QMessageBox::information(this, tr("提示"), tr("ip地址格式不正确"));
        return false;
    }
    if (ui->portText->text().trimmed().isEmpty()) {
        QMessageBox::information(this, tr("提示"), tr("端口不能为空"));
        return false;
    }
    if (ui->emailText->text().trimmed().isEmpty()) {
        QMessageBox::information(this, tr("提示"), tr("邮箱不能为空"));
        return false;
    }
    if (ui->nameText->text().trimmed().isEmpty()) {
        QMessageBox::information(this, tr("提示"), tr("名称不能为空"));
        return false;
    }
    if (ui->groupText->text().trimmed().toInt() < 0) {
        QMessageBox::information(this, tr("提示"), tr("聊天组id不能为负"));
        return false;
    }

    return true;
}

//连接服务器
void MainWindow::connectServer() {
    if (checkFormInput()) {

        QHostAddress add(QHostAddress(ui->ipText->text().trimmed()));
        quint16 port = static_cast<quint16>(ui->portText->text().toInt());
        QString name = ui->nameText->text().trimmed();
        QString email = ui->emailText->text().trimmed();
        int groupid = ui->groupText->text().trimmed().toInt();

        chatSocket->setAdd(add);
        chatSocket->setPort(port);
        chatSocket->setName(name);
        chatSocket->setEmail(email);
        chatSocket->setGroupid(groupid);
        if (chatSocket->connectToServer()) {

            chatSocket->sendOnline();
            chatSocket->startRecvMsg();

        } else {
            QMessageBox::information(this, tr("错误"), tr("连接服务器失败"));
        }
        //qDebug() << ui->ipText->text() << " " << ui->portText->text() << " " << ui->nameText->text();
    }

}

void MainWindow::recvMsg(const QString &data) {
    qDebug() << data << endl;
    serverjson::ParseServerJson p(data);
    if (p.getCode() == serverjson::ADD_GROUP_INFO_CODE) {
        if (p.getStatus()) {
            //加入群组成功

            //取消接收消息信号槽连接
            disconnect(chatSocket, &ChatTcpSocket::recvMsg, this, &MainWindow::recvMsg);
            chatWin = new ChatWindow(chatSocket, this);
            this->hide();
            chatWin->show();
        } else {
            //加入群组失败，显示消息框
            QMessageBox::information(this, tr("错误"), tr("该Email正在聊天..."));
        }
    }
}


