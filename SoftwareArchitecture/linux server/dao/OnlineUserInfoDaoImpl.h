//
// Created by whileskies on 19-6-13.
//

#ifndef CHAT_SERVER_CLION_ONLINEUSERINFODAOIMPL_H
#define CHAT_SERVER_CLION_ONLINEUSERINFODAOIMPL_H


#include <map>
#include <string>
#include "IOnlineUserInfoDao.h"
#include "ClientInfo.h"

extern std::map<std::string, dao::ClientInfo> map_clients_info;

namespace dao {
    class OnlineUserInfoDaoImpl : public IOnlineUserInfoDao {
    private:

    public:
        OnlineUserInfoDaoImpl();

        ~OnlineUserInfoDaoImpl() override;

        void add_new_user(std::string email, std::string name, int groupid) override;

        bool del_user_by_email(std::string email) override;

        std::vector<std::string> query_emails_by_groupid(int groupid) override;

        bool query_clientinfo_by_email(std::string email, dao::ClientInfo &client_info) override;

        int check_email_exists(std::string email) override;

        bool exclude_email_from_vector(std::vector<std::string> &emails, std::string excluded_email) override;

        void print_map_clients_info() override;

        std::vector<dao::ClientInfo> query_clientsinfo_by_groupid(int groupid) override;
    };


}

#endif //CHAT_SERVER_CLION_ONLINEUSERINFODAOIMPL_H
