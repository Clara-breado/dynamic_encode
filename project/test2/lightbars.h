#ifndef LIGHTBARS_H
#define LIGHTBARS_H
#include <QGraphicsItem>
#include "setting.h"

class lightbars : public QGraphicsItem
{
//    Q_OBJECT
public:
    lightbars(const int& _pos_x = 0);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    int usedFlag = false;
    int state = THREE_FREE;
//public slots:
//    void lbSet(int _state);

//signals:
//    void lbChange(int _state);

protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    qreal angle;
    qreal speed;
    qreal mouseEyeDirection;
    int pos_x;
    int pos_y = 140;
    int bar_width = 200;
    int bar_height = 20;

    //bounding rect parameters
    int bound_x;
    int bound_y;
    int bias = 0;
    QColor color;


    int lst_state = state;
    //TODO ADD AN INDEX FOR LIGHTSBAR
};

#endif // LIGHTBARS_H
