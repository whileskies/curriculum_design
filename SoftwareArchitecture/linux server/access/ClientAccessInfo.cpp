//
// Created by whileskies on 19-6-13.
//

#include "ClientAccessInfo.h"

namespace access {
    ClientAccessInfo::ClientAccessInfo() {}

    ClientAccessInfo::ClientAccessInfo(evutil_socket_t sockfd, struct sockaddr_in addr,
                                       struct bufferevent *client_bufferevent) :
            sockfd_(sockfd), addr_(addr), client_bufferevent_(client_bufferevent) {
    }

    ClientAccessInfo::~ClientAccessInfo() {
        bufferevent_free(client_bufferevent_);
    }

    struct sockaddr_in ClientAccessInfo::get_addr() const {
        return addr_;
    }

    void ClientAccessInfo::print() const {
        char buf[100];
        inet_ntop(AF_INET, &addr_.sin_addr, buf, 16);
        std::cout << "addr: " << buf << " port:" << ntohs(addr_.sin_port) << std::endl;
    }

    void ClientAccessInfo::set_email(std::string email) {
        email_ = email;
    }

    std::string ClientAccessInfo::get_email() const {
        return email_;
    }

    evutil_socket_t ClientAccessInfo::get_sockfd() const {
        return sockfd_;
    }

    struct bufferevent *ClientAccessInfo::get_bufferevent() const {
        return client_bufferevent_;
    }

}