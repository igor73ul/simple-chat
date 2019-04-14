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
    //минимизировал исключения. остальное фатально, поэтому выходим
    std::unique_ptr<mainservice_widget::ManageWindow> mainwidget;
    try {
        mainwidget.reset(new mainservice_widget::ManageWindow);
    } catch(const std::exception & exc) {
        std::cerr<<"Exception:"<<exc.what()<<std::endl;
        return -1;
    }
    mainwidget->show();
    return a.exec();
}
