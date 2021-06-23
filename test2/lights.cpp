#include "lights.h"
#include <QDebug>
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsScene>

lights::lights(const int& _pos_x,const int &_pos_y,const int &_light_type,const int &_light_dir):pos_x(_pos_x),pos_y(_pos_y),light_type(_light_type),light_dir(_light_dir)
{   
    if(light_dir==0){
        stick_bias = 40;
    }
}

QRectF lights::boundingRect() const
{
    qreal adjust = 0.5;
//    return QRectF(-18 - adjust, -22 - adjust,
//                  36 + adjust, 60 + adjust);
    return  QRectF(pos_x,pos_y,40,30);

}

void lights::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    //bouding rect
//    painter->setPen(QPen(Qt::black,1,Qt::DotLine,Qt::SquareCap,Qt::MiterJoin));
//    painter->drawRect(QRectF(pos_x,pos_y,40,30));


    l = Qt::gray;
    r = Qt::gray;

    painter->setPen(Qt::white);

    if(this->light_type==0){
        switch (this->mz-1) {
        case 0:{
            l = Qt::red;
            r = Qt::black;
            break;
        }
        case 1:{
            l = Qt::yellow;
            r = Qt::black;
            break;
        }
        case 2:{
            l = Qt::green;
            r = Qt::yellow;
            break;
        }
        case 30:{
            l = Qt::yellow;
            r = Qt::black;
            break;
        }
        case 31:{
            l = Qt::yellow;
            r = Qt::black;
            break;
        }
        case 40:{
            l = Qt::yellow;
            r = Qt::black;
            break;
        }
        case 41:{
            l = Qt::yellow;
            r = Qt::black;
            break;
        }
        default:{
            l = Qt::green;
            r = Qt::black;
        }
        }
    }else{
        switch (this->mz) {
        case 0:{
            l = Qt::red;
            r = Qt::black;
            break;
        }
        case 1:{
            l = Qt::yellow;
            r = Qt::black;
            break;
        }
        case 3:{
            //cx
            l = Qt::yellow;
            r = Qt::yellow;
            break;
        }
        case 4:{
            //18
            l = Qt::yellow;
            r = Qt::white;
            break;
        }
        case 5:{
            l = Qt::green;
            r = Qt::black;
            break;
        }
        case 6:{
            l = Qt::red;
            r = Qt::white;
            break;
        }
        default:{
            l = Qt::red;
            r = Qt::black;
        }
        }

    }

    painter->setBrush(l);
    painter->drawEllipse(pos_x,pos_y,20,20);
    painter->setBrush(r);
    painter->drawEllipse(pos_x+20,pos_y,20,20);

    painter->setBrush(Qt::black);
    //painter->drawLine(QPoint(pos_x+stick_bias,pos_y),QPoint(pos_x+stick_bias,pos_y+30));

    if(light_dir==1){
        painter->drawLine(QPoint(pos_x+stick_bias,pos_y),QPoint(pos_x+stick_bias,pos_y+30));
    }else{
        painter->drawLine(QPoint(pos_x+stick_bias,pos_y-10),QPoint(pos_x+stick_bias,pos_y+20));
    }


}
