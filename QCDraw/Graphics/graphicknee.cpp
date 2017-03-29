#include "graphicknee.h"
#include "graphic.h"
GraphicKnee::GraphicKnee()
{
    _kneeType = KNEE_UNKNOW;
    _kneeIndex = -1;
    _beginLine = NULL;
    _endLine = NULL;
}

bool GraphicKnee::isJointed(int& selPos)
{
    if(KNEE_JOIN == _kneeType)
    {
        if(!_beginLine)
        {
            selPos = Graphic::JOIN_BEGIN;
            return true;
        }
        else if(!_endLine)
        {
            selPos = Graphic::JOIN_END;
            return true;
        }
    }
    return false;
}
