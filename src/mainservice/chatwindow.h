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
    explicit ChatWindow(QWidget *parent = 0);
    ~ChatWindow() = default;
    Q_INVOKABLE void getUserList(const QStringList);
public slots:
    void addUser(const QString );
    void delUser(const QString );
    void newMsgAvailable(const QString );
private:
    void closeEvent(QCloseEvent *);
    void keyReleaseEvent(QKeyEvent *);

    const QIcon kAvatarIcon;//одна аватарка на всех
    const QString kInformationTitle, kInformationText,//информационное сообщение
    kDelUserText, kConectUserText,//события
    kMyNameText;//приписка для идентификации самого себя
    std::unique_ptr<Ui::ChatWindow> chat_window_;//GUI форма
private slots:
    void on_sendButton_released();
signals:
    void sendUserText(const QString);
};

}
#endif // CHATWINDOW_H
