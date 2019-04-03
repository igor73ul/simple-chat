#ifndef ASYNCWORK_H
#define ASYNCWORK_H

#include <thread>
#include <atomic>

namespace network_imitation {
//Обёртка для циклического запуска задачи в отдельном потоке
class AsyncWork {
public:
    AsyncWork(const int) noexcept;
    virtual ~AsyncWork();
    void start();
    void stop();
protected:
    virtual void run() = 0;//Циклическая часть
private:
    //частота запуска циклической части (время для выполнения задачи учитывается)
    const int frequency_;
    //Флаг для проверки - продолжать ли работу (для корректного выхода из цикла)
    std::atomic_bool working_flag_;
    std::thread controller_;
};

}
#endif // ASYNCWORK_H
