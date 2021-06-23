#include "myscene.h"

myscene::myscene(QObject *parent) :
    QGraphicsScene(parent)
{
    clearFocus();
}

void myscene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("*********MyScene::mousePressEvent***************");
    QGraphicsScene::mousePressEvent(event);

//    // 如果是鼠标左键按下
//    if(event->button() == Qt::LeftButton)
//    {
//        QGraphicsScene::mousePressEvent(event);//这个函数没多大用，因为已经检测到鼠标左键按下事件了
//        qDebug()<<"mousePressEvent LeftButton" << event->scenePos().x() << event->scenePos().y();//鼠标的坐标点。注意用scenePos（）
//    }
//    // 如果是鼠标右键按下
//    else if(event->button() == Qt::RightButton)
//    {
//        qDebug()<<"mousePressEvent RightButton" << event->scenePos().x() << event->scenePos().y();
//        QGraphicsScene::mousePressEvent(event);//
//    }

}
