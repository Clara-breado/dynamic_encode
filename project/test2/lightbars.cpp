#include "lightbars.h"
#include <QDebug>
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsScene>

lightbars::lightbars(const int& _pos_x,const int &_pos_y,const int &_bar_width,const int &_type,const int &_logic_type):pos_x(_pos_x),pos_y(_pos_y),bar_width(_bar_width),type(_type),logic_type(_logic_type)
{
    bound_x = pos_x;
    bound_y = pos_y;
    text_pos = QPoint(pos_x+100,pos_y+40);
}

QRectF lightbars::boundingRect() const
{
    qreal adjust = 0.5;
//    return QRectF(-18 - adjust, -22 - adjust,
//                  36 + adjust, 60 + adjust);
    return  QRectF(bound_x,pos_y-10,bar_width,bar_height);

}

void lightbars::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

//    switch (this->logic_type) {
//        //区间
//    case 0:{
//        break;
//    }
//        //进站咽喉
//    case 1:{
//        if(JZ_FLAG){
//            break;
//        }else{
//            //B
//            this->state = 10;
//            break;
//        }
//    }
//        //股道
//    case 2:{
//        break;
//    }
//        //出站咽喉
//    case 3:{
//        if(CZ_FLAG){
//            break;
//        }else{
//            //B
//            this->state = 10;
//            break;
//        }
//    }
//    default:{
//        this->state = 10;
//    }
//    }





    switch (this->state) {
    case 0: {
                painter->drawText(text_pos,"H");
                color.setRgb(255,0,0);
                break;
            }
    case 1: {
                painter->drawText(text_pos,"HU");
                color.setRgb(255,69,0);
                break;
            }
    case 2: {
                painter->drawText(text_pos,"U");
                color.setRgb(255,255,0);
                break;
            }
    case 3: {
                painter->drawText(text_pos,"LU");
                color.setRgb(127,255,0);
                break;
            }
    case 4: {
                painter->drawText(text_pos,"L");
                color.setRgb(0,255,0);
                break;
            }
    case 5: {
                painter->drawText(text_pos,"L2");
                color.setRgb(0,238,0);
                break;
            }
    case 6: {
                painter->drawText(text_pos,"L3");
                color.setRgb(0,205,0);
                break;}
    case 7: {
                painter->drawText(text_pos,"L4");
                color.setRgb(0,139,0);
                break;
            }
    case 8: {
                painter->drawText(text_pos,"L5");
                color.setRgb(0,108,0);
                break;
            }

    case 10:{
            painter->drawText(text_pos,"B");
            color.setRgb(255,255,255);
            break;
    }
    default:{
                painter->drawText(text_pos,"L5");
                color.setRgb(0,108,0);
                break;
            }
    }


    switch(this->type){
    case 0:{
        painter->setBrush(color);
        painter->drawRect(pos_x,pos_y,bar_width-5,bar_height);
        break;
    }
    case 1:{
        angle = 45;
        painter->setBrush(color);
        painter->drawRect(pos_x,pos_y,bar_width-5,bar_height);

        QRect rect(pos_x-30,pos_y-90,200,bar_height);
        rotateAndPaintRect(painter, rect, angle);
        break;
    }
    case 2:{
        angle = 135;
        painter->setBrush(color);
        painter->drawRect(pos_x,pos_y,bar_width-5,bar_height);

        QRect rect(pos_x+160,pos_y-90,200,bar_height);
        rotateAndPaintRect(painter, rect, angle);
        break;
    }
    case 3:{
        angle = 45;
        painter->setBrush(color);

        painter->drawRect(pos_x,pos_y,bar_width-5,bar_height);

        painter->drawRect(pos_x+200,pos_y,bar_width-5,bar_height);

        QRect rect(pos_x-10,pos_y-90,226,bar_height);
        rotateAndPaintRect(painter, rect, angle);

        painter->drawRect(pos_x,pos_y-170,30,bar_height);

        QRect rect2(pos_x-180,pos_y-270,226,bar_height);
        rotateAndPaintRect(painter, rect2, angle);

        painter->drawRect(pos_x-165,pos_y-350,20,bar_height);

        break;
    }
    case 4:{
        angle = 135;
        painter->setBrush(color);

        painter->drawRect(pos_x,pos_y,bar_width-5,bar_height);

        painter->drawRect(pos_x+200,pos_y,bar_width-5,bar_height);

        QRect rect(pos_x+190,pos_y-90,226,bar_height);
        rotateAndPaintRect(painter, rect, angle);

        painter->drawRect(pos_x+380,pos_y-170,30,bar_height);

        QRect rect2(pos_x+370,pos_y-270,226,bar_height);
        rotateAndPaintRect(painter, rect2, angle);

        painter->drawRect(pos_x+560,pos_y-350,20,bar_height);

        break;
    }
    default:{
        painter->drawRect(pos_x,pos_y,bar_width,bar_height);
    }
    }

//    QRect rect(pos_x,pos_y,bar_width,bar_height);
//    painter->setBrush(color);

//    rotateAndPaintRect(painter, rect, angle);

}

void lightbars::rotateAndPaintRect(QPainter *painter, const QRect &rect, int angle){
    QRect rotatedRect(-rect.width()/2, -rect.height()/2, rect.width(), rect.height());
        int cx = rect.x() + rect.width() / 2;
        int cy = rect.y() + rect.height() / 2;

        painter->save();
        painter->translate(cx, cy);
        painter->rotate(angle);
        painter->drawRect(rotatedRect);
        painter->restore();
}



