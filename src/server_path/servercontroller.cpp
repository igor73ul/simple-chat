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
    for(auto msg: inputTraffic)
        service_.processing(msg);
    return !inputTraffic.empty();
}

void ServerController::run() {
    readTraffic();
    //рассылаем alive сообщение, если необходимо
    service_.reSendAliveMsg_if_req();
    net_controller_.multi_send(service_.takeData());
}

}
