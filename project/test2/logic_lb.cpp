#include "logic_lb.h"
#include <QDebug>

logic_lb::logic_lb(QObject *parent,int _pos_x,int _pos_y,int _bar_width,int _angle) : QObject(parent),pos_x(_pos_x),pos_y(_pos_y),angle(_angle)
{
    view_lb = new lightbars(pos_x,pos_y,_bar_width,angle);
}

void logic_lb::getState(){
    if(this->train_flag == true){
//        qDebug()<<"car on me"<<endl;
        this->state = 0;
    }
    emit stateChanged(this->state);
}

void logic_lb::toChangestate(int _nxtstate){
    if(this->train_flag==true){
        this->view_lb->state = 0;
    }else{
        this->state = _nxtstate +1;
        this->view_lb->state = this->state;
    }

    getState();
}

void logic_lb::changeState(int car_pos_x,int car_pos_y){
    if(car_pos_x*2>this->pos_x && car_pos_x*2<this->pos_x+200){
        train_flag = true;
        qDebug()<<"car:"<<car_pos_x<<"-----"<<"lb:"<<this->pos_x<<endl;

    }else{
        train_flag = false;
    }

}

void logic_lb::timerTest(){
    getState();

}
