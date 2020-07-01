cmake_minimum_required(VERSION 3.14)
project(chat_server_clion)

set(CMAKE_CXX_STANDARD 14)

link_libraries(/usr/local/lib/libevent.so)

add_executable(chat_server_clion main.cpp access/AccessClient.cpp access/AccessClient.h access/ClientAccessInfo.cpp access/ClientAccessInfo.h service/IChatroomService.h service/ServerToClientMsg.h service/ChatroomServiceImpl.cpp service/ChatroomServiceImpl.h dao/ClientInfo.h dao/IOnlineUserInfoDao.h dao/OnlineUserInfoDaoImpl.cpp dao/OnlineUserInfoDaoImpl.h util/ClientJsonMsgParser.h util/SysConfig.h)