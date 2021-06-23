#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QMenu>
#include <QAction>
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
#include "myscene.h"

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

    void on_start_btn_clicked();

    void on_stop_btn_clicked();

    void on_zx_recieve_clicked();

    void on_cx_recieve_clicked();

    void on_lg_recieve_clicked();

    void on_cx_send_clicked();

    void on_lg_send_clicked();

    void on_zx_send_clicked();

    void on_zx_send_customContextMenuRequested(const QPoint &pos);
    void testMenu();
    void r_YD();
    void showMenu(const QPoint &pos);
    void showJCMenu(const QPoint &pos);
    void on_zx_recieve_customContextMenuRequested(const QPoint &pos);

private:
    void getStaticData();

    QMenu *m_menu;
    QMenu *r_menu;

    QAction *m_yd;
    QAction *r_yd;


    Ui::Widget *ui;
    myscene *scene;
    //QGraphicsScene *scene;
    QString filePath = "G:\\gradethree\\static_db_1.xlsx";
    //QString filePath = "G:\\gradethree\\test2\\test2.xlsx";

    QTimer timer;
};

#endif // WIDGET_H
