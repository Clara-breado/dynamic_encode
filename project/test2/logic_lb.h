#ifndef LOGIC_LB_H
#define LOGIC_LB_H

#include <QObject>
#include "lightbars.h"
class logic_lb : public QObject
{
    Q_OBJECT
public:
    explicit logic_lb(QObject *parent = nullptr,int _pos = 0);
    lightbars *view_lb;
    void getState();

signals:
    void stateChanged(int _state);

public slots:
    void toChangestate(int _nxtstate);
    void timerTest();
private:
    int id;
    int pos;
    int state;

};

#endif // LOGIC_LB_H
