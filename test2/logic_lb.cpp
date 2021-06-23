#include "logic_lb.h"
#include <QDebug>

logic_lb::logic_lb(QObject *parent,int _pos_x,int _pos_y,int _bar_width,int _type,int _logic_type) : QObject(parent),pos_x(_pos_x),pos_y(_pos_y),lb_type(_logic_type),view_type(_type),bar_width(_bar_width)
{
    view_lb = new lightbars(pos_x,pos_y,_bar_width,view_type,lb_type);
}

void logic_lb::getState(){
        //cx12: 3--LU     30--HU     31--UU   32--U2
        if(this->state>=32 && this->state<40) this->state -= 30;
        //cx18: 3--LU     40--HU     41--UUS  42--U2S
        if(this->state>=42 && this->state<50) this->state -= 40;
        //yd 51--HB 52=2--U
        if(this->YD_FLAG) this->state = 50;
        if(this->state>=51) this->state -= 50;

        if(this->state>=20 && this->state<30) this->state -= 20;

        int send_state = this->state;
        if(this->view_lb->gzFlag){
            this->view_lb->state = 0;//H
            send_state = 0;//HU
        }else if(this->train_flag){
            send_state = 0;
        }
    emit stateChanged(send_state);
}

void logic_lb::toChangestate(int _nxtstate){
    this->nxt_state = _nxtstate;    //storage

    if(this->lb_type!=3){
        this->state = _nxtstate +1;
        this->view_lb->state = this->state;
    }



    getState();
}

void logic_lb::changeState(int car_pos_x,int car_pos_y){
    train_flag = lb_used(car_pos_x,car_pos_y);
}

void logic_lb::timerTest(){
    getState();
    if(lb_type==1){
        JzState();
    }
    if(lb_type==3){
        CzState();
    }

}

void logic_lb::JzState(){
    if(this->train_flag==true){
        //HU
//        qDebug()<<"jl close!"<<endl;
        jl_type = -1;//关闭进路
        JZ_FLAG = false;
        this->view_lb->state = 1;
        this->state = 20;
    }else{
        if(JZ_FLAG){
            //JC
            this->view_lb->state = 1;
            if(jl_type==1){
                this->state = 30;
            }else if(jl_type==2){
                this->state = 40;
            }else{
                this->state = 21;//下一个区段码有区别根据进路方式 21/31/41
            }

        }else{
            //B
            //qDebug()<<"jl close!"<<endl;
            jl_type = -1;//未开放
            this->view_lb->state = 20;
            this->state = 20;
        }
    }
    emit sendJzState(YD_FLAG?3:jl_type);
}

void logic_lb::CzState(){
    if(this->train_flag==true){
        this->view_lb->state = nxt_state;

        jl_type = -1;//关闭进路
        CZ_FLAG = false;
        this->state = 0;
        emit closeGUDAO();
    }else{
        if(CZ_FLAG){
            this->state = nxt_state;
            this->view_lb->state = nxt_state;

        }else{
            this->state = 0;
            this->view_lb->state = 20;//B
        }
    }
    emit sendCzState(YD_FLAG?100:state,jl_type);
}

void logic_lb::toCloseGUDAO(){
    this->state = 1;
    this->view_lb->state = 1;
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
    case 3:{
        if(x>this->pos_x && x <this->pos_x+395 && y<30 && y >(20-360)){
            flag = true;
        }
        if(x>this->pos_x-180 && x<this->pos_x+395 && y<(30-180) && y>(20-360)){
            flag = true;
        }
        break;
    }
    case 4:{
        if(x>this->pos_x && x <this->pos_x+395 && y<30 && y >(20-360)){
            flag = true;
        }
        if(x>this->pos_x && x<this->pos_x+575 && y<(30-200) && y>(20-360)){
            flag = true;
        }
        break;
    }
    default: break;
    }
    return flag;
}
