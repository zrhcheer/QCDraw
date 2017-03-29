#include "shuntcapacitorgraphic.h"
#include <QPainter>

const QString ShuntCapacitorGraphic::_devName = CodeConvertor::fromLocal("²¢ÁªµçÈÝÆ÷");

ShuntCapacitorGraphic::ShuntCapacitorGraphic()
{
    setType(Graphic::GRAPHIC_SHUNTCAPACITOR);
    this->setColor(QColor(22,149,19));
    _bOpen = true;
    this->setDirect(Graphic::POS_UP);
    _portPoints.resize(1);
}
void ShuntCapacitorGraphic::setSize(const int &height)
{
    if(height < ELE_MIN_SIZE)
    {
        _size.setHeight(ELE_MIN_SIZE);
    }
    else
    {
        _size.setHeight(height);
    }
    _size.setWidth(height * 2 / 3);
}
QPointF ShuntCapacitorGraphic::getPortPos(int pos)
{
    switch(pos)
    {
    case Graphic::JOIN_BEGIN:
        return _portPoints[Graphic::JOIN_BEGIN].getJoinPoint();
        break;
   default:
        assert(false);
        break;
    }
}

void ShuntCapacitorGraphic::loadPortPos()
{
    float halfHeight = _size.height() / 2.0;
    switch(this->getDirect())
    {
    case POS_UP:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(0, -halfHeight));
        return;
    case POS_RIGHT:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(halfHeight,0));
        return;
    case POS_DOWN:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(0, halfHeight));
        return;
    case POS_LEFT:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(-halfHeight,0));
        return;
    }
}

void ShuntCapacitorGraphic::prepareGraphic(QPainter *painter)
{
    GraphicBase::prepareGraphic(painter);
    switch(this->getDirect())
    {
    case POS_UP:
        break;
    case POS_RIGHT:
        painter->rotate(90);
        break;
    case POS_DOWN:
        painter->rotate(180);
        break;
    case POS_LEFT:
        painter->rotate(270);
        break;
    }
}

void ShuntCapacitorGraphic::drawGraphic(QPainter *painter)
{
    float radius = _size.height()  / 3;
    painter->drawLine(0, -_size.height() / 2,
                      0, - radius / 2);
    painter->setBrush(Qt::NoBrush);
    painter->drawEllipse(QPointF( 0, radius / 2),radius ,radius );

    painter->drawLine(-radius / 2 , radius / 2 - radius / 2,
                      -radius / 2 ,  radius / 2 + radius / 2);
    painter->drawLine(radius / 2 , radius / 2 - radius / 2,
                      radius / 2 ,  radius / 2 + radius / 2);
}
















