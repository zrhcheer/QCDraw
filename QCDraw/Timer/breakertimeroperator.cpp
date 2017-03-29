#include "breakertimeroperator.h"
#include "Graphics/breakergraphic.h"
#include "Graphics/disconnectorgraphic.h"

BreakerTimerOperator::BreakerTimerOperator() :
    _lightClr(0,255,0),
    _darkClr(0,0,255)
{
     _bClrA = true;
     _bTick = false;
}

void BreakerTimerOperator::doTimer()
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

    for(set<Graphic*>::iterator iterObj = _timerObj.begin();
        iterObj != _timerObj.end(); ++iterObj)
    {
        Graphic* tmpGraphc = *iterObj;

        switch(tmpGraphc->getType())
        {
        case Graphic::GRAPHIC_BREAKER:
        case Graphic::GRAPHIC_DISCONNECTOR:
        case Graphic::GRAPHIC_GROUNDDISCONNECTOR:
        {
            GraphicBase* base = dynamic_cast<GraphicBase*>(tmpGraphc);
            if(!_bTick)
            {
                base->setTick(true);
            }
            base->setTickColor(*tmpClr);
            base->update();
        }
            break;
        }
    }
    _bTick = true;
}




