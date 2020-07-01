//
// Created by whileskies on 19-6-13.
//

#ifndef CHAT_SERVER_CLION_CLIENTJSONMSGPARSER_H
#define CHAT_SERVER_CLION_CLIENTJSONMSGPARSER_H

#include <string>
#include "../include/rapidjson/document.h"

namespace util {

    class ParseException : public std::exception {
    public:
        const char *what() const noexcept override {
            return "parse exception";
        }

    };


    class ClientJsonMsgParser {
    private:
        rapidjson::Document d;
        int code_;
        std::string email_;
        std::string name_;
        int groupid_;
        std::string msg_;

    public:
        explicit ClientJsonMsgParser(const std::string &msg) {
            d.Parse(msg.c_str());

            if (d.HasParseError())
                throw ParseException();

            rapidjson::Value &code = d["code"];
            code_ = code.GetInt();

            auto it_email = d.FindMember("email");
            if (it_email != d.MemberEnd()) {
                rapidjson::Value &email = d["email"];
                email_ = email.GetString();
            }

            auto it_name = d.FindMember("name");
            if (it_name != d.MemberEnd()) {
                rapidjson::Value &name = d["name"];
                name_ = name.GetString();
            }

            auto it_groupid = d.FindMember("groupid");
            if (it_groupid != d.MemberEnd()) {
                rapidjson::Value &groupid = d["groupid"];
                groupid_ = groupid.GetInt();
            }

            auto it_msg = d.FindMember("msg");
            if (it_msg != d.MemberEnd()) {
                rapidjson::Value &msg = d["msg"];
                msg_ = msg.GetString();
            }

        }

        ~ClientJsonMsgParser()
        = default;

        int get_code() const {
            return code_;
        }

        std::string get_email() const {
            return email_;
        }

        std::string get_name() const {
            return name_;
        }

        int get_groupid() const {
            return groupid_;
        }

        std::string get_msg() const {
            return msg_;
        }
    };


}

#endif //CHAT_SERVER_CLION_CLIENTJSONMSGPARSER_H
