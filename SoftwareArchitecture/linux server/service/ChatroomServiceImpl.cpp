//
// Created by whileskies on 19-6-13.
//

#include "ChatroomServiceImpl.h"

namespace service {
    ChatroomServiceImpl::ChatroomServiceImpl() {
        online_user_info_dao = new dao::OnlineUserInfoDaoImpl();
    }

    ChatroomServiceImpl::~ChatroomServiceImpl() {
        delete online_user_info_dao;
    }

    int ChatroomServiceImpl::data_dispatch(std::string &src_client_email, std::string &src_data,
                                           std::vector<std::string> &dst_clients_email, std::string &dst_data) {
        std::string ori_src_data = src_data;
        std::string ori_src_client_email = src_client_email;

        try {
            util::ClientJsonMsgParser json_parser(ori_src_data);

            if (json_parser.get_code() == CLIENT_TO_SERVER_ONLINE_CODE) {
                online_user_info_dao->print_map_clients_info();
                int groupid = online_user_info_dao->check_email_exists(json_parser.get_email());
                //std::cout << "groupid: " << groupid << std::endl;

                if (groupid == -1) {
                    //用户未加入群组
                    online_user_info_dao->add_new_user(json_parser.get_email(), json_parser.get_name(),
                                                       json_parser.get_groupid());
                    src_client_email = json_parser.get_email();
                    src_data = service::EnterGroup(ADD_GROUP, 1, "succ", time(nullptr)).to_json();


                    std::vector<std::string> emails = online_user_info_dao->query_emails_by_groupid(
                            json_parser.get_groupid());

                    online_user_info_dao->exclude_email_from_vector(emails, src_client_email);

                    dst_clients_email.insert(dst_clients_email.end(), emails.begin(), emails.end());
                    dst_data = service::UserOnline(USER_ONLINE, json_parser.get_email(), json_parser.get_name(),
                                                   time(nullptr)).to_json();

                    return RET_NEW_ONLINE;
                } else {
                    //已加入groupid群组

                    src_data = service::EnterGroup(ADD_GROUP, 0,
                                                   "fail: User owning this email has entered the group : " +
                                                   std::to_string(groupid), time(nullptr)).to_json();

                    return RET_DENY_ENTER_GROUP;
                }

            } else if (json_parser.get_code() == CLIENT_TO_SERVER_SENDMSG_CODE && !ori_src_client_email.empty()) {
                dao::ClientInfo c;
                online_user_info_dao->query_clientinfo_by_email(ori_src_client_email, c);

                std::vector<std::string> emails = online_user_info_dao->query_emails_by_groupid(c.groupid);
                dst_clients_email.insert(dst_clients_email.end(), emails.begin(), emails.end());
                dst_data = service::GroupMsg(GROUP_MSG, json_parser.get_msg(), ori_src_client_email,
                                             time(nullptr)).to_json();

                return RET_GROUP_MSG;
            } else if (json_parser.get_code() == CLIENT_TO_SERVER_OFFLINE_CODE && !ori_src_client_email.empty()) {
                online_user_info_dao->del_user_by_email(ori_src_client_email);
                std::vector<std::string> emails = online_user_info_dao->query_emails_by_groupid(
                        json_parser.get_groupid());

                dst_clients_email.insert(dst_clients_email.begin(), emails.begin(), emails.end());
                dst_data = service::UserOffline(USER_OFFLINE, json_parser.get_email(), time(nullptr)).to_json();

                return RET_USER_OFFLINE;
            } else if (json_parser.get_code() == CLIENT_TO_SERVER_GET_GROUP_INFO && !ori_src_client_email.empty()) {
                int groupid = online_user_info_dao->check_email_exists(json_parser.get_email());
                if (groupid != -1) {
                    std::vector<dao::ClientInfo> infos = online_user_info_dao->query_clientsinfo_by_groupid(groupid);
                    std::vector<service::Member> members;
                    members.reserve(infos.size());
                    for (const dao::ClientInfo &info : infos) {
                        members.emplace_back(info.email, info.name);
                    }

                    src_data = service::GroupInfo(GROUP_MEMBERS_LIST, members, time(nullptr)).to_json();

                    return RET_GROUP_MEMBERS_LIST;
                }

            }


        } catch (util::ParseException &e) {
            std::cout << e.what() << std::endl;
        }


        return -1;

    }

    void ChatroomServiceImpl::offline(std::string &src_client_email, std::vector<std::string> &dst_clients_email,
                                      std::string &dst_data) {

        dao::ClientInfo c;
        online_user_info_dao->query_clientinfo_by_email(src_client_email, c);
        std::vector<std::string> emails = online_user_info_dao->query_emails_by_groupid(c.groupid);
        online_user_info_dao->exclude_email_from_vector(emails, src_client_email);

        dst_clients_email.insert(dst_clients_email.begin(), emails.begin(), emails.end());
        dst_data = service::UserOffline(USER_OFFLINE, src_client_email, time(nullptr)).to_json();

        online_user_info_dao->del_user_by_email(src_client_email);
    }


}