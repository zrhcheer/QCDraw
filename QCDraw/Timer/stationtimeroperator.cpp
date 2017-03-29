#include "stationtimeroperator.h"
#include "Graphics/linegraphic.h"

StationTimerOperator::StationTimerOperator() :
    _lightClr(0,255,0),
    _darkClr(0,0,255)
{
    _bClrA = true;
}

void StationTimerOperator::addTimerObj(Graphic* graphic,bool crossBegin,bool crossEnd)
{
    map<Graphic*,CrossDirect> ::iterator iterObj = _timerObj.find(graphic);
    if(iterObj == _timerObj.end())
    {
        _timerObj.insert(make_pair(graphic,CrossDirect(crossBegin,crossEnd)));
    }
    else
    {
        CrossDirect& crossDirect = iterObj->second;
        if(crossBegin)
        {
            crossDirect._crossBegin = true;
        }
        if(crossEnd)
        {
            crossDirect._crossEnd = true;
        }
    }
}

void StationTimerOperator::doTimer()
{
    _bClrA = !_bClrA;
    QColor* tmpClr = NULL;
    if(_bClrA)
    {
        tmpClr = &_lightClr;
    }
    else
    {
        tmpClr = &_darkClr;
    }
    for(map<Graphic*,CrossDirect>::iterator iterGraphic = _timerObj.begin();
        iterGraphic != _timerObj.end(); ++iterGraphic)
    {
        Graphic* tmpLine = iterGraphic->first;
        CrossDirect& cross = iterGraphic->second;
        if(Graphic::GRAPHIC_LINE == tmpLine->getType())
        {
            LineGraphic* line = dynamic_cast<LineGraphic*>(tmpLine);
            if(cross._crossBegin)
            {
                if(cross._crossBeginFirst)
                {
                    cross._crossBeginFirst = false;
                    line->setLineBreak(Graphic::JOIN_BEGIN);
                }
                line->setLineBreakColor(Graphic::JOIN_BEGIN,*tmpClr);
            }
            if(cross._crossEnd)
            {
                if(cross._crossEndFirst)
                {
                    cross._crossEndFirst = false;
                    line->setLineBreak(Graphic::JOIN_END);
                }
                line->setLineBreakColor(Graphic::JOIN_END,*tmpClr);
            }
        }
    }
}
