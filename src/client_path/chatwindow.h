#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <memory>

#include <QWidget>

#include "netmessageconverter.h"
#include "ui_chatwindow.h"

namespace Ui {
class ChatWindow;
}

namespace chatclient {
//окно участника программы
class ChatWindow : public QWidget {
    Q_OBJECT
public:
    explicit ChatWindow(const int kClientFreq, const int kClientGuiFreq,
                        const int kReconnFreq, QWidget *parent = 0);
    bool isReady() const noexcept { return ready_flag_;}//удалось ли завершить инициализацию
private:
    ~ChatWindow() = default;//уничтожение объекта только по собственной инициативе
    void addUser(const QString &);
    void delUser(const QString &);
    void newText(const QString &);
    void processingComand(const NetMessageConverter::ChatMsg &);

    void closeEvent(QCloseEvent *);
    void timerEvent(QTimerEvent *);
    void keyReleaseEvent(QKeyEvent *);

    const QIcon kAvatarIcon;//одна аватарка на всех
    const QString kInformationTitle, kInformationText,//информационное сообщение
    kDelUserText, kConectUserText,//события
    kMyNameText,//приписка для идентификации самого себя
    kWarningTitle, kWarningText,//текст предупреждения
    kReconnectTitle, kReconnectText;//запрос на переподключение

    bool ready_flag_ = true;//удалось ли завершить инициализацию
    std::unique_ptr<Ui::ChatWindow> chat_window_;//GUI форма
    NetMessageConverter netclient_;//"сетевое" соединение
    const int kClientGuiFreq;//период обновления GUI
    const int kReconnFreq;//время между переподключениями
private slots:
    void on_sendButton_released();
    void reconnect();
};

}
#endif // CHATWINDOW_H
