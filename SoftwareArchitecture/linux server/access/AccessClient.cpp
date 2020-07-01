//
// Created by whileskies on 19-6-13.
//

#include "AccessClient.h"

namespace access {
    //根据端口初始化event管理器event_base_与监听事件listener_
    AccessClient::AccessClient(const int port, const int max_data_len) : port_(port),
                                                                         max_data_len_(max_data_len) {
        struct sockaddr_in sin = accept_all_sock_addr();
        event_base_ = event_base_new();

        listener_ = evconnlistener_new_bind(event_base_, accept_conn_cb, this,
                                            LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE, -1,
                                            reinterpret_cast<struct sockaddr *>(&sin), sizeof(sin));
        int sockfd = evconnlistener_get_fd(listener_);

        int keepAlive = 1; // 开启keepalive属性
        int keepIdle = 30; // 如该连接在30秒内没有任何数据往来,则进行探测
        int keepInterval = 5; // 探测时发包的时间间隔为5 秒
        int keepCount = 3; // 探测尝试的次数.如果第1次探测包就收到响应了,则后2次的不再发.

        setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, (void *)&keepAlive, sizeof(keepAlive));
        setsockopt(sockfd, SOL_TCP, TCP_KEEPIDLE, (void*)&keepIdle, sizeof(keepIdle));
        setsockopt(sockfd, SOL_TCP, TCP_KEEPINTVL, (void *)&keepInterval, sizeof(keepInterval));
        setsockopt(sockfd, SOL_TCP, TCP_KEEPCNT, (void *)&keepCount, sizeof(keepCount));

        evconnlistener_set_error_cb(listener_, accept_error_cb);

        i_chatroom_service = new service::ChatroomServiceImpl();
    }

    AccessClient::~AccessClient() {
        stop();
        delete i_chatroom_service;
    }

    struct sockaddr_in AccessClient::accept_all_sock_addr() const {
        struct sockaddr_in sin{};
        bzero(&sin, sizeof(sin));
        sin.sin_family = AF_INET;
        sin.sin_addr.s_addr = htonl(INADDR_ANY);
        sin.sin_port = htons(port_);

        return sin;
    }

    void AccessClient::accept_error_cb(struct evconnlistener *listener, void *ctx) {
        struct event_base *base = evconnlistener_get_base(listener);
        int err = EVUTIL_SOCKET_ERROR();
        std::cerr << "Got an error " << err << " (" << evutil_socket_error_to_string(err)
                  << ") on the listener. Shutting down." << std::endl;
        event_base_loopexit(base, nullptr);
    }

    //当有新客户端到来时调用此回调函数
    void AccessClient::accept_conn_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *addr,
                                      int socklen, void *ctx) {
        //ctx 为 传递的当前对象指针
        auto *this_access_client = (AccessClient *) ctx;
        std::cout << "new client  ";

        struct bufferevent *bf = bufferevent_socket_new(this_access_client->event_base_, fd, BEV_OPT_CLOSE_ON_FREE);

        auto *client_access_info = new ClientAccessInfo(fd, *(struct sockaddr_in *) addr, bf);

        client_access_info->print();

        this_access_client->clients_map_by_sockfd[fd] = client_access_info;

        bufferevent_setcb(bf, read_cb, nullptr, event_cb, this_access_client);
        bufferevent_enable(bf, EV_READ | EV_WRITE);
    }

    //当客户端写入消息时回调
    void AccessClient::read_cb(struct bufferevent *bev, void *ctx) {
        //获取this对象
        auto *this_access_client = (AccessClient *) ctx;

        //获取输入、输出缓冲区
        auto *input = bufferevent_get_input(bev);
        auto *output = bufferevent_get_output(bev);

        //读取输入，交给service层处理
        char *line;
        size_t n;

        int fd = bufferevent_getfd(bev);
        ClientAccessInfo *client_access_info = this_access_client->clients_map_by_sockfd[fd];


        while ((line = evbuffer_readln(input, &n, EVBUFFER_EOL_ANY))) {
            std::cout << "recv: " << line << std::endl;
            //交给服务层处理，根据服务层返回状态
            std::string src_email;
            if (!client_access_info->get_email().empty())
                src_email = client_access_info->get_email();
            std::string src_data = std::string(line);
            std::vector<std::string> dst_emails;
            std::string dst_data;
            int code = this_access_client->i_chatroom_service->data_dispatch(src_email, src_data,
                                                                             dst_emails, dst_data);

            switch (code) {
                case service::IChatroomService::RET_NEW_ONLINE:
                    this_access_client->user_online_op(client_access_info, src_email, src_data, dst_emails, dst_data);
                    break;

                case service::IChatroomService::RET_DENY_ENTER_GROUP:
                    this_access_client->deny_enter_op(client_access_info, src_email, src_data, dst_emails, dst_data);
                    break;

                case service::IChatroomService::RET_GROUP_MSG:
                    this_access_client->group_msg_op(client_access_info, src_email, src_data, dst_emails, dst_data);
                    break;

                case service::IChatroomService::RET_USER_OFFLINE:
                    this_access_client->user_offline_op(client_access_info, src_email, src_data, dst_emails, dst_data);
                    break;

                case service::IChatroomService::RET_GROUP_MEMBERS_LIST:
                    this_access_client->group_members_list_op(client_access_info, src_email, src_data, dst_emails,
                                                              dst_data);
                    break;
                default:
                    break;
            }

        }
    }

    //当向客户端写入完消息后（缓冲区为空）回调
    void AccessClient::write_cb(struct bufferevent *bev, void *ctx) {

    }

    //缓冲区事件回调
    void AccessClient::event_cb(struct bufferevent *bev, short events, void *ctx) {
        //获取this对象
        auto *this_access_client = (AccessClient *) ctx;
        ClientAccessInfo *client_access_info = this_access_client->clients_map_by_sockfd[fd];
        int fd = bufferevent_getfd(bev);

        if (events & BEV_EVENT_ERROR) {
            int err = EVUTIL_SOCKET_ERROR();
            std::cerr <<  client_access_info->get_email() << " Got an error from bufferevent: "
                      << evutil_socket_error_to_string(err) << std::endl;
        }

        if (events & BEV_EVENT_EOF) {
            std::cout << "client " << client_access_info->get_email() << " " << " disconnected..." << std::endl;
        }

        if (events & (BEV_EVENT_ERROR | BEV_EVENT_EOF)) {
            std::string src_email = client_access_info->get_email();
            std::string src_data;
            std::vector<std::string> dst_emails;
            std::string dst_data;

            if (!src_email.empty()) {
                this_access_client->i_chatroom_service->offline(src_email, dst_emails, dst_data);

                this_access_client->user_offline_op(client_access_info, src_email, src_data, dst_emails, dst_data);
            }
        }

    }

    //用户进入群聊组操作
    void AccessClient::user_online_op(ClientAccessInfo *client_access_info, const std::string &src_email,
                                      const std::string &src_data,
                                      const std::vector<std::string> &dst_emails, const std::string &dst_data) {
        map_sockfd_user(client_access_info->get_sockfd(), src_email);
        send_msg_by_email(src_email, src_data);
        broadcast_msg_by_emails(dst_emails, dst_data);
    }

    //群聊消息操作
    void AccessClient::group_msg_op(ClientAccessInfo *client_access_info, const std::string &src_email,
                                    const std::string &src_data,
                                    const std::vector<std::string> &dst_emails, const std::string &dst_data) {
        broadcast_msg_by_emails(dst_emails, dst_data);
    }

    //进入群聊失败操作
    void AccessClient::deny_enter_op(ClientAccessInfo *client_access_info, const std::string &src_email,
                                     const std::string &src_data,
                                     const std::vector<std::string> &dst_emails, const std::string &dst_data) {
        auto *output = bufferevent_get_output(client_access_info->get_bufferevent());
        evbuffer_add_printf(output, "%s\n", src_data.c_str());
    }

    //用户退出群聊操作
    void AccessClient::user_offline_op(ClientAccessInfo *client_access_info, const std::string &src_email,
                                       const std::string &src_data,
                                       const std::vector<std::string> &dst_emails, const std::string &dst_data) {
        remove_access_info_by_email(src_email);
        broadcast_msg_by_emails(dst_emails, dst_data);
    }

    //获取成员列表操作
    void AccessClient::group_members_list_op(ClientAccessInfo *client_access_info, const std::string &src_email,
                                             const std::string &src_data, const std::vector<std::string> &dst_emails,
                                             const std::string &dst_data) {
        send_msg_by_email(src_email, src_data);
    }

    //建立本层socket描述符与用户email的映射
    void AccessClient::map_sockfd_user(evutil_socket_t fd, const std::string &email) {
        ClientAccessInfo *c = clients_map_by_sockfd[fd];
        c->set_email(email);

        clients_map_by_email[email] = c;
    }

    //清除用户连接信息
    void AccessClient::remove_access_info_by_email(const std::string &email) {
        auto it = clients_map_by_email.find(email);

        ClientAccessInfo *c = it->second;
        evutil_socket_t sockfd = c->get_sockfd();
        clients_map_by_email.erase(it);

        auto it2 = clients_map_by_sockfd.find(sockfd);
        clients_map_by_sockfd.erase(it2);

        delete c;
    }

    //根据邮箱发送消息
    void AccessClient::send_msg_by_email(const std::string &email, const std::string &data) {
        ClientAccessInfo *c = clients_map_by_email[email];
        auto *output = bufferevent_get_output(c->get_bufferevent());
        evbuffer_add_printf(output, "%s\n", data.c_str());
    }

    //根据邮箱列表广播消息
    void AccessClient::broadcast_msg_by_emails(const std::vector<std::string> &emails, const std::string &data) {
        for (const std::string &email : emails) {
            send_msg_by_email(email, data);
        }
    }

    //向sockfd为fd的客户端发送data
    void AccessClient::send_data(evutil_socket_t fd, const std::string &data) {
        ClientAccessInfo *c = clients_map_by_sockfd[fd];
        auto *output = bufferevent_get_output(c->get_bufferevent());
        evbuffer_add_printf(output, "%s\n", data.c_str());
    }


    //启动事件循环，处理客户端连接
    void AccessClient::start() const {
        event_base_dispatch(event_base_);
    }

    //终止事件循环，清理资源
    void AccessClient::stop() const {
        for (auto it : clients_map_by_sockfd)
            delete it.second;

        if (listener_ != nullptr)
            evconnlistener_free(listener_);
        if (event_base_ != nullptr)
            event_base_free(event_base_);
    }


}

