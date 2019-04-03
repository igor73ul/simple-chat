#include "asyncwork.h"

namespace network_imitation {

AsyncWork::AsyncWork(const int freq) noexcept : frequency_(freq) {}

AsyncWork::~AsyncWork() {
    stop();
}

void AsyncWork::start() {
    working_flag_ = true;
    controller_ = std::thread([&]() {
        while(working_flag_) {
            auto start_label = std::chrono::high_resolution_clock::now();
            run();
            std::chrono::duration<double, std::milli> elapsed_time =
                    std::chrono::high_resolution_clock::now() - start_label;
            std::this_thread::sleep_for(std::chrono::milliseconds( frequency_) - elapsed_time);
        }
    });
}

void AsyncWork::stop() {
    working_flag_ = false;
    if(controller_.joinable())
        controller_.join();
}

}
