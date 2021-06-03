#include "lights.h"
#include <QDebug>
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsScene>

lights::lights(const int& _pos_x):pos_x(_pos_x)
{
    qDebug()<<"lightbars borned"<<endl;
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
    painter->setPen(QPen(Qt::black,1,Qt::DotLine,Qt::SquareCap,Qt::MiterJoin));
    painter->drawRect(QRectF(pos_x,pos_y,40,30));

    painter->setBrush(Qt::green);
    painter->drawEllipse(pos_x,pos_y,20,20);
    painter->setBrush(Qt::green);
    painter->drawEllipse(pos_x+20,pos_y,20,20);

    painter->setBrush(Qt::black);
    painter->drawLine(QPoint(pos_x,pos_y),QPoint(pos_x,pos_y+30));




}
