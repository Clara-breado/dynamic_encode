#include "train.h"
#include <QDebug>
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsScene>

train::train(const int& _pos_x):pos_x(_pos_x)
{
   qDebug()<<"my train borned"<<endl;
   setY(pos_y);
   setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
}

//! [1]
QRectF train::boundingRect() const
{
    qreal adjust = 0.5;
//    return QRectF(pos_x-adjust,pos_y-adjust,
//           36+adjust,65+adjust);
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 65 + adjust);
}
//! [1]

//! [3]
void train::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)



    painter->setBrush(Qt::yellow);
    painter->drawRect(QRectF(-10,20,40,25));

    QPixmap img1;
    painter->drawPixmap(-10,-20,40,25,img1);

//    // Body
//    painter->setBrush(color);
//    painter->drawEllipse(-10, -20, 20, 40);

//    // Eyes
//    painter->setBrush(Qt::white);
//    painter->drawEllipse(-10, -17, 8, 8);
//    painter->drawEllipse(2, -17, 8, 8);

//    // Nose
//    painter->setBrush(Qt::black);
//    painter->drawEllipse(QRectF(-2, -22, 4, 4));

//    // Pupils
//    painter->drawEllipse(QRectF(-8.0 + mouseEyeDirection, -17, 4, 4));
//    painter->drawEllipse(QRectF(4.0 + mouseEyeDirection, -17, 4, 4));

//    // Ears
//    painter->setBrush(scene()->collidingItems(this).isEmpty() ? Qt::green : Qt::red);
//    if(scene()->collidingItems(this).isEmpty()){
//        //no collid
//        painter->setBrush(Qt::darkBlue);
//    }else if(scene()->collidingItems(this).size()==1){
//        painter->setBrush(Qt::green);
//    }else if(scene()->collidingItems(this).size()==2){
//        painter->setBrush(Qt::red);
//    }else if(scene()->collidingItems(this).size()==3){
//        painter->setBrush(Qt::white);
//    }
//    //scene()->collidingItems(this).size()>2;
//    painter->drawEllipse(-17, -12, 16, 16);
//    painter->drawEllipse(1, -12, 16, 16);

//    // Tail
//    QPainterPath path(QPointF(0, 20));
//    path.cubicTo(-5, 22, -5, 22, 0, 25);
//    path.cubicTo(5, 27, 5, 32, 0, 30);
//    path.cubicTo(-5, 32, -5, 42, 0, 35);
//    painter->setBrush(Qt::NoBrush);
//    painter->drawPath(path);

    //bouding rect
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(Qt::black,1,Qt::DotLine,Qt::SquareCap,Qt::MiterJoin));
    painter->drawRect(boundingRect());
}
//! [3]

void train::advance(int phase){
    if(!phase) return;
    pos_x += 1;
    //setPos(pos_x,pos_y);

    setX(this->pos().x()+1);
    //timeLine->start();
}
