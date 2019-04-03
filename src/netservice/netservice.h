#ifndef NETSERVICE_H
#define NETSERVICE_H

#include <unordered_map>
#include <list>

#include "netmessage_struct.h"

namespace simpleserver {
    class ServerController;
}

namespace network_imitation {

using trafficStorage = std::unordered_map<int, std::list<NetMessage>> ;
//получить идентификатор сервера (один на всех, известен всем)
constexpr int getServerID() noexcept {return 0;}
//получить уникальный ключ для чат-клиента
int getNewClientUniqID() noexcept;

//Имитирует работу по сети сервера
//(соединение с клиентами, хранение и обмен информации)
//обмен для скорости производится списками сообщений,а не по 1-му
class  NetService {
    //Только chat-сервер может выполнять "эксклюзивные" операции
    friend class simpleserver::ServerController;
public:
    NetService() noexcept = default;
    bool send(int, std::list<NetMessage> &&);
    std::list<NetMessage> receive(int);
    //отправить список абоненту, вместо него получить список от другого абонента
    bool exchange(int, int, std::list<NetMessage> &);
private:
    void multi_send(trafficStorage &&);//разослать списки сообщений нескольким абонентам
    void init(const int);//создать базовое соединение для chat-сервера
    void clear();//очистить все списки (соединения)
};

}
#endif // NETSERVICE_H
