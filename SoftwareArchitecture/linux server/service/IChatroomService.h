//
// Created by whileskies on 19-6-13.
//

#ifndef CHAT_SERVER_CLION_ICHATROOMSERVICE_H
#define CHAT_SERVER_CLION_ICHATROOMSERVICE_H


#include <string>
#include <vector>
#include <iostream>
#include "../dao/IOnlineUserInfoDao.h"

namespace service {
    class IChatroomService {
    public:
        virtual ~IChatroomService() = default;

    protected:
        dao::IOnlineUserInfoDao *online_user_info_dao{};

    public:
        const static int NO_RETURN_DATA = 0;
        const static int USER_ONLINE = 100;
        const static int USER_OFFLINE = 101;
        const static int GROUP_MSG = 102;
        const static int GROUP_MEMBERS_LIST = 103;
        const static int ADD_GROUP = 104;

        const static int CLIENT_TO_SERVER_ONLINE_CODE = 0;
        const static int CLIENT_TO_SERVER_OFFLINE_CODE = 1;
        const static int CLIENT_TO_SERVER_SENDMSG_CODE = 2;
        const static int CLIENT_TO_SERVER_GET_GROUP_INFO = 3;

        const static int RET_NEW_ONLINE = 0;
        const static int RET_DENY_ENTER_GROUP = 1;
        const static int RET_GROUP_MSG = 2;
        const static int RET_USER_OFFLINE = 3;
        const static int RET_GROUP_MEMBERS_LIST = 4;


        virtual int data_dispatch(std::string &src_client_email, std::string &src_data,
                                  std::vector<std::string> &dst_clients_email, std::string &dst_data) = 0;

        virtual void offline(std::string &src_client_email,
                             std::vector<std::string> &dst_clients_email, std::string &dst_data) = 0;

    };
}


#endif //CHAT_SERVER_CLION_ICHATROOMSERVICE_H
