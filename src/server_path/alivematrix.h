#ifndef ALIVEMATRIX_H
#define ALIVEMATRIX_H

#include <map>
#include <list>

namespace  simpleserver {
//подсчёт обновлений от абонентов, что бы следить кто жив, а кто отвалился
class AliveMatrix {
public:
    AliveMatrix() = default;
    //обновить состояние-жив для абонента kUserId идентификатором
    void update(const int kUserId);
    void del(const int kUserId) { matrix_[kUserId] = AliveState::kLost; }
    void insert(const int kUserId) { matrix_[kUserId] = AliveState::kUpdateNow; }
    std::list<int> eraselist(); //Забрать кандидатов на удаление, завершив текущую итерацию обновлений
private:
    enum class AliveState {
        kUpdateNow=0, //Пришло сообщение
        kUpdatePrev, //Собщение с прошлой итерации
        kUpdateLast, //Кандидат на вылет
        kLost //Давно не было обновлений
    };
    AliveState reduce(AliveState) const noexcept; //Получить следующее (худшее) состояние
    bool isAlive(AliveState) const noexcept; //оценить состояние (жив ли)
    std::map<int, AliveState> matrix_;
};

inline void AliveMatrix::update(const int kUserId) {
    auto iter = matrix_.find(kUserId);
    if(iter != matrix_.end())
        iter->second = AliveState::kUpdateNow;
}

}
#endif // ALIVEMATRIX_H
