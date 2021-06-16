#include "logic_light.h"

logic_light::logic_light(QObject *parent,const int& _pos_x,const int &_pos_y,const int &_light_type,const int &_light_dir) : QObject(parent),pos_x(_pos_x),pos_y(_pos_y),light_type(_light_type)
{
    view_lt = new lights(_pos_x,_pos_y,_light_type,_light_dir);
}

void logic_light::JM(int _mz){
    this->mz = _mz+1;
    this->view_lt->mz = this->mz;
}

void logic_light::JzJM(int _mz){
    //_mz = -1/0/2/3
    switch (_mz) {
    case 0:{
        //zx
        this->view_lt->mz = 1;
        break;
    }
    case 1:{
        //cx
        this->view_lt->mz = 3;
        break;
    }
    case 2:{
        //18
        this->view_lt->mz = 4;
        break;
    }
    default:{
        this->view_lt->mz = 0;
    }
    }
}

void logic_light::CzJM(int _mz,int _jl){
    //L/H
    if(_jl==-1) this->view_lt->mz = 0;
    if(_jl==this->light_type){
        if(_mz==0){
            this->view_lt->mz = 0;
        }else{
            this->view_lt->mz = 5;
        }
    }

}
