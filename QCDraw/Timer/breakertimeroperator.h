#ifndef BREAKERTIMEROPERATOR_H
#define BREAKERTIMEROPERATOR_H

#include "timeoperator.h"
#include "Graphics/graphic.h"
#include <set>

class BreakerTimerOperator : public TimeOperator
{
public:
    BreakerTimerOperator();
    virtual void doTimer();
    virtual bool isStop()
    {
        return false;
    }
    virtual bool isEmpty()
    {
        return _timerObj.empty();
    }

    void clearTimerObj()
    {
        _timerObj.clear();
    }
    void addTimerObj(Graphic* graphic)
    {
        _timerObj.insert(graphic);
    }
    void setTimerObj(set<Graphic*>& timerObj)
    {
        _timerObj = timerObj;
    }
    bool isTimerObjEmpty()
    {
        return _timerObj.empty();
    }

private:
    set<Graphic*> _timerObj;
    bool _bClrA;
    bool _bTick;
    QColor _lightClr;
    QColor _darkClr;
};

#endif // BREAKERTIMEROPERATOR_H
