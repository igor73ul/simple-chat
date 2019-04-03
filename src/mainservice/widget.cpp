#include "widget.h"

#include <QMessageBox>

#include "client_path.h"

namespace  mainservice_widget {

ManageWindow::ManageWindow(QWidget *parent) : QWidget(parent),
    ui_form_(new Ui::Widget), net_server_(new simpleserver::Server_path),
    kErrorMessageUser_("Can`t create new user!"), kErrorMessageServer_("Can`t create server!"),
    kErrorTitle_("Error"),
    kConnectIco_(":/ico/ico/icon-ok.png"), kDisconnectIco_(":/ico/ico/icon-fail.png") {
    ui_form_->setupUi(this);
    ui_form_->label->setPixmap(kDisconnectIco_);
}

void ManageWindow::on_startServer_toggled(bool checked) {
    ui_form_->startServer->setEnabled(!checked);
    ui_form_->stopServer->setEnabled(checked);
    ui_form_->newClient->setEnabled(checked);
    if(checked) {
        ui_form_->label->setPixmap(kConnectIco_);
        if(!net_server_->start()) {
            QMessageBox::critical(this, kErrorTitle_, kErrorMessageServer_);
            QCoreApplication::exit(-1);
        }
    } else {
        ui_form_->label->setPixmap(kDisconnectIco_);
        net_server_->stop();
    }
}

void ManageWindow::on_newClient_released() {
    if(!ClientPath::make_client())
        QMessageBox::critical(this, kErrorTitle_, kErrorMessageUser_);
}

void ManageWindow::closeEvent(QCloseEvent *) {
    QCoreApplication::exit(0);
}

}
