#include "grounddisconnectorgraphic.h"

const QString GroundDisconnectorGraphic::_devName = CodeConvertor::fromLocal("½ÓµØµ¶Õ¢");

GroundDisconnectorGraphic::GroundDisconnectorGraphic()
{
    earthGraphic = NULL;
    setType(Graphic::GRAPHIC_GROUNDDISCONNECTOR);
}
QPointF  GroundDisconnectorGraphic::getPortPos(int pos)
{
    switch(pos)
    {
    case Graphic::JOIN_BEGIN:
        return _portPoints[Graphic::JOIN_BEGIN].getJoinPoint();
        break;
    case Graphic::JOIN_END:
    default:
        assert(false);
        break;
    }
    return QPointF(0,0);
}
void GroundDisconnectorGraphic::loadPortPos()
{
    DisconnectorGraphic::loadPortPos();
    if(!earthGraphic)
    {
        earthGraphic = new EarthGraphic(this);
    }
    earthGraphic->setSize(_size.width());
    earthGraphic->setDirect(this->getDirect());
    earthGraphic->setColor(_color);
    earthGraphic->setPos(_portPoints[Graphic::JOIN_END].getJoinPoint());
    earthGraphic->loadPortPos();
}



