#include "server_path.h"

#include "configreader.h"
#include "servercontroller.h"
namespace  simpleserver {

Server_path::~Server_path() {
    stop();
}
bool Server_path::start() {
    auto updating_time = configfile::ConfigReader().getServerNetFrequency();
    controller_ = new(std::nothrow) ServerController(updating_time);
    if(controller_ != nullptr) {
        controller_->start();
        return true;
    }
    return false;
}

void Server_path::stop() {
    delete controller_;
    controller_ = nullptr;
}

}
