#ifndef NETMESSAGECONVERTER_H
#define NETMESSAGECONVERTER_H

#include <QPair>
#include <QQueue>
#include <QString>

#include "asyncwork.h"
#include "safelist.h"
#include "netservice.h"

namespace chatclient {
//расширение для сетевого клиента, конвертит информацию в формат понятный чат-окну
//прослойка для асинхронной работы с хранилищем
class NetMessageConverter : public network_imitation::AsyncWork
{
public:
    //команды которые понятны чат-окну
    enum class ChatCommand {
        kConnectToServer = 0,
        kDisconnectFromServer,
        kDelUser,
        kAddUser,
        kNewMsg
    };
    using ChatMsg = QPair<ChatCommand, QString>;
    NetMessageConverter(const QString &name, const int updating_time);
    ~NetMessageConverter();
    ChatMsg takeNext() {return std::move(current_data_.takeFirst());}
    bool isEmpty() const noexcept {return current_data_.isEmpty();}
    void load();//загрузить все сообщения из хранилища для клиента
    void sendText(const QString &);//отправить текстовое сообщение в хранилище
    void reconnect();
private:
    void run();//один "такт" работы с сервером
    void sendAllivemsg(std::list<network_imitation::NetMessage> &);

    const int kUniqClientID_;
    const int kServerID_ = network_imitation::getServerID();//адрес сервера
    const QString myusername_;//имя данного клиента чата
    QQueue<ChatMsg> current_data_;//очередь необработанных сообщений из хранилища
    network_imitation::SafeList input_traffic_, output_traffic_;
    network_imitation::NetService net_controller_;
};

}
#endif // NETMESSAGECONVERTER_H

