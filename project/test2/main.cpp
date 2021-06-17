#include "widget.h"
#include <QApplication>
#include "train.h"
#include <QtWidgets>
#include <QTimer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    //w.setWindowTitle("动态编码仿真");
    //w.setWindowIcon(QIcon("G:\\gradethree\\test2\\logo.ico"));
    w.setWindowIcon(QIcon(":/icon/logo.ico"));
    w.showMaximized();
    w.show();

    return a.exec();
}
