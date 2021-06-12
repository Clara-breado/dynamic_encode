#include "widget.h"
#include <QApplication>
#include "train.h"
#include <QtWidgets>
#include <QTimer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.showMaximized();
    w.show();

    return a.exec();
}
