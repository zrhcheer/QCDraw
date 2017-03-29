#include "switchgraphic.h"

SwitchGraphic::SwitchGraphic()
{
}


QPointF  SwitchGraphic::getPortPos(int pos)
{
    switch(pos)
    {
    case Graphic::JOIN_BEGIN:
        return _portPoints[Graphic::JOIN_BEGIN].getJoinPoint();
        break;
    case Graphic::JOIN_END:
        return _portPoints[Graphic::JOIN_END].getJoinPoint();
        break;
    default:
        assert(false);
        break;
    }
}
