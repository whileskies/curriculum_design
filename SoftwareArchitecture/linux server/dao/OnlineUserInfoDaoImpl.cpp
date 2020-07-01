//
// Created by whileskies on 19-6-13.
//

#include "OnlineUserInfoDaoImpl.h"

namespace dao {
    OnlineUserInfoDaoImpl::OnlineUserInfoDaoImpl()
    = default;

    OnlineUserInfoDaoImpl::~OnlineUserInfoDaoImpl()
    = default;

    void OnlineUserInfoDaoImpl::add_new_user(std::string email, std::string name, int groupid) {
        ClientInfo c;
        c.email = email;
        c.name = name;
        c.groupid = groupid;
        map_clients_info[email] = c;
    }

    bool OnlineUserInfoDaoImpl::del_user_by_email(std::string email) {
        auto it = map_clients_info.find(email);
        if (it != map_clients_info.end()) {
            map_clients_info.erase(it);
            return true;
        }

        return false;
    }

    std::vector<std::string> OnlineUserInfoDaoImpl::query_emails_by_groupid(int groupid) {
        std::vector<std::string> emails;

        for (auto &it : map_clients_info) {
            if (it.second.groupid == groupid)
                emails.push_back(it.second.email);
        }

        return emails;
    }

    //查询用户是否已在某个群组中， 不存在返回-1，存在返回groupid
    int OnlineUserInfoDaoImpl::check_email_exists(std::string email) {
        auto it = map_clients_info.find(email);
        if (it == map_clients_info.end()) {
            return -1;
        } else {
            return it->second.groupid;
        }
    }

    //从string 的vector中移除excluded_email字符串
    bool
    OnlineUserInfoDaoImpl::exclude_email_from_vector(std::vector<std::string> &emails, std::string excluded_email) {
        if (emails.empty()) return false;
        bool ex = false;

        for (auto it = emails.begin(); it != emails.end();) {
            if (*it == excluded_email) {
                emails.erase(it);
                ex = true;
            } else {
                *it++;
            }
        }

        return ex;
    }

    bool OnlineUserInfoDaoImpl::query_clientinfo_by_email(std::string email, dao::ClientInfo &client_info) {
        auto it = map_clients_info.find(email);
        if (it != map_clients_info.end()) {
            client_info = map_clients_info[email];
            return true;
        }

        return false;
    }

    void OnlineUserInfoDaoImpl::print_map_clients_info() {
        std::cout << "map_clients_info: ";
        for (auto &it : map_clients_info) {
            std::cout << "{";
            std::cout << it.first << " " << it.second.email << " " << it.second.name << " " << it.second.groupid;
            std::cout << "}, ";
        }
        std::cout << std::endl;
    }

    //按照groupid查询所有在线用户信息
    std::vector<dao::ClientInfo> OnlineUserInfoDaoImpl::query_clientsinfo_by_groupid(int groupid) {
        std::vector<ClientInfo> infos;
        std::vector<std::string> emails = query_emails_by_groupid(groupid);

        infos.reserve(emails.size());
        for (const std::string &email : emails) {
            infos.push_back(map_clients_info[email]);
        }

        return infos;
    }
}