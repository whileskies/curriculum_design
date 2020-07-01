//
// Created by whileskies on 19-6-13.
//

#ifndef CHAT_SERVER_CLION_SERVERTOCLIENTMSG_H
#define CHAT_SERVER_CLION_SERVERTOCLIENTMSG_H

#include <string>
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/writer.h"
#include "../include/rapidjson/stringbuffer.h"

namespace service {
    class UserOnline {
    private:
        int code_;
        std::string email_;
        std::string name_;
        time_t time_;
    public:
        UserOnline(int code, std::string email, std::string name, time_t time) : code_(code),
                                                                                 email_(email), name_(name),
                                                                                 time_(time) {}

        ~UserOnline() = default;

        std::string to_json() const {
            rapidjson::Document d;
            d.SetObject();
            auto &allocator = d.GetAllocator();

            d.AddMember("code", code_, allocator);
            d.AddMember("email", rapidjson::StringRef(email_.c_str()), allocator);
            d.AddMember("name", rapidjson::StringRef(name_.c_str()), allocator);
            d.AddMember("time", time_, allocator);

            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

            d.Accept(writer);
            return buffer.GetString();
        }
    };

    class UserOffline {
    private:
        int code_;
        std::string email_;
        time_t time_;

    public:
        UserOffline(int code, std::string email, time_t time) : code_(code), email_(email), time_(time) {}

        ~UserOffline() = default;

        std::string to_json() const {
            rapidjson::Document d;
            d.SetObject();
            auto &allocator = d.GetAllocator();

            d.AddMember("code", code_, allocator);
            d.AddMember("email", rapidjson::StringRef(email_.c_str()), allocator);
            d.AddMember("time", time_, allocator);

            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

            d.Accept(writer);
            return buffer.GetString();

        }
    };

    class EnterGroup {
    private:
        int code_;
        int status_;
        std::string desc_;
        time_t time_;
    public:
        EnterGroup(int code, int status, std::string desc, time_t time) : code_(code), status_(status),
                                                                          desc_(desc), time_(time) {}

        ~EnterGroup() = default;

        std::string to_json() const {
            rapidjson::Document d;
            d.SetObject();
            auto &allocator = d.GetAllocator();

            d.AddMember("code", code_, allocator);
            d.AddMember("status", status_, allocator);
            d.AddMember("desc", rapidjson::StringRef(desc_.c_str()), allocator);
            d.AddMember("time", time_, allocator);

            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

            d.Accept(writer);
            return buffer.GetString();
        }
    };

    class GroupMsg {
    private:
        int code_;
        std::string msg_;
        std::string email_;
        time_t time_;

    public:
        GroupMsg(int code, std::string msg, std::string email, time_t time) : code_(code),
                                                                              msg_(msg), email_(email), time_(time) {}

        ~GroupMsg() = default;

        std::string to_json() const {
            rapidjson::Document d;
            d.SetObject();
            auto &allocator = d.GetAllocator();

            d.AddMember("code", code_, allocator);
            d.AddMember("msg", rapidjson::StringRef(msg_.c_str()), allocator);
            d.AddMember("email", rapidjson::StringRef(email_.c_str()), allocator);
            d.AddMember("time", time_, allocator);

            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

            d.Accept(writer);
            return buffer.GetString();
        }
    };

    class Member {
    private:
        std::string email_;
        std::string name_;
    public:
        Member(const std::string &email, const std::string &name) : email_(email), name_(name) {}

        const std::string &getEmail() const {
            return email_;
        }

        void setEmail(const std::string &email) {
            email_ = email;
        }

        const std::string &getName() const {
            return name_;
        }

        void setName(const std::string &name) {
            name_ = name;
        }
    };

    class GroupInfo {
    private:

        int code_;
        std::vector<Member> members_;
        time_t time_;

    public:
        GroupInfo(int code, const std::vector<Member> &members, time_t time) : code_(code), members_(members),
                                                                               time_(time) {}

        std::string to_json() const {
            rapidjson::StringBuffer strBuf;
            rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);

            writer.StartObject();

            writer.Key("code");
            writer.Int(code_);

            writer.Key("members");
            writer.StartArray();
            for (const Member &m : members_) {
                writer.StartObject();
                writer.Key("email");
                writer.String(m.getEmail().c_str());
                writer.Key("name");
                writer.String(m.getName().c_str());
                writer.EndObject();
            }
            writer.EndArray();

            writer.Key("time");
            writer.Int(time_);

            writer.EndObject();

            return strBuf.GetString();
        }

    };


}

#endif //CHAT_SERVER_CLION_SERVERTOCLIENTMSG_H
