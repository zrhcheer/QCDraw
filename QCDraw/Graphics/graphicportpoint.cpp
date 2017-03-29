#include "graphicportpoint.h"

#include "graphic.h"

void GraphicPortPoint::setJoinPoint(const QPointF& joinPoint)
{
    _joinPoint = joinPoint;
    if(_anchor)
    {
        _anchor->setPos(joinPoint);
    }
}
void GraphicPortPoint::showAnchor(Graphic* parent,int selPos)
{
    if(!_anchor)
    {
        QGraphicsItem* parentItem = dynamic_cast<QGraphicsItem*>(parent);
        bool bBig = false;
        if(parent->isLine())
        {
            bBig = true;
        }
        _anchor = new AnchorGraphic(bBig,parentItem);
        _anchor->setPos(parent->getPortPos(selPos));
    }
    else
    {
        if(parent->isLine())
        {
            _anchor->setPos(parent->getPortPos(selPos));
        }
    }
    _anchor->show();
}
