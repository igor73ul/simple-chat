#include "chatwindow.h"
#include <iostream>
#include <QListWidgetItem>
#include <QMessageBox>

#include "loginform.h"

namespace chatclient {

ChatWindow::ChatWindow(QWidget *parent) :
    QWidget(parent),
    kAvatarIcon(":/ico/ico/background.png"), kInformationTitle("Logout"),
    kInformationText("Do you want close chat-client application?"),
    kDelUserText(" disconnected from server."), kConectUserText(" connected to server."),
    kMyNameText("(It`s me)"),
    chat_window_(new Ui::ChatWindow) {
    chat_window_->setupUi(this);
    const auto myName = LoginForm().userName();
    setObjectName(myName);
    setAttribute(Qt::WA_DeleteOnClose);
    //Центруем позицию кнопки-Send в ячейке
    auto itemLayout = chat_window_->gridLayout->itemAtPosition(1,1);
    if(itemLayout != nullptr)
        itemLayout->setAlignment(Qt::AlignHCenter);
    show();
    addUser(myName + kMyNameText);
}

void ChatWindow::addUser(const QString userName) {
    try {
        auto newUser = new QListWidgetItem(userName, chat_window_->clientList);
        newUser->setIcon(kAvatarIcon);
    } catch (const std::bad_alloc &exc) {
        std::cerr<<"Exception::addUser:"<<exc.what()<<std::endl;
        return;
    }
    chat_window_->textBrowser->appendHtml("<b>" + userName + "</b>" + kConectUserText);
}

void ChatWindow::getUserList(const QStringList users) {
    Q_FOREACH(auto one_user, users) {
        addUser(one_user);
    }
}

void ChatWindow::delUser(const QString userName) {
    auto deleteUsersList = chat_window_->clientList->findItems(userName, Qt::MatchExactly);
    for(auto delUser : deleteUsersList) {
        delete chat_window_->clientList->takeItem(chat_window_->clientList->row(delUser));
        chat_window_->textBrowser->appendHtml("<b>" + userName + "</b>" + kDelUserText);
    }
}

void ChatWindow::newMsgAvailable(const QString txt) {
    chat_window_->textBrowser->appendHtml(txt);
}

void ChatWindow::on_sendButton_released() {
    const auto userText(chat_window_->textEdit->toPlainText());
    if(userText.isEmpty())
        return;
    emit sendUserText(userText);
    chat_window_->textEdit->clear();
}

void ChatWindow::closeEvent(QCloseEvent *event) {
    if(QMessageBox::information(this, kInformationTitle, kInformationText, QMessageBox::Yes, QMessageBox::No) ==
            QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}

void ChatWindow::keyReleaseEvent(QKeyEvent * event)
{
    chat_window_->textEdit->setFocus();
    if(event->key() == Qt::Key_Return)// Qt::Key_Enter)
        on_sendButton_released();
}

}
