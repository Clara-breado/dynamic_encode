#ifndef LOGIC_LB_H
#define LOGIC_LB_H

#include <QObject>
#include "lightbars.h"
class logic_lb : public QObject
{
    Q_OBJECT
public:
    explicit logic_lb(QObject *parent = nullptr,int _pos_x = 0,int _pos_y = 140,int _bar_width = 200,int _angle = 0);
    lightbars *view_lb;
    void getState();

signals:
    void stateChanged(int _state);

public slots:
    void toChangestate(int _nxtstate);
    void changeState(int car_pos_x,int car_pos_y);
    void timerTest();
private:
    int id;
    int pos;
    int pos_x;
    int pos_y;
    int angle;
    bool train_flag = false;
    int state = 9;  //H,B--0 ,
    int lb_type = 0;//qj,cz,gd
    int jl_type = 0;//默认正线进路--0，侧线12号--1，侧线18号--2

};

#endif // LOGIC_LB_H
