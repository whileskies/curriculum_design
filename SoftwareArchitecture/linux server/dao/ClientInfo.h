//
// Created by whileskies on 19-6-13.
//

#ifndef CHAT_SERVER_CLION_CLIENTINFO_H
#define CHAT_SERVER_CLION_CLIENTINFO_H

#include <string>

namespace dao {
    struct ClientInfo {
        std::string email;
        std::string name;
        int groupid;
    };
}

#endif //CHAT_SERVER_CLION_CLIENTINFO_H
