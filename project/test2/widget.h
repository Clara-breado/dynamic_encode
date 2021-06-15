#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QGraphicsScene>
#include <QAxObject>
#include <QDebug>
#include "train.h"
#include "lightbars.h"
#include "lights.h"
#include "logic_lb.h"
#include "logic_train.h"
#include "logic_light.h"
#include "setting.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    logic_lb *lb[55];
    logic_light *lt[50];
    logic_train *train_1;

private slots:
    void on_pushButton_clicked();

    void on_start_btn_clicked();

    void on_stop_btn_clicked();

    void on_zx_send_clicked();

    void on_zx_recieve_clicked();

private:
    void getStaticData();
    Ui::Widget *ui;
    QGraphicsScene *scene;
    train *mytrain;
    lightbars *bar[50];
    lights *light[40];
    QString filePath = "G:\\gradethree\\static_db_1.xlsx";
    QTimer timer;
};

#endif // WIDGET_H
