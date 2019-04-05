#include "widget.h"

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
    auto client = new chatclient::ChatWindow();
    QMetaObject::invokeMethod(&net_server_, "registerNewUser", Qt::QueuedConnection, Q_ARG(QObject*, client));
}

void ManageWindow::closeEvent(QCloseEvent *) {
    QCoreApplication::exit(0);
}

}
