#include "chatwindow.h"
#include "ui_chatwindow.h"

ChatWindow::ChatWindow(ChatTcpSocket *pChatSocket,
                       QWidget *parent) :
                        QMainWindow(parent),
                        ui(new Ui::ChatWindow),
                        chatSocket(pChatSocket) {
    ui->setupUi(this);

    email = chatSocket->getEmail();
    name = chatSocket->getName();
    groupid = chatSocket->getGroupid();

    //禁止最大化
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);

    //窗口居中
    desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);

    //标题与关于设置
    setWindowTitle(tr("聊天室"));
    QAction *aboutAction = new QAction(tr("关于"), this);
    QMenu *about = menuBar()->addMenu("关于");
    about->addAction(aboutAction);
    connect(aboutAction, &QAction::triggered, this, &ChatWindow::showAbout);

    //连接socket接收到消息的信号槽
    connect(chatSocket, &ChatTcpSocket::recvMsg, this, &ChatWindow::recvMsg);
    //connect(chatSocket, &ChatTcpSocket::disconn, this, &ChatWindow::disconn);

    //请求在线用户
    chatSocket->sendRequestMembersList();

    tableFormat.setBorder(0);

    ui->memberList->addItem(new QListWidgetItem(QIcon(":/pic/group"), "聊天室id: " + QString::number(groupid)));

    ui->sendButton->setShortcut(Qt::Key_Enter);
    ui->sendButton->setShortcut(Qt::Key_Return);

    connect(this->ui->sendButton, &QPushButton::clicked, this, &ChatWindow::sendMsg);
    connect(this->ui->leaveButton, &QPushButton::clicked, this, &ChatWindow::leaveChat);
}

ChatWindow::~ChatWindow() {
    delete ui;
}

//显示个人信息
void ChatWindow::showAbout() {
    QMessageBox::about(this, "关于", "姓名：高天<br>学号：201616030213");
}

void ChatWindow::recvMsg(const QString &data) {
    serverjson::ParseServerJson p(data);

    switch (p.getCode()) {
    case serverjson::USER_ONLINE_CODE:
        newUserOnline(p.getEmail(), p.getName());
        break;
    case serverjson::USER_OFFLINE_CODE:
        if (membersMap.contains(p.getEmail())) {
            userOffline(p.getEmail(), membersMap[p.getEmail()]);
        }
        break;
    case serverjson::USER_MSG_CODE:
        if (membersMap.contains(p.getEmail())) {
            newUserMsg(p.getEmail(), membersMap[p.getEmail()], p.getMsg(), p.getTime());
        }
        break;
    case serverjson::GROUP_MEMBER_LIST_CODE:
        disGroupMembersList(p.getMembers());
        break;
    }
    qDebug() << "recv: " << data << endl;
}

//与服务器端开连接
void ChatWindow::disconn()
{

}

//发送消息
void ChatWindow::sendMsg()
{
    QString msg = ui->msgText->text();

    if (msg.trimmed().isEmpty())
        return;

    chatSocket->sendMsg(email, msg);

    ui->msgText->setText("");
}

//新用户上线在聊天框显示
void ChatWindow::newUserOnline(const QString email, const QString name) {
    QTextCursor cursor(ui->chatMsgs->textCursor());
    cursor.movePosition(QTextCursor::End);
    QTextTable *table = cursor.insertTable(1, 1, tableFormat);
    table->cellAt(0, 0).firstCursorPosition().insertHtml("<font color='grey'>" + name + "&lt;" + email + "&gt; 加入了群聊 </font>");

    ui->memberList->addItem(name + "<" + email + ">");
    membersMap.insert(email, name);

    QScrollBar *bar = ui->chatMsgs->verticalScrollBar();
    bar->setValue(bar->maximum());
}

void ChatWindow::userOffline(const QString email, const QString name) {
    QList<QListWidgetItem *> items = ui->memberList->findItems("<" + email + ">",
                                                           Qt::MatchEndsWith);
    if (items.isEmpty())
        return;
    membersMap.remove(email);
    delete items.at(0);
    QTextCursor cursor(ui->chatMsgs->textCursor());
    cursor.movePosition(QTextCursor::End);
    QTextTable *table = cursor.insertTable(1, 1, tableFormat);
    table->cellAt(0, 0).firstCursorPosition().insertHtml("<font color='grey'>" + name + "&lt;" + email + "&gt; 退出了群聊 </font>");

    QScrollBar *bar = ui->chatMsgs->verticalScrollBar();
    bar->setValue(bar->maximum());
}

void ChatWindow::newUserMsg(const QString email, const QString name, const QString msg, const QDateTime time) {
    if (QString::compare(email, this->email) == 0) {
        QTextCursor cursor(ui->chatMsgs->textCursor());
        cursor.movePosition(QTextCursor::End);
        QTextTable *table = cursor.insertTable(2, 1, tableFormat);

        qDebug() << "name: " << name << endl;
        table->cellAt(0, 0).firstCursorPosition().insertHtml("<font color='blue'>"+ name + "&lt;" + email + "&gt;  " + time.toLocalTime().toString("M/dd hh:mm:ss") + "</font>");
        table->cellAt(1, 0).firstCursorPosition().insertHtml("<font color='blue'>"+ msg + "</font> <br>");
    } else {
        QTextCursor cursor(ui->chatMsgs->textCursor());
        cursor.movePosition(QTextCursor::End);
        QTextTable *table = cursor.insertTable(2, 1, tableFormat);
        table->cellAt(0, 0).firstCursorPosition().insertHtml(name +  "&lt;" + email + "&gt;  " + time.toLocalTime().toString("M/dd hh:mm:ss"));
        table->cellAt(1, 0).firstCursorPosition().insertHtml(msg + "<br>");
    }

    QScrollBar *bar = ui->chatMsgs->verticalScrollBar();
    bar->setValue(bar->maximum());
}

//显示组成员列表
void ChatWindow::disGroupMembersList(const QList<serverjson::Member> members) {
    foreach(serverjson::Member m , members) {
        membersMap.insert(m.getEmail(), m.getName());
        if (m.getEmail().compare(email) == 0)
            ui->memberList->addItem("我 <" + m.getEmail() + ">");
        else
            ui->memberList->addItem(m.getName() + "<" + m.getEmail() + ">");
    }
}

//退出聊天
void ChatWindow::leaveChat() {
    chatSocket->disconnected();
    this->close();
}


