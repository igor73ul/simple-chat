#ifndef SERVER_PATH_H
#define SERVER_PATH_H

namespace  simpleserver {

class ServerController;
//обёртка для управления сервером;
class Server_path {
    //Скрываем подробности от пользователя библиотеки
    ServerController * controller_ = nullptr;
public:
    Server_path() noexcept = default;
    ~Server_path();
    bool start();
    void stop();
};

}
#endif // SERVER_PATH_H
