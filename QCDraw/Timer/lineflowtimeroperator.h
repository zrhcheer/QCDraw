#ifndef LINEFLOWTIMEROPERATOR_H
#define LINEFLOWTIMEROPERATOR_H

#include <map>
#include "timeoperator.h"
#include "Graphics/linegraphic.h"

struct LineFlowG
{
    LineGraphic* line;
    bool bBegin;
    float percent;
};

class LineFlowTimerOperator : public TimeOperator
{
public:
    enum
    {
        FLOW_BEGIN,
        FLOW_END
    };
    LineFlowTimerOperator();

    virtual void doTimer();
    virtual bool isStop()
    {
        return false;
    }
    virtual bool isEmpty()
    {
        return _mapLine.empty();
    }

    void addFlow(const LineFlowG& lineFlow);
    void clearFlow();


private:
    map<LineGraphic*,map<int,LineFlow*> > _mapLine;
    QColor _clrFlow;
};

#endif // LINEFLOWTIMEROPERATOR_H
