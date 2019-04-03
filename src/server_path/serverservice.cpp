#include "serverservice.h"

#include <algorithm>

namespace  simpleserver {

using namespace network_imitation;

trafficStorage ServerService::takeData() {
    trafficStorage result;
    for(auto & oneUser : user_list_)
    {
        result.emplace(oneUser.first, std::move(oneUser.second.messagelist));
        oneUser.second.messagelist.clear();
    }
    return result;
}

void ServerService::addUser(const std::string &user, const int userID) {
    auto finalUserName(user);
    //Проверяем используется ли имя, которое просит клиент для себя
    if(user_list_.end() != std::find_if(user_list_.begin(), user_list_.end(),
                                      [finalUserName](std::pair<int, UserParam> val) {
        if(val.second.username == finalUserName)
            return true;
        return false;
    }))
        finalUserName = user + '-' + std::to_string(userID);
    //отправляем новому абоненту его имя
    std::list<NetMessage> currentClients = {NetMessage(kServerID_, NetMessage::CommandCode::kAddUser, finalUserName)};
    for(auto & oneUser : user_list_) {
        //Рассылаем участникам нового абонента
        oneUser.second.messagelist.emplace_back(kServerID_, NetMessage::CommandCode::kAddUser, finalUserName);
        //формируем список участников новомоу абоненту
        currentClients.emplace_back(kServerID_, NetMessage::CommandCode::kAddUser, oneUser.second.username);
    }
    user_list_[userID] = {finalUserName, currentClients};
}

void ServerService::reSendText(const std::string &text, const int userID) {
    auto userNameIter = user_list_.find(userID);
    if(userNameIter == user_list_.end())
        return;
    for(auto & oneUser : user_list_) {
        if(oneUser.first == userID)
            oneUser.second.messagelist.emplace_back(kServerID_, NetMessage::CommandCode::kTextMsg,
                                                    "<b>(Me):</b> " +  text);
        else
            oneUser.second.messagelist.emplace_back(kServerID_, NetMessage::CommandCode::kTextMsg,
                                                    "<b>" + userNameIter->second.username + ":</b> " +  text);
    }
}

void ServerService::delUser(const int userID) {
    auto delUserNameIter = user_list_.find(userID);
    if(delUserNameIter == user_list_.end())
        return;
    std::string delUserName = delUserNameIter->second.username;
    user_list_.erase(delUserNameIter);
    for(auto & oneUser : user_list_)
        oneUser.second.messagelist.emplace_back(kServerID_, NetMessage::CommandCode::kDelUser, delUserName);
}

void ServerService::reSendAliveMsg_if_req() {
    if(user_list_.empty() || !user_list_.begin()->second.messagelist.empty())
        return;
    for(auto & oneUser : user_list_)
        oneUser.second.messagelist.emplace_back(kServerID_, NetMessage::CommandCode::kAlliveMsg,  std::string());
}

void ServerService::processing(const NetMessage & msg) {
    switch(msg.command_id) {
        case NetMessage::CommandCode::kAlliveMsg: {
            break;
        }
        case NetMessage::CommandCode::kTextMsg: {
            reSendText(msg.text, msg.sender_id);
            break;
        }
        case NetMessage::CommandCode::kAddUser: {
            addUser(msg.text, msg.sender_id);
            break;
        }
        case NetMessage::CommandCode::kDelUser: {
            delUser(msg.sender_id);
        }break;
        default: {
            break;
        }
    }
}

}
