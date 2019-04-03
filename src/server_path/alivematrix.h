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
    void update(const int kUserId){ matrix_[kUserId] = AliveState::kUpdateNow; }
    std::list<int> eraselist(); //Забрать кандидатов на удаление, завершив текущую итерацию обновлений
private:
    enum class AliveState {
        kUpdateNow=0, //Пришло сообщение
        kUpdatePrev, //Собщение с прошлой итерации
        kLost //Давно не было обновлений
    };
    AliveState reduce(AliveState) const noexcept; //Получить следующее (худшее) состояние
    bool isAlive(AliveState) const noexcept; //оценить состояние (жив ли)
    std::map<int, AliveState> matrix_;
};

}
#endif // ALIVEMATRIX_H
