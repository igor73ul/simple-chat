#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <memory>

#include <QDialog>
#include <QEventLoop>

#include "ui_loginform.h"

namespace Ui {
class LoginForm;
}

namespace chatclient {
//форма для задания имя пользователя в чате
class LoginForm : public QDialog {
    Q_OBJECT
public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm() = default;
    QString userName();//имя которое ввёл пользователь или пусто в случаи отмены
private:
    std::unique_ptr<Ui::LoginForm> login_form;
    QEventLoop loop;
private slots:
    void accept() { loop.exit(1); }
    void reject() { loop.exit(0); }
};

}
#endif // LOGINFORM_H
