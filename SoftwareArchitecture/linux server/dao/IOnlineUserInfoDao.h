//
// Created by whileskies on 19-6-13.
//

#ifndef CHAT_SERVER_CLION_IONLINEUSERINFODAO_H
#define CHAT_SERVER_CLION_IONLINEUSERINFODAO_H

#include <string>
#include <vector>
#include <iostream>

#include "ClientInfo.h"

namespace dao {
    class IOnlineUserInfoDao {
    private:

    public:

        virtual void add_new_user(std::string email, std::string name, int groupid) = 0;

        virtual bool del_user_by_email(std::string email) = 0;

        virtual std::vector<std::string> query_emails_by_groupid(int groupid) = 0;

        virtual int check_email_exists(std::string email) = 0;

        virtual bool exclude_email_from_vector(std::vector<std::string> &emails, std::string excluded_email) = 0;

        virtual bool query_clientinfo_by_email(std::string email, dao::ClientInfo &client_info) = 0;

        virtual std::vector<dao::ClientInfo> query_clientsinfo_by_groupid(int groupid) = 0;

        virtual void print_map_clients_info() = 0;

        virtual ~IOnlineUserInfoDao() = default;

    };
}

#endif //CHAT_SERVER_CLION_IONLINEUSERINFODAO_H
