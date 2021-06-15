#ifndef LOGIC_TRAIN_H
#define LOGIC_TRAIN_H

#include <QObject>
#include <QTimer>
#include "train.h"

class logic_train : public QObject
{
    Q_OBJECT
public:
    explicit logic_train(QObject *parent = nullptr,int _pos_x = 0,int _pos_y = 100);
    train *view_train;
    QTimer mytimer;
    void enterQD();

signals:
    void sendPos(int _pos_x,int _pos_y);
    void sendPoint(QPointF train_pos);

public slots:
//    void toStop(bool stop_flag);
    void timerStart();

private:
    int pos_x;
    int pos_y;

};

#endif // LOGIC_TRAIN_H
