#ifndef SERVERJSON_H
#define SERVERJSON_H

#include <QJsonDocument>
#include <QString>
#include <QTime>
#include <QVariantMap>
#include <QVector>


namespace serverjson {
    const int USER_ONLINE_CODE = 100;
    const int USER_OFFLINE_CODE = 101;
    const int USER_MSG_CODE = 102;
    const int GROUP_MEMBER_LIST_CODE = 103;
    const int ADD_GROUP_INFO_CODE = 104;

    class Member {
    public:
        Member(const QString &pemail, const QString pname) : email(pemail),
            name(pname) {}
        QString getEmail() const { return email; }
        void setEmail(const QString &email) { this->email = email; }

        QString getName() const { return name; }
        void setName(const QString &name) { this->name = name; }

    private:
        QString email;
        QString name;

    };

    class ParseServerJson {
    private:
        int code = -1;
        QString email;
        QString name;
        QString msg;
        QDateTime time;
        QList<Member> members;
        bool status;
        QString desc;
    public:
        ParseServerJson(const QString &json) {
            QJsonParseError error;
            // 2. 使用静态函数获取 QJsonDocument 对象
            QJsonDocument jsonDocument = QJsonDocument::fromJson(json.toUtf8(), &error);
            // 3. 根据解析结果进行处理
            if (error.error == QJsonParseError::NoError) {
                if (!(jsonDocument.isNull() || jsonDocument.isEmpty())) {
                    if (jsonDocument.isObject()) {
                        QVariantMap ret = jsonDocument.toVariant().toMap();
                        if (ret.contains("code"))
                            code = ret["code"].toInt();
                        if (ret.contains("email"))
                            email = ret["email"].toString();
                        if (ret.contains("name"))
                            name = ret["name"].toString();
                        if (ret.contains("msg"))
                            msg = ret["msg"].toString();
                        if (ret.contains("time"))
                            time = QDateTime::fromTime_t(static_cast<uint>(ret["time"].toInt()));
                        if (ret.contains("members")) {
                            QList<QVariant> list = ret["members"].toList();
                            foreach(QVariant v, list) {
                               QVariantMap map = v.toMap();
                               Member m(map["email"].toString(), map["name"].toString());
                               members.push_back(m);
                            }
                        }
                        if (ret.contains("status"))
                            status = ret["status"].toBool();
                        if (ret.contains("desc"))
                            desc = ret["desc"].toString();
                    } else if (jsonDocument.isArray()) {
                        // ...
                    }
                }
            } else {
                // 检查错误类型
            }
        }

        int getCode() const { return code; }
        QString getEmail() const { return email; }
        QString getName() const { return name; }
        QString getMsg() const { return msg; }
        QDateTime getTime() const { return time; }
        QList<Member> getMembers() const { return members; }
        bool getStatus() const { return status; }
        QString getDesc() const { return desc; }
    };


}

#endif // SERVERJSON_H
