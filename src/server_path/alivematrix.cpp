#include "alivematrix.h"

namespace  simpleserver {

bool AliveMatrix::isAlive(AliveMatrix::AliveState val) const noexcept{
    if(val == AliveMatrix::AliveState::kLost)
        return true;
    return false;
}

AliveMatrix::AliveState AliveMatrix::reduce(AliveState val) const  noexcept{
    switch(val) {
        case AliveMatrix::AliveState::kUpdateNow:
            return AliveMatrix::AliveState::kUpdatePrev;
        case AliveMatrix::AliveState::kUpdatePrev:
            return AliveMatrix::AliveState::kLost;
        default:
            return AliveMatrix::AliveState::kLost;
    }

}

std::list<int> AliveMatrix::eraselist() {
    std::list<int> result;
    for(auto iterMatrix = matrix_.begin(); iterMatrix != matrix_.end();) {
        iterMatrix->second = reduce(iterMatrix->second);
        if(isAlive(iterMatrix->second)) {
            result.emplace_back(iterMatrix->first);
            iterMatrix = matrix_.erase(iterMatrix);
        } else {
            ++iterMatrix;
        }
    }
    return std::move(result);
}

}
