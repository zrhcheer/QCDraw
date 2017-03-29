#ifndef STATIONTIMEROPERATOR_H
#define STATIONTIMEROPERATOR_H

#include "timeoperator.h"
#include "Graphics/stationgraphic.h"
#include <set>
#include <QColor>

struct CrossDirect
{
    CrossDirect(bool crossBegin,bool crossEnd)
    {
        _crossBegin = crossBegin;
        _crossEnd = crossEnd;
        _crossBeginFirst = true;
        _crossEndFirst = true;
    }

    bool _crossBegin;
    bool _crossEnd;

    bool _crossBeginFirst;
    bool _crossEndFirst;

};

class StationTimerOperator : public TimeOperator
{
public:
    StationTimerOperator();
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
    void addTimerObj(Graphic* graphic,bool crossBegin,bool crossEnd);
    void setTimerObj(map<Graphic*,CrossDirect>& timerObj)
    {
        _timerObj = timerObj;
    }

private:
    map<Graphic*,CrossDirect> _timerObj;
    bool _bClrA;
    QColor _lightClr;
    QColor _darkClr;
};

#endif // STATIONTIMEROPERATOR_H
