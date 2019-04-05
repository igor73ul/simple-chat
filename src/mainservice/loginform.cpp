#include "loginform.h"

namespace chatclient {

LoginForm::LoginForm(QWidget *parent) :
    QDialog(parent), login_form(new Ui::LoginForm) {
    login_form->setupUi(this);
    show();
}

QString LoginForm::userName() {
    if(loop.exec() > 0)
        return login_form->lineEdit->text();
    return QString("empty");
}

}
