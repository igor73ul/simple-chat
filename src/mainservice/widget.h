#ifndef WIDGET_H
#define WIDGET_H

#include <memory>

#include <QThread>

#include "servercontroller.h"
#include "ui_widget.h"

namespace Ui {
class Widget;
}

namespace  mainservice_widget {
//GUI-класс для управления Симулятором чата: запустить серверную часть, добавить клиента
class ManageWindow : public QWidget {
    Q_OBJECT
public:
    explicit ManageWindow(QWidget *parent = nullptr);
    ~ManageWindow();
private:
    void closeEvent(QCloseEvent *);
    std::unique_ptr<Ui::Widget> ui_form_;//Основная графическая форма
    simpleserver::ServerController net_server_;//server
    QThread server_thread_;
    const QPixmap kConnectIco_;//иконки-состояния сервера
private slots:
    void on_newClient_released();//команда - добавить пользователя

};

}
#endif // WIDGET_H
