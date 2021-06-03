#ifndef TRAIN_H
#define TRAIN_H

#include <QGraphicsItem>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
class train : public QGraphicsItem
{
public:
    train(const int& _pos_x = 0);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QTimeLine *timeLine = new QTimeLine(1000);

protected:
    void advance(int phase) override;
private:
    qreal angle;
    qreal speed;
    qreal mouseEyeDirection;
    int pos_x;
    int pos_y = 100;
    int car_width = 110;
    int car_height = 60;
    QColor color;

};

#endif // TRAIN_H
