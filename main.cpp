#include "myprint.h"
#include <QApplication>
#include <QGuiApplication>

extern bool loginFlag=0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Address w;

    QFont font;
    //font.setPointSize(9);//font size
    font.setFamily("微软雅黑");//change all word type
    a.setFont(font);

    w.show();
    return a.exec();//主运行循环
}
