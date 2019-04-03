#include "servercontroller.h"

namespace  simpleserver {

ServerController::ServerController(const int freq):AsyncWork(freq) {
    net_controller_.init(service_.getServerID());
}

ServerController::~ServerController() {
    stop();
    net_controller_.clear();
}

bool ServerController::readTraffic() {
    auto inputTraffic(net_controller_.receive(service_.getServerID()));
    for(auto msg: inputTraffic) {
        liveclient_controler_.update(msg.sender_id);
        service_.processing(msg);
    }
    return !inputTraffic.empty();
}

bool ServerController::delLostContact() {
    auto delUsers = liveclient_controler_.eraselist();
    for(auto user : delUsers) {
        service_.delUser(user);
    }
    return delUsers.empty();
}

void ServerController::run() {
    readTraffic();
    //рассылаем alive сообщение, если не было событий о удалении(для экономии)
    if(delLostContact())
        service_.reSendAliveMsg_if_req();
    net_controller_.multi_send(service_.takeData());

}

}
