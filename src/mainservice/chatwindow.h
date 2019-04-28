#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <memory>

#include <QWidget>
#include "ui_chatwindow.h"

namespace Ui {
class ChatWindow;
}

namespace chatclient {
//окно участника программы
class ChatWindow : public QWidget {
    Q_OBJECT
public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow() = default;
    //интерфейс клиента
    Q_INVOKABLE void getUserList(const QStringList);//получить список текущих пользователей
    Q_INVOKABLE void addUser(const QString );//добавить нового пользователя
    Q_INVOKABLE void delUser(const QString );//удалить пользователя
    Q_INVOKABLE void newMsgAvailable(const QString );//получить новое сообщение
private:
    void closeEvent(QCloseEvent *);
    void keyReleaseEvent(QKeyEvent *);

    const QIcon kAvatarIcon;//одна аватарка на всех
    const QString kInformationTitle, kInformationText,//информационное сообщение
    kDelUserText, kConectUserText,//события
    kMyNameText;//приписка для идентификации самого себя
    std::unique_ptr<Ui::ChatWindow> chat_window_;//GUI форма
private slots:
    void on_sendButton_released();//обработка кнопки - отправить
signals:
    void sendUserText(const QString);//отправить сообщение на сервер
};

}
#endif // CHATWINDOW_H
