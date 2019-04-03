#include "client_path.h"

#include "configreader.h"
#include "chatwindow.h"

bool ClientPath::make_client() {
    //В реальной жизни (обычно) клиент сам отвечает за свое время жизни,
    //поэтому создаём объект и далее не контролируем объект
    try {
        //стараемся не использовать исключения,
        //но Qt генерирует код допускающий их
        configfile::ConfigReader configuration;
        new chatclient::ChatWindow(configuration.getClientNetFrequency(),
                                   configuration.getClientGuiFrequency(),
                                   configuration.getClientReconnectFrequency() );
    }
    catch(std::bad_alloc) {
        return false;
    }
    catch(...) {
        return false;
    }
    return true;
}
