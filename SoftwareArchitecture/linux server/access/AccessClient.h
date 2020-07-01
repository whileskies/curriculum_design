//
// Created by whileskies on 19-6-13.
//

#ifndef CHAT_SERVER_CLION_ACCESSCLIENT_H
#define CHAT_SERVER_CLION_ACCESSCLIENT_H


#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>

#include <iostream>
#include <map>
#include <arpa/inet.h>
#include <string>
#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>

#include "ClientAccessInfo.h"
#include "../util/SysConfig.h"
#include "../service/IChatroomService.h"
#include "../service/ChatroomServiceImpl.h"

namespace access {
    //客户端连接类，负责与各客户端的连接、IO
    class AccessClient {
    private:
        const int port_;
        const int max_data_len_;
        struct event_base *event_base_ = nullptr;
        struct evconnlistener *listener_ = nullptr;
        std::map<int, ClientAccessInfo *> clients_map_by_sockfd;
        std::map<std::string, ClientAccessInfo *> clients_map_by_email;
        service::IChatroomService *i_chatroom_service;

        struct sockaddr_in accept_all_sock_addr() const;

        static void accept_error_cb(struct evconnlistener *listener, void *ctx);

        static void
        accept_conn_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *addr, int socklen,
                       void *ctx);

        static void read_cb(struct bufferevent *bev, void *ctx);

        static void write_cb(struct bufferevent *bev, void *ctx);

        static void event_cb(struct bufferevent *bev, short events, void *ctx);

        void
        user_online_op(ClientAccessInfo *client_access_info, const std::string &src_email, const std::string &src_data,
                       const std::vector<std::string> &dst_emails, const std::string &dst_data);

        void
        group_msg_op(ClientAccessInfo *client_access_info, const std::string &src_email, const std::string &src_data,
                     const std::vector<std::string> &dst_emails, const std::string &dst_data);

        void
        deny_enter_op(ClientAccessInfo *client_access_info, const std::string &src_email, const std::string &src_data,
                      const std::vector<std::string> &dst_emails, const std::string &dst_data);

        void
        user_offline_op(ClientAccessInfo *client_access_info, const std::string &src_email, const std::string &src_data,
                        const std::vector<std::string> &dst_emails, const std::string &dst_data);

        void group_members_list_op(ClientAccessInfo *client_access_info, const std::string &src_email,
                                   const std::string &src_data,
                                   const std::vector<std::string> &dst_emails, const std::string &dst_data);

        void map_sockfd_user(evutil_socket_t fd, const std::string &email);

        void send_msg_by_email(const std::string &email, const std::string &data);

        void broadcast_msg_by_emails(const std::vector<std::string> &emails, const std::string &data);

        void send_data(evutil_socket_t fd, const std::string &data);

        void remove_access_info_by_email(const std::string &email);


    public:
        AccessClient(int port, int max_data_len);

        ~AccessClient();

        void start() const;

        void stop() const;
    };
}


#endif //CHAT_SERVER_CLION_ACCESSCLIENT_H
