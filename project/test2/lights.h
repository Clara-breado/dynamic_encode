#ifndef LIGHTS_H
#define LIGHTS_H
#include <QGraphicsItem>

class lights : public QGraphicsItem
{
public:
    lights(const int& _pos_x = 0,const int &_pos_y = 110,const int &_light_type = 0,const int &_light_dir = 0);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    int mz;

//    /*接口函数：修改信号机状态-->修改两个灯颜色*/
//    void modiState(int state);
protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    qreal angle;
    qreal speed;
    qreal mouseEyeDirection;
    int pos_x;
    int pos_y = 110;
    int light_type = 0;//0,1,2
    int light_dir = 0;//0,1
    int stick_bias = 0;

    QColor l;
    QColor r;

//    用宏定义来统一
//    int state;
//    int l_left;
//    int l_right;

//    int bar_width = 200;
//    int bar_height = 20;
    QColor color;
};
#endif // LIGHTS_H
