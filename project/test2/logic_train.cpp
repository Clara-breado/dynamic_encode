#include "logic_train.h"

logic_train::logic_train(QObject *parent,int _pox_x,int _pos_y) : QObject(parent),pos_x(_pox_x),pos_y(_pos_y)
{
    view_train = new train(pos_x,pos_y);
}

void logic_train::enterQD(){
    emit sendPos(this->view_train->x(),this->view_train->y());
}

void logic_train::timerStart(){
    enterQD();
}
