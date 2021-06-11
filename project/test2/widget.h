#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QGraphicsScene>
#include "train.h"
#include "lightbars.h"
#include "lights.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_start_btn_clicked();

    void on_stop_btn_clicked();

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    train *mytrain;
    lightbars *bar[8];
    lights *light[8];
    QTimer timer;
};

#endif // WIDGET_H
