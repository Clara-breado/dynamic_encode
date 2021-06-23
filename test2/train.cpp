#include "train.h"
#include <QDebug>
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsScene>

train::train(const int& _pos_x,const int& _pos_y):pos_x(_pos_x),pos_y(_pos_y)
{
//   setX(pos_x);
//   setY(pos_y);
   setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
}

//! [1]
QRectF train::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(pos_x-adjust,pos_y-adjust,
           40+adjust,25+adjust);
//    return QRectF(-18 - adjust, -22 - adjust,
//                  36 + adjust, 65 + adjust);
}
//! [1]

//! [3]
void train::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setBrush(Qt::yellow);
    painter->drawRect(pos_x,pos_y,40,25);


    //bouding rect
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::black,1,Qt::DotLine,Qt::SquareCap,Qt::MiterJoin));
    painter->drawRect(boundingRect());
}
//! [3]

void train::advance(int phase){
    if(!phase) return;
    //pos_x += 1;
    //setPos(pos_x,pos_y);

    //setX(pos_x);

    //setX(this->pos().x()+1);


    //test斜线

        qDebug()<<this->pos().x()<<endl;

//咽喉区2
//    if(this->pos().x()>=3280 && this->pos().x()<3450){
//        if(move_type == 2){
//            setX(this->pos().x()+0.7);
//            setY(this->pos().y()-0.7);
//        }else{
//            setX(this->pos().x()+1);
//        }
//    }else{
//        setX(this->pos().x()+1);
//    }

    switch (move_type) {
    case 0:{
        //0应该是禁止前进
        break;
    }
    case 1:{
        //正线
        setX(this->pos().x()+1);
        break;
    }
    case 2:{
        //侧线进站
        if((this->pos().x()>=3280 && this->pos().x()<3450)||(this->pos().x()>=280 && this->pos().x()<480)){
                setX(this->pos().x()+0.7);
                setY(this->pos().y()-0.7);
        }else{
            setX(this->pos().x()+1);
        }
        break;
    }
    case 3:{
        //18进站
        if((this->pos().x()>=3280 && this->pos().x()<3630)||(this->pos().x()>=280 && this->pos().x()<625)){
                setX(this->pos().x()+0.7);
                setY(this->pos().y()-0.7);
        }else{
            setX(this->pos().x()+1);
        }
        break;
    }
    case 4:{
        //正线
        setX(this->pos().x()+1);
        break;
    }
    case 5:{
        //侧线出站
        if(this->pos().x()>=910 && this->pos().x()<1080){
                setX(this->pos().x()+0.7);
                setY(this->pos().y()+0.7);
        }else{
            setX(this->pos().x()+1);
        }
        break;
    }
    case 6:{
        //18出站
        if(this->pos().x()>=740 && this->pos().x()<1080){
                setX(this->pos().x()+0.7);
                setY(this->pos().y()+0.7);
        }else{
            setX(this->pos().x()+1);
        }
        break;
    }
    default:{

    }
    }


//    if(move_type == 2){
//        setX(this->pos().x()+0.7);
//        setY(this->pos().y()-0.7);
//    }else{
//        setX(this->pos().x()+1);
//    }
}
