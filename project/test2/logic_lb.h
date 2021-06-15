#ifndef LOGIC_LB_H
#define LOGIC_LB_H

#include <QObject>
#include "lightbars.h"
class logic_lb : public QObject
{
    Q_OBJECT
public:
    explicit logic_lb(QObject *parent = nullptr,int _pos_x = 0,int _pos_y = 140,int _bar_width = 200,int _type = 0,int _logic_type = 0);
    lightbars *view_lb;
    void getState();

signals:
    void stateChanged(int _state);
    void sendJzState(int _jl_type);

public slots:
    void toChangestate(int _nxtstate);
    void changeState(int car_pos_x,int car_pos_y);
    void change(QPointF car_pos);
    void timerTest();

    void JzState();

private:
    int id;
    int pos;
    int pos_x;
    int pos_y;
    int angle;
    bool train_flag = false;
    int state = 9;  //H,B--0 ,
    int lb_type = 0;//qj--0,jz--1,gd--2,cz--3
    int view_type = 0;
    int bar_width;

    bool lb_used(int x,int y);

public:
    int jl_type = -1;//默认正线进路--0，侧线12号--1，侧线18号--2,未开放-1
    bool JZ_FLAG = false;
    bool CZ_FLAG = false;

};

#endif // LOGIC_LB_H
