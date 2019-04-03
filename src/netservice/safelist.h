#ifndef SAFELIST_H
#define SAFELIST_H

#include <list>
#include <mutex>

#include "netmessage_struct.h"

namespace network_imitation {

using Guard = std::lock_guard<std::mutex>;

//Список сообщений NetMessage с доступом через mutex
class SafeList {
    std::list<NetMessage> mainData_;
    std::mutex locker_;
public:
    SafeList() = default;
    //TODO перед уничтожением, многопоточную работу надо прерывать (следим на стороне владельца экземпляра)
    ~SafeList() = default;
    inline void push_back(std::list<NetMessage> &&);
    inline void push_back(NetMessage &&);
    inline void swap(std::list<NetMessage> &);//обменяться содержимым
};

void SafeList::push_back(std::list<NetMessage> &&data) {
    Guard myGuard(locker_);
    mainData_.splice(mainData_.end(), std::move(data));
}

void SafeList::push_back(NetMessage &&data) {
    Guard myGuard(locker_);
    mainData_.push_back(std::move(data));
}

void SafeList::swap(std::list<NetMessage> &data) {
    Guard myGuard(locker_);
    data.swap(mainData_);
}

}
#endif // SAFELIST_H
