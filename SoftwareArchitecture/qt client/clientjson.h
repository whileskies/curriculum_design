#ifndef CLIENTJSON_H
#define CLIENTJSON_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>


namespace clientjson {
    const int ONLINE_CODE = 0;
    const int OFFLINE_CODE = 1;
    const int SENDMSG_CODE = 2;
    const int GROUP_MEMBERS_LIST_CODE = 3;

    class Online {
    private:
        int code;
        QString email;
        QString name;
        int groupid;
    public:
        Online(int pcode, QString pemail, QString pname, int pgroupid) :
            code(pcode), email(pemail), name(pname), groupid(pgroupid) {}

        QString toJson() const {
            QJsonObject json;
            json.insert("code", code);
            json.insert("email", email);
            json.insert("name", name);
            json.insert("groupid", groupid);

            QJsonDocument document;
            document.setObject(json);
            QByteArray byteArray = document.toJson(QJsonDocument::Compact);
            return QString(byteArray) + "\n";
        }
    };

    class Offline {
    private:
        int code;
        QString email;

    public:
        Offline(int pcode, QString pemail) : code(pcode), email(pemail) {}

        QString toJson() const {
            QJsonObject json;
            json.insert("code", code);
            json.insert("email", email);

            QJsonDocument document;
            document.setObject(json);
            QByteArray byteArray = document.toJson(QJsonDocument::Compact);
            return QString(byteArray) + "\n";
        }
    };


    class SendMsg {
    private:
        int code;
        QString email;
        QString msg;
    public:
        SendMsg(int pcode, QString pemail, QString pmsg) :
            code(pcode), email(pemail), msg(pmsg) {}

        QString toJson() const {
            QJsonObject json;
            json.insert("code", code);
            json.insert("email", email);
            json.insert("msg", msg);

            QJsonDocument document;
            document.setObject(json);
            QByteArray byteArray = document.toJson(QJsonDocument::Compact);
            return QString(byteArray) + "\n";
        }
    };

    class GroupMembersList {
    private:
        int code;
        QString email;

    public:
        GroupMembersList(int pcode, QString pemail) : code(pcode), email(pemail) {}

        QString toJson() const {
            QJsonObject json;
            json.insert("code", code);
            json.insert("email", email);

            QJsonDocument document;
            document.setObject(json);
            QByteArray byteArray = document.toJson(QJsonDocument::Compact);
            return QString(byteArray) + "\n";
        }
    };
}

#endif // CLIENTJSON_H
