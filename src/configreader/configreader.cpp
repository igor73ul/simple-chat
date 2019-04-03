#include "configreader.h"


namespace configfile {

ConfigReader::ConfigReader():kConfiguration_("../config/settings.cfg", QSettings::IniFormat) {}

int ConfigReader::takeInformation(InformationType type) const {
    switch (type) {
    case InformationType::kServerFreq:
        return kConfiguration_.value("server_frequency").toInt();
    case InformationType::kClientFreq:
        return kConfiguration_.value("client_frequency").toInt();
    case InformationType::kClientGuiFreq:
        return kConfiguration_.value("client_gui_frequency").toInt();
    case InformationType::kClientReconnectFreq:
        return kConfiguration_.value("client_gui_reconnect_frequency").toInt();
    default:
        break;
    }
    return 0;
}


int ConfigReader::getServerNetFrequency()  const {
    const auto freqminimum(10), freqdefault(150);
    auto freq = takeInformation(InformationType::kServerFreq);
    if(freq < freqminimum)
        freq = freqdefault;
    return freq;
}
int ConfigReader::getClientNetFrequency() const {
    const auto freqminimum(10), freqdefault(150);
    auto freq = takeInformation(InformationType::kServerFreq);
    if(freq < freqminimum)
        freq = freqdefault;
    return freq;
}
int ConfigReader::getClientGuiFrequency() const {
    const auto freqminimum(20), freqdefault(300);
    auto freq = takeInformation(InformationType::kClientGuiFreq);
    if(freq < freqminimum)
        freq = freqdefault;
    return freq;
}

int ConfigReader::getClientReconnectFrequency() const {
    const auto freqminimum(300), freqdefault(1000);
    auto freq = takeInformation(InformationType::kClientReconnectFreq);
    if(freq < freqminimum)
        freq = freqdefault;
    return freq;
}

}
