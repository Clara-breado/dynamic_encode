#include "logic_lb.h"
#include <QDebug>

logic_lb::logic_lb(QObject *parent,int _pos) : QObject(parent)
{
    pos = _pos;
    view_lb = new lightbars(pos);
}

void logic_lb::getState(){
    if(this->view_lb->usedFlag==true){
        this->state = 0;
        emit stateChanged(this->state);
        qDebug()<<"used"<<endl;
    }
}

void logic_lb::toChangestate(int _nxtstate){
    this->state = _nxtstate +1;
    this->view_lb->state = this->state;
    qDebug()<<this->state<<endl;
}

void logic_lb::timerTest(){
    getState();
//    qDebug()<<this->state<<endl;

}
