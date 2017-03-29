#include "groundreactorgraphic.h"

const QString GroundReactorGraphic::_devName = CodeConvertor::fromLocal("½ÓµØµç¿¹Æ÷");

GroundReactorGraphic::GroundReactorGraphic()
{
    earthGraphic = NULL;
    setType(Graphic::GRAPHIC_GROUNDREACTOR);
}
QPointF  GroundReactorGraphic::getPortPos(int pos)
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

void GroundReactorGraphic::loadPortPos()
{
    ReactorGraphic::loadPortPos();
    if(!earthGraphic)
    {
        earthGraphic = new EarthGraphic(this);
    }
    earthGraphic->setSize(_size.width() );
    earthGraphic->setDirect(this->getDirect());
    earthGraphic->setColor(_color);
    earthGraphic->setPos(_portPoints[Graphic::JOIN_END].getJoinPoint());
    earthGraphic->loadPortPos();
}
