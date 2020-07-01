//
// Created by whileskies on 19-6-13.
//

#ifndef CHAT_SERVER_CLION_SYSCONFIG_H
#define CHAT_SERVER_CLION_SYSCONFIG_H

#include <fstream>
#include <string>
#include <exception>
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/istreamwrapper.h"


namespace util {
    using namespace std;

    class SysConfig {
    private:
        int port = -1;
        int maxdatalen = -1;

    public:
        explicit SysConfig(const string &filename) {
            ifstream ifs(filename);

            rapidjson::IStreamWrapper isw(ifs);

            rapidjson::Document d;
            d.ParseStream(isw);

            if (!d.HasParseError()) {
                port = d["port"].GetInt();
                maxdatalen = d["maxdatalen"].GetInt();
            }

        }

        ~SysConfig()
        = default;

        int get_port() const {
            return port;
        }

        int get_max_data_len() const {
            return maxdatalen;
        }

    };


}

#endif //CHAT_SERVER_CLION_SYSCONFIG_H
