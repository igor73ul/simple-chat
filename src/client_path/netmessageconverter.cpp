#include "netmessageconverter.h"

namespace chatclient {

using namespace network_imitation;

NetMessageConverter::NetMessageConverter(const QString & name, const int updating_time):kUniqClientID_(getNewClientUniqID()),
    AsyncWork(updating_time), myusername_(name) {
    if(!name.isEmpty()) {
        start();
        reconnect();
    }
}

NetMessageConverter::~NetMessageConverter() {
    disconnect();
    stop();
}

void NetMessageConverter::reconnect() {
    output_traffic_.push_back(NetMessage(kUniqClientID_, NetMessage::CommandCode::kAddUser, myusername_.toStdString()));
}

void NetMessageConverter::disconnect() {
    output_traffic_.push_back(NetMessage(kUniqClientID_, NetMessage::CommandCode::kDelUser, std::string()));
}

void NetMessageConverter::load() {
    std::list<NetMessage> traffic;
    input_traffic_.swap(traffic);
    for(auto msg : traffic) {
        switch(msg.command_id) {
          case NetMessage::CommandCode::kTextMsg: {
            current_data_.append(qMakePair(ChatCommand::kNewMsg,QString::fromStdString(msg.text)) );
            break;
          }
          case NetMessage::CommandCode::kAddUser: {
            current_data_.append(qMakePair(ChatCommand::kAddUser,QString::fromStdString(msg.text)) );
            break;
          }
          case NetMessage::CommandCode::kDelUser: {
            current_data_.append(qMakePair(ChatCommand::kDelUser,QString::fromStdString(msg.text)) );
            break;
          }
        case NetMessage::CommandCode::kAlliveMsg: {
            current_data_.append(qMakePair(ChatCommand::kConnectToServer,QString()));
            break;
          }
          default: {
            break;
          }
        }
    }
}
void NetMessageConverter::sendText(const QString &txt) {
    output_traffic_.push_back(NetMessage(kUniqClientID_, NetMessage::CommandCode::kTextMsg, txt.toStdString()));
}

void NetMessageConverter::run() {
    std::list<NetMessage> tmpList;
    output_traffic_.swap(tmpList);//забираем подготовленные сообщения для отправки, очищая внутренний список
    sendAllivemsg(tmpList);//если "молчим", дописываем alive сообщение
    //обмениваемся с главным хранилищем: отдаём "свой", получая сообщения для "нас"
    if(net_controller_.exchange(kServerID_, kUniqClientID_, tmpList))
        input_traffic_.push_back(std::move(tmpList));
}

void NetMessageConverter::sendAllivemsg(std::list<NetMessage> &data) {
    if(data.empty())
        data.emplace_back(kUniqClientID_, NetMessage::CommandCode::kAlliveMsg, std::string());
}

}
