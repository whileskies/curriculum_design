#include <iostream>

#include <map>
#include <string>

#include "access/AccessClient.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/document.h"
#include "util/SysConfig.h"
#include "dao/ClientInfo.h"

std::map<std::string, dao::ClientInfo> map_clients_info;


int main() {
    util::SysConfig config("config.json");


    access::AccessClient access_client(config.get_port(), config.get_max_data_len());

    access_client.start();


    return 0;
}