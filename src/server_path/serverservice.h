#ifndef SERVERSERVICE_H
#define SERVERSERVICE_H

#include "alivematrix.h"
#include "netservice.h"
#include "netmessage_struct.h"

namespace  simpleserver {
//Сервисная часть сервера (обработка сообщений и т.п., не знает логики),
//собирает информацию внутри, формирует список сообщений для отправки
class ServerService {
public:
    ServerService() = default;
    virtual ~ServerService() = default;
    ServerService(ServerService&& ) = default;
    ServerService& operator=(ServerService&& ) = default;
    int getServerID() const noexcept {return kServerID_;}
    void addUser(const std::string & , const int);
    void delUser(const int);
    void reSendText(const std::string & , const int);//Переслать всем пользователям
    void reSendAliveMsg_if_req();//Проверить и по необходимости отправить alive сообщение
    void processing(const network_imitation::NetMessage &);
    //забрать списоск сообщений на отправку (очистив внутренне хранилище)
    network_imitation::trafficStorage takeData();
private:
    //информация о клиенте сервера
    struct UserParam {
        std::string username;
        std::list<network_imitation::NetMessage> messagelist;
    };
    const int kServerID_ = network_imitation::getServerID();
    std::unordered_map<int, UserParam> user_list_;
    AliveMatrix liveclient_controler_;
};

}
#endif // SERVERSERVICE_H
