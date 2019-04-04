#include "netservice.h"

#include <mutex>
#include <utility>

namespace network_imitation {

namespace storage {

template <class T>
T* make_static_obj() {
    auto ptr = new(std::nothrow) T;
    if(ptr == nullptr)
        std::exit(-1);//дальнейшая работа не имеет смысла
    return ptr;

}
//потокобезопасный доступ к хранилищу по принципу std::lock_guard, но с перемещением
class BlockedInformation {
public:
    BlockedInformation(std::mutex* m, trafficStorage* t):
        locker_(m), traffic_(*t) {
        locker_->lock();
    }
    ~BlockedInformation() {
        if(locker_ != nullptr)
            locker_->unlock();
    }
    BlockedInformation(BlockedInformation && data):
        traffic_(data.traffic_), locker_(data.locker_) {
        data.locker_ = nullptr;
    }
    trafficStorage & traffic_;
private:
    std::mutex* locker_;
};

BlockedInformation getAccesToStorage() {
    //TODO создание объектов без удаления, хотя они и нужны на всё время работы приложения
    //стоит сделать глобальными и зарегистрировать функцию для очистки через std::atexit
    static std::mutex * commonMutex  = make_static_obj<std::mutex>();
    static trafficStorage * commonTraffic = make_static_obj<trafficStorage>();
    return std::move(BlockedInformation(commonMutex, commonTraffic));
}

}

int getNewClientUniqID() noexcept {
    static int kUniqeID = getServerID();//уникальные идентификаторы для подключений
    ++kUniqeID;
    //предположим что не сможем израсходовать такое количество,
    //иначе придётся делать пул ID-шников и следить какие освобождаются/занимаются
    return kUniqeID;
}

bool NetService::send(int keySend, std::list<NetMessage> &&data) {
    auto commonTraffic = storage::getAccesToStorage();
    auto iter = commonTraffic.traffic_.find(keySend);
    if(iter != commonTraffic.traffic_.end())
        iter->second.splice(iter->second.end(), std::move(data));
    else
        return false;
    return true;
}

void NetService::multi_send(trafficStorage &&syncData) {
    auto commonTraffic = storage::getAccesToStorage();
    for(auto & oneUser : syncData) {
        auto & userTraffic = commonTraffic.traffic_[oneUser.first];
        userTraffic.splice(userTraffic.end(), oneUser.second);
    }
}

std::list<NetMessage> NetService::receive(int keyRec) {
    auto commonTraffic = storage::getAccesToStorage();
    auto iter = commonTraffic.traffic_.find(keyRec);
    if(iter == commonTraffic.traffic_.end())
        return std::list<NetMessage>();
    std::list<NetMessage> data(iter->second);
    iter->second.clear();
    return std::move(data);
}

bool NetService::exchange(int keySend, int keyRec, std::list<NetMessage> &data) {
    bool flag(false);
    auto commonTraffic = storage::getAccesToStorage();
    auto iterSend = commonTraffic.traffic_.find(keySend);
    if(iterSend != commonTraffic.traffic_.end()) {
        flag = true;
        iterSend->second.splice(iterSend->second.end(), data);
    }
    auto iterRec = commonTraffic.traffic_.find(keyRec);
    if(iterRec != commonTraffic.traffic_.end())
        data.swap(iterRec->second);
    return flag;
}

void NetService::init(const int id) {
    storage::getAccesToStorage().traffic_[id] = {};
}
void NetService::clear() {
    storage::getAccesToStorage().traffic_.clear();
}

}
