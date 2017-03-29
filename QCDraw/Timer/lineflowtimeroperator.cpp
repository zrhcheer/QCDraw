#include "lineflowtimeroperator.h"

LineFlowTimerOperator::LineFlowTimerOperator()
{
    _clrFlow =  QColor(0,200,0);
}
void LineFlowTimerOperator::doTimer()
{
    for(map<LineGraphic*,map<int,LineFlow*> >::iterator iterLine = _mapLine.begin();
        iterLine != _mapLine.end(); ++iterLine)
    {
        map<int,LineFlow*>& flowMap = iterLine->second;
        for(map<int,LineFlow*>::iterator iterFlow = flowMap.begin();
            iterFlow != flowMap.end(); ++iterFlow)
        {
            LineFlow* flow = iterFlow->second;
            flow->moveFlow();
        }
    }
}

void LineFlowTimerOperator::addFlow(const LineFlowG& lineFlow)
{
    map<int,LineFlow*>& flowMap = _mapLine[lineFlow.line];
    int pos = lineFlow.bBegin? FLOW_BEGIN : FLOW_END;

    int beginPer = 0;
    int endPer = 100;
    switch(pos)
    {
    case FLOW_BEGIN:
        beginPer = 0;
        endPer = lineFlow.percent * 100;
        if(endPer > 100)
        {
            endPer = 100;
        }
        break;
    case FLOW_END:
        beginPer = 100;
        endPer = (1 - lineFlow.percent) * 100;
        if(endPer < 0)
        {
            endPer = 0;
        }
        break;
    }

    map<int,LineFlow*>::iterator iterFlow = flowMap.find(pos);
    if(iterFlow != flowMap.end())
    {
        LineFlow* tmpFlow = iterFlow->second;
        tmpFlow->initMove(beginPer,endPer,1,_clrFlow);
    }
    else
    {
        LineFlow* tmpFlow = lineFlow.line->addMove(beginPer,endPer,1,_clrFlow);
        flowMap.insert(make_pair(pos,tmpFlow));
    }
}

void LineFlowTimerOperator::clearFlow()
{
    for(map<LineGraphic*,map<int,LineFlow*> >::iterator iterLine = _mapLine.begin();
        iterLine != _mapLine.end(); ++iterLine)
    {
        LineGraphic* lineGraphic = iterLine->first;
        map<int,LineFlow*>& flowMap = iterLine->second;
        for(map<int,LineFlow*>::iterator iterFlow = flowMap.begin();
            iterFlow != flowMap.end(); ++iterFlow)
        {
            LineFlow* flow = iterFlow->second;
            lineGraphic->delMove(flow);
        }
        _mapLine.erase(iterLine);
    }
}
