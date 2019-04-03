#include "chatwindow.h"

#include <QTimer>
#include <QListWidgetItem>
#include <QMessageBox>

#include "loginform.h"

namespace chatclient {

ChatWindow::ChatWindow(const int client_freq, const int client_gui_freq,
                       const int reconn_freq, QWidget *parent) :
    QWidget(parent),
    kAvatarIcon(":/ico/ico/background.png"), kInformationTitle("Logout"),
    kInformationText("Do you want close chat-client application?"),
    kDelUserText(" disconnected from server."), kConectUserText(" connected to server."),
    kMyNameText("(It`s me)"), kWarningTitle("Warning"),
    kWarningText("Can`t add a user!"), kReconnectTitle("Conection lost"),
    kReconnectText("Sorry. Server not response."),
    chat_window_(new Ui::ChatWindow), netclient_([&](){
        QString name(LoginForm().userName());
        if(name.isEmpty()) ready_flag_ = false;
        return qMove(name);
    }(),
    client_freq), kClientGuiFreq(client_gui_freq), kReconnFreq(reconn_freq) {
    if(!ready_flag_)
        return;
    chat_window_->setupUi(this);
    if(startTimer(kClientGuiFreq) == 0) {
        ready_flag_ = false;
        return;
    }
    //Центруем позицию кнопки-Send в ячейке
    auto itemLayout = chat_window_->gridLayout->itemAtPosition(1,1);
    if(itemLayout != nullptr)
        itemLayout->setAlignment(Qt::AlignHCenter);
    show();
}

void ChatWindow::addUser(const QString &userName) {
    auto newUser = new(std::nothrow) QListWidgetItem(userName);
    if(newUser == nullptr) {
       QMessageBox::warning(this, kWarningTitle, kWarningText);
       return;
    }
    newUser->setIcon(kAvatarIcon);
    chat_window_->clientList->addItem(newUser);
}

void ChatWindow::delUser(const QString &userName) {
    auto deleteUsersList = chat_window_->clientList->findItems(userName, Qt::MatchExactly);
    for(auto delUser : deleteUsersList) {
        delete chat_window_->clientList->takeItem(chat_window_->clientList->row(delUser));
        chat_window_->textBrowser->appendHtml("<b>" + userName + "</b>" + kDelUserText);
    }
}

void ChatWindow::newText(const QString &txt) {
    chat_window_->textBrowser->appendHtml(txt);
}

void ChatWindow::on_sendButton_released() {
    QString userText(chat_window_->textEdit->toPlainText());
    if(userText.isEmpty())
        return;
    netclient_.sendText(userText);
    chat_window_->textEdit->clear();
}

void ChatWindow::closeEvent(QCloseEvent *event) {
    if(QMessageBox::information(this, kInformationTitle, kInformationText, QMessageBox::Yes, QMessageBox::No) ==
            QMessageBox::Yes) {
        delete this;//! уничтожение объекта
    } else {
        event->ignore();
        return;
    }
}

void ChatWindow::keyReleaseEvent(QKeyEvent * event)
{
    chat_window_->textEdit->setFocus();
    if(event->key() == Qt::Key_Return)// Qt::Key_Enter)
        on_sendButton_released();
}

void ChatWindow::processingComand(const NetMessageConverter::ChatMsg &info) {
    switch(info.first) {
      case NetMessageConverter::ChatCommand::kAddUser: {
        if(chat_window_->clientList->count() == 0) {//!Подключение, первый пользователь - это я сам
            addUser(kMyNameText + info.second);
        } else {
            addUser(info.second);
            chat_window_->textBrowser->appendHtml("<b>" + info.second + "</b>" + kConectUserText);
        }
        break;
      }
      case NetMessageConverter::ChatCommand::kDelUser: {
        delUser(info.second);
        break;
      }
      case NetMessageConverter::ChatCommand::kNewMsg: {
        newText(info.second);
        break;
      }
      default: {
        break;
      }
    }
}

void ChatWindow::reconnect() {
    netclient_.load();
    if(netclient_.isEmpty()) {
        netclient_.reconnect();
        QTimer::singleShot(kReconnFreq, this, SLOT(reconnect()));//&ChatWindow::reconnect);
    } else {
        if(startTimer(kClientGuiFreq) == 0) {
            QMessageBox::critical(this, kWarningTitle, kDelUserText, QMessageBox::NoButton);
            delete this;//переподключиться невозможно
            return;
        }
        chat_window_->sendButton->setEnabled(true);
        chat_window_->textEdit->setEnabled(true);
    }
}

void ChatWindow::timerEvent(QTimerEvent *timerID) {
    static bool isDelay = true;//Для пропуска первой задержки
    netclient_.load();
    if(netclient_.isEmpty()) {
        if(isDelay) {
            isDelay = false;
            return;
        }
        killTimer(timerID->timerId());
        netclient_.disconnect();
        chat_window_->sendButton->setDisabled(true);
        chat_window_->textEdit->setDisabled(true);
        chat_window_->clientList->clear();
        chat_window_->textBrowser->appendPlainText(kReconnectText);
        if(QMessageBox::critical(this, kReconnectTitle, kReconnectText, QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
            netclient_.reconnect();
            QTimer::singleShot(kReconnFreq, this, SLOT(reconnect()));//&ChatWindow::reconnect);
        } else {
            netclient_.stop();
        }
    } else {
        isDelay = true;
        do {
            auto info = netclient_.takeNext();
            processingComand(info);
        }while(!netclient_.isEmpty());
    }
}

}
