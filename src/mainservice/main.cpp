#include <iostream>

#include <QApplication>
#include <QFile>

#include "widget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QFile style_file(":/style/qss/coffee.qss");
    if (style_file.open(QIODevice::ReadOnly)) {
        a.setStyleSheet(style_file.readAll());
        style_file.close();
    }
    auto result = -1;
    //минимизировал исключения. остальное фатально, поэтому обрабатываем и выходим
    try {
        mainservice_widget::ManageWindow w;
        w.show();
        result = a.exec();
    }
    catch(const std::exception & exc) {
        std::cerr<<"Exception:"<<exc.what()<<std::endl;
        return result;
    }
    return result;
}
