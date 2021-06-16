#ifndef LOGIC_LIGHT_H
#define LOGIC_LIGHT_H

#include <QObject>
#include "lights.h"

class logic_light : public QObject
{
    Q_OBJECT
public:
    explicit logic_light(QObject *parent = nullptr,const int& _pos_x = 0,const int &_pos_y = 110,const int &_light_type = 0,const int &_light_dir = 0);
    lights *view_lt;
//signals:

public slots:
    void JM(int _mz);
    void JzJM(int _mz);
    void CzJM(int _mz,int _jl);

private:
    int pos_x;
    int pos_y;
    int light_type;
    int mz;
};

#endif // LOGIC_LIGHT_H
