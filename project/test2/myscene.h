#ifndef MYSCENE_H
#define MYSCENE_H


#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPaintEvent>
#include <QKeyEvent>

class myscene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit myscene(QObject *parent = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:

public slots:

};

#endif // MYSCENE_H
