#ifndef SERVERCONTROLLER_H
#define SERVERCONTROLLER_H

#include <QObject>

namespace  simpleserver {
//Управляет работой сервера
class ServerController: public QObject {
    Q_OBJECT
public:
    ServerController(QObject* parent = nullptr);
    Q_INVOKABLE void registerNewUser(QObject*);
public slots:
    void deleteUser();
    void readUserMessage(const QString text);
private:
    void resend(const char *member, QGenericArgument arg, const QObject *exc);
    bool sendUserList(QObject*);
    QObjectList register_users;
};

}
#endif // SERVERCONTROLLER_H
