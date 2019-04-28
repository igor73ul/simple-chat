#ifndef SERVERCONTROLLER_H
#define SERVERCONTROLLER_H

#include <QObject>

namespace  simpleserver {
//Управляет работой сервера
class ServerController: public QObject {
    Q_OBJECT
public:
    ServerController(QObject* parent = nullptr);
    Q_INVOKABLE void registerNewUser(QObject*);//добавить нового пользователя в систему
public slots:
    void deleteUser();//обработка события - пользователь отключился от сервера
    void readUserMessage(const QString text);//обработка события - пользователь отправил текст
private:
    void resend(const char *member, QGenericArgument arg, const QObject *exc);
    bool sendUserList(QObject*);
    QObjectList register_users;//список пользователей на сервере
};

}
#endif // SERVERCONTROLLER_H
