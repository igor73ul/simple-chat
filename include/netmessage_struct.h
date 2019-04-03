#ifndef NETMESSAGE_STRUCT_H
#define NETMESSAGE_STRUCT_H

#include <string>
namespace network_imitation {

//Сетевое сообщение
//(при необходимости легко реализовать сериализацию/десериализацию)
struct NetMessage {
    enum class CommandCode {
        kAddUser = 0,//!new user connected
        kDelUser,//!user disconnected
        kAlliveMsg,//!steel connected
        kTextMsg//!user send text message
    };
    int sender_id;
    CommandCode command_id;
    std::string text;
    NetMessage(const int & i, const CommandCode & c, const std::string &t):sender_id(i), command_id(c), text(t){}
};

}
#endif //NETMESSAGE_STRUCT_H
