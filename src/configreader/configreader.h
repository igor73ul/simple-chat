#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <QSettings>

namespace configfile {
//получить значения из конф.файла с проверкой на мин.значения
class ConfigReader {
public:
    ConfigReader();
    ~ConfigReader() = default;
    int getServerNetFrequency() const;//Период работы сервера с "сетью"
    int getClientNetFrequency() const;//Период работы клиента с "сетью"
    int getClientGuiFrequency() const;//Период обновления информации на GUI для клиента
    int getClientReconnectFrequency() const;//Период между попытками востановить подключение к серверу
private:
    enum class InformationType {
        kServerFreq=0,//server_frequency
        kClientFreq,//client_frequency
        kClientGuiFreq,//client_gui_frequency
        kClientReconnectFreq//client_gui_reconnect_frequency
    };
    int takeInformation(InformationType) const;//Запросить значение поля из конф.файла
    QSettings kConfiguration_;
};

}
#endif // CONFIGREADER_H
