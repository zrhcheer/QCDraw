#include "serialcapacitorgraphic.h"

const QString SerialCapacitorGraphic::_devName = CodeConvertor::fromLocal("´®ÁªµçÈÝÆ÷");
SerialCapacitorGraphic::SerialCapacitorGraphic()
{
    setType(Graphic::GRAPHIC_SERIALCAPACITOR);
    this->setColor(QColor(255,0,0));
    this->setDirect(Graphic::POS_UP);
    _portPoints.resize(2);
}

QPointF  SerialCapacitorGraphic::getPortPos(int pos)
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

void SerialCapacitorGraphic::loadPortPos()
{
    float halfHeight = _size.height() / 2.0;
    switch(this->getDirect())
    {
    case POS_UP:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(0, -halfHeight));
        _portPoints[Graphic::JOIN_END].setJoinPoint(QPointF(0, halfHeight));
        return;
    case POS_RIGHT:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(halfHeight,0));
        _portPoints[Graphic::JOIN_END].setJoinPoint(QPointF(-halfHeight, 0));
        return;
    case POS_DOWN:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(0, halfHeight));
        _portPoints[Graphic::JOIN_END].setJoinPoint(QPointF(0, -halfHeight));
        return;
    case POS_LEFT:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(-halfHeight,0));
        _portPoints[Graphic::JOIN_END].setJoinPoint(QPointF(halfHeight, 0));
        return;
    }
    GraphicBase::loadPortPos();
}

void SerialCapacitorGraphic::prepareGraphic(QPainter *painter)
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

void SerialCapacitorGraphic::drawGraphic(QPainter *painter)
{
    float square =  _size.height() / 3;
    painter->drawLine(0, - _size.height() / 2,
                      0,-square / 2);
    painter->drawLine(-square / 2,-square / 2,square / 2,-square / 2);
    painter->drawLine(-square / 2,square / 2,square / 2,square / 2);
    painter->drawLine(0, _size.height() / 2,
                      0, square/ 2);
}
