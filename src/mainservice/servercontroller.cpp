#include "servercontroller.h"

#include <QStringList>

namespace  simpleserver {

ServerController::ServerController(QObject * parent):QObject(parent) {}

void ServerController::resend(const char *member, QGenericArgument arg, const QObject *exc) {
    Q_FOREACH(auto one_client, register_users) {
        if(one_client == exc)
            continue;
        QMetaObject::invokeMethod(one_client, member, Qt::QueuedConnection, arg);
    }
}

bool ServerController::sendUserList(QObject* user) {
    QStringList result;
    Q_FOREACH(auto one_user, register_users) {
        result<<one_user->objectName();
    }
    return QMetaObject::invokeMethod(user, "getUserList", Qt::QueuedConnection, Q_ARG(const QStringList, result));
}

void ServerController::registerNewUser(QObject* user) {

    if(user != nullptr) {
        if(connect(user, &QObject::destroyed, this, &ServerController::deleteUser, Qt::QueuedConnection) &&
                connect(user, SIGNAL(sendUserText(const QString)), this, SLOT(readUserMessage(const QString)), Qt::QueuedConnection))
        {
            if(sendUserList(user)) {
                register_users.append(user);
                resend("addUser", Q_ARG(const QString, user->objectName()), user);
            }
        }
    }
}

void ServerController::deleteUser() {
    QObject* user(sender());
    if(!register_users.contains(user))
        return;
    register_users.removeOne(sender());
    resend("delUser", Q_ARG(const QString, user->objectName()), nullptr);
}

void ServerController::readUserMessage(const QString text) {
    QObject* user(sender());
    if(!register_users.contains(user))
        return;
    const QString message("<b>" + user->objectName() + ":</b> " + text);
    resend("newMsgAvailable", Q_ARG(const QString, message), nullptr);
}

}
