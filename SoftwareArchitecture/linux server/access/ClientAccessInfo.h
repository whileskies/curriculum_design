//
// Created by whileskies on 19-6-13.
//

#ifndef CHAT_SERVER_CLION_CLIENTACCESSINFO_H
#define CHAT_SERVER_CLION_CLIENTACCESSINFO_H


#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/util.h>

#include <arpa/inet.h>
#include <iostream>
#include <string>


namespace access {
    class ClientAccessInfo {
    private:
        evutil_socket_t sockfd_{};
        struct sockaddr_in addr_{};
        struct bufferevent *client_bufferevent_{};
        std::string email_ = "";

    public:
        ClientAccessInfo();

        ClientAccessInfo(evutil_socket_t sockfd, struct sockaddr_in addr, struct bufferevent *client_bufferevent);

        ~ClientAccessInfo();

        struct sockaddr_in get_addr() const;

        void set_email(std::string email);

        std::string get_email() const;

        evutil_socket_t get_sockfd() const;

        struct bufferevent *get_bufferevent() const;

        void print() const;
    };

}


#endif //CHAT_SERVER_CLION_CLIENTACCESSINFO_H
