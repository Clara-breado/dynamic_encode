#include "logic_lb.h"
#include <QDebug>

logic_lb::logic_lb(QObject *parent,int _pos_x,int _pos_y,int _bar_width,int _type,int _logic_type) : QObject(parent),pos_x(_pos_x),pos_y(_pos_y),lb_type(_logic_type),view_type(_type),bar_width(_bar_width)
{
    view_lb = new lightbars(pos_x,pos_y,_bar_width,view_type,lb_type);
}

void logic_lb::getState(){
//    if(this->train_flag == true){
//        this->state = 0;
//    }
    emit stateChanged(this->train_flag == true?0:this->state);
}

void logic_lb::toChangestate(int _nxtstate){
//    if(this->train_flag==true){
//        this->view_lb->state = 0;
//    }else{
        this->state = _nxtstate +1;
        this->view_lb->state = this->state;
    //}



    getState();
}

void logic_lb::changeState(int car_pos_x,int car_pos_y){
//    if(car_pos_x>this->pos_x && car_pos_x<this->pos_x+200){
//        train_flag = true;
//        qDebug()<<"car:"<<car_pos_x<<"-----"<<"lb:"<<this->pos_x<<endl;

//    }else{
//        train_flag = false;
//        qDebug()<<"car:"<<car_pos_x<<endl;

//    }

    train_flag = lb_used(car_pos_x,car_pos_y);
    if(this->train_flag==true){
//        qDebug()<<this->lb_type<<endl;
        //this->view_lb->state = 0;
    }
    else {
        train_flag = false;
        //this->view_lb->state = 8;
    }

}

void logic_lb::change(QPointF car_pos){
    qreal x = this->view_lb->mapToParent(car_pos).x();
    //qDebug()<<"car:"<<x<<"-----"<<"lb:"<<this->pos_x<<endl;
}

void logic_lb::timerTest(){
    getState();
    if(lb_type==1){
        JzState();
    }

}

void logic_lb::JzState(){
    if(this->train_flag==true){
        //HU
        qDebug()<<"jl close!"<<endl;
        jl_type = -1;//关闭进路
        JZ_FLAG = false;
        this->view_lb->state = 1;
    }else{
        if(JZ_FLAG){
            //JC
            qDebug()<<"jl open!"<<endl;
            this->view_lb->state = 1;//下一个区段码有区别根据进路方式
        }else{
            //B
            qDebug()<<"jl close!"<<endl;
            jl_type = -1;//未开放
            this->view_lb->state = 10;
        }
    }
    emit sendJzState(jl_type);



}

bool logic_lb::lb_used(int x,int y){
    bool flag = false;
    switch (this->view_type) {
    case 0:{
        if(x>this->pos_x && x<this->pos_x+this->bar_width && y<pos_y-560 && y>pos_y-620){
            flag = true;
        }
        break;
    }
    case 4:{
        if(x>this->pos_x && x <this->pos_x+395 && y<20 && y >(20-250)){
            flag = true;
        }
        if(x>this->pos_x+390 && x<this->pos_x+575 && y<(20-250) && y>(20-360)){
            flag = true;
        }
        break;
    }
    default: break;
    }
    return flag;
}
