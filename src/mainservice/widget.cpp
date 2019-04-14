#include "widget.h"

#include <iostream>

#include "chatwindow.h"

namespace  mainservice_widget {

ManageWindow::ManageWindow(QWidget *parent) : QWidget(parent), ui_form_(new Ui::Widget),
    kConnectIco_(":/ico/ico/icon-ok.png") {
    ui_form_->setupUi(this);
    ui_form_->label->setPixmap(kConnectIco_);
    net_server_.moveToThread(&server_thread_);
    server_thread_.start();
}

ManageWindow::~ManageWindow() {
    server_thread_.quit();
    server_thread_.wait();
}

void ManageWindow::on_newClient_released() {
    const char kRegNewUserCommand[] = {"registerNewUser"};
    try {
        auto client = new chatclient::ChatWindow();
        QMetaObject::invokeMethod(&net_server_, kRegNewUserCommand, Qt::QueuedConnection, Q_ARG(QObject*, client));
    } catch(const std::bad_alloc & exc) {
        std::cerr<<"Exception:New Client:"<<exc.what()<<std::endl;
    }
}

void ManageWindow::closeEvent(QCloseEvent *) {
    QCoreApplication::exit(0);
}

}
