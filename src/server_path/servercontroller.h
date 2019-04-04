#ifndef SERVERCONTROLLER_H
#define SERVERCONTROLLER_H

#include "netservice.h"
#include "alivematrix.h"
#include "serverservice.h"
#include "asyncwork.h"

namespace  simpleserver {
//Управляет работой сервера
class ServerController: public network_imitation::AsyncWork {
public:
    ServerController(const int);
    ~ServerController();
    ServerController(ServerController&& ) = default;
    ServerController& operator=(ServerController&& ) = default;
    void run();//один "такт" работы сервера
private:
    bool readTraffic();//забираем все сообщения для сервера и обрабатываем их
    //Сервисная часть - разбор и накопление информации(выделена в отдельный класс для удобства)
    ServerService service_;
    network_imitation::NetService net_controller_;
};

}
#endif // SERVERCONTROLLER_H
