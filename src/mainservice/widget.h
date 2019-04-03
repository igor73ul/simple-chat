#ifndef WIDGET_H
#define WIDGET_H

#include <memory>

#include "server_path.h"
#include "ui_widget.h"

namespace Ui {
class Widget;
}

namespace  mainservice_widget {
//GUI-класс для управления Симулятором чата: запустить/остановить серверную часть, добавить клиента
class ManageWindow : public QWidget {
    Q_OBJECT
public:
    explicit ManageWindow(QWidget *parent = 0);
    ~ManageWindow() = default;
private:
    std::unique_ptr<Ui::Widget> ui_form_;//Основная графическая форма
    std::unique_ptr<simpleserver::Server_path> net_server_;//Основная графическая форма
    const QString kErrorMessageUser_, kErrorMessageServer_, kErrorTitle_;//текст сообщений об ошибке
    const QPixmap kConnectIco_, kDisconnectIco_;//иконки-состояния сервера
    void closeEvent(QCloseEvent *);
private slots:
    void on_startServer_toggled(bool checked);//команда на смену состояния сервера
    void on_newClient_released();//команда - добавить пользователя

};

}
#endif // WIDGET_H
