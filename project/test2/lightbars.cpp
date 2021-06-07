#include "lightbars.h"
#include <QDebug>
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsScene>

lightbars::lightbars(const int& _pos_x):pos_x(_pos_x)
{
    qDebug()<<"lightbars borned"<<endl;
    bound_x = pos_x;
    bound_y = pos_y;
}

QRectF lightbars::boundingRect() const
{
    qreal adjust = 0.5;
//    return QRectF(-18 - adjust, -22 - adjust,
//                  36 + adjust, 60 + adjust);
    return  QRectF(bound_x,pos_y-22,bar_width,bar_height);

}

void lightbars::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    bias = 0;
    bound_x = pos_x+bias*bar_width;
    if(scene()->collidingItems(this).size()>=3){
        color = Qt::red;
        this->usedFlag = true;
    }else{
        this->usedFlag = false;
        bias++;
        bound_x = pos_x+200;
        if(scene()->collidingItems(this).size()>=2){
            color.setRgb(255,180,0);
        }else{
//            bias++;
//            bound_x = pos_x+400;
//            if(scene()->collidingItems(this).size()>=2){
//                color.setRgb(255,255,0);
//            }else{
                color.setRgb(0,255,0);
//            }

        }
    }
    painter->setBrush(color);                                           
    painter->drawRect(pos_x,pos_y,bar_width-2,bar_height);
    painter->setBrush(color);
    painter->drawRect(pos_x,pos_y,bar_width-2,bar_height);

//    //bouding rect
//    painter->setPen(QPen(Qt::white,1,Qt::DotLine,Qt::SquareCap,Qt::MiterJoin));
//    painter->drawRect(bound_x,pos_y+25,bar_width,bar_height);
}

//void lightbars::lbSet(int _state){
//    this->state = _state;
//    qDebug()<<"change state"<<endl;
//}

