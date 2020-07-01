//
// Created by whileskies on 19-6-13.
//

#ifndef CHAT_SERVER_CLION_CHATROOMSERVICEIMPL_H
#define CHAT_SERVER_CLION_CHATROOMSERVICEIMPL_H


#include "IChatroomService.h"
#include "../util/ClientJsonMsgParser.h"
#include "../dao/OnlineUserInfoDaoImpl.h"
#include "ServerToClientMsg.h"

namespace service {
    class ChatroomServiceImpl : public IChatroomService {
    private:

    public:
        ChatroomServiceImpl();

        ~ChatroomServiceImpl() override;

        int data_dispatch(std::string &src_client_email, std::string &src_data,
                          std::vector<std::string> &dst_clients_email, std::string &dst_data) override;

        void offline(std::string &src_client_email,
                     std::vector<std::string> &dst_clients_email, std::string &dst_data) override;
    };

}


#endif //CHAT_SERVER_CLION_CHATROOMSERVICEIMPL_H
