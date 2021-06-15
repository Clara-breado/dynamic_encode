#include "logic_train.h"

logic_train::logic_train(QObject *parent,int _pox_x,int _pos_y) : QObject(parent),pos_x(_pox_x),pos_y(_pos_y)
{
    view_train = new train(pos_x,pos_y);
}

void logic_train::enterQD(){
    pos_x = this->view_train->pos_x;
    int x = this->view_train->mapToScene(this->view_train->pos().x(),this->view_train->pos().y()).x();
    int y = this->view_train->mapToScene(this->view_train->pos().x(),this->view_train->pos().y()).y();

    emit sendPos(this->view_train->pos().x(),this->view_train->pos().y());
    emit sendPoint(this->view_train->pos());
    //emit sendPos(this->view_train->x(),this->view_train->y());
}

void logic_train::timerStart(){
    enterQD();
}
