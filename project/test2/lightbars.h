#ifndef LIGHTBARS_H
#define LIGHTBARS_H
#include <QGraphicsItem>
#include "setting.h"

class lightbars : public QGraphicsItem
{
public:
    lightbars(const int& _pos_x = 0,const int &_pos_y = 0,const int &_bar_width = 200,const int &_type = 0,const int &_logic_type = 0);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    int usedFlag = false;
    int state = 9;

private:
    qreal speed;
    qreal mouseEyeDirection;
    int pos_x;
    int pos_y = 140;
    int bar_width = 200;
    int bar_height = 10;
    int angle;
    //bounding rect parameters
    int bound_x;
    int bound_y;
    int bias = 0;
    int type;//0,1,2,3,4
    int logic_type;
    QColor color;
    QPoint text_pos;

    bool JZ_FLAG = false;
    bool CZ_FLAG = false;


    int lst_state = state;
    //TODO ADD AN INDEX FOR LIGHTSBAR
    void rotateAndPaintRect(QPainter *painter, const QRect &rect, int angle);
};

#endif // LIGHTBARS_H
