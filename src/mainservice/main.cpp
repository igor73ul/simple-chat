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
    mainservice_widget::ManageWindow w;
    w.show();
    return a.exec();
}
