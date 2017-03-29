#include "reactorgraphic.h"

const QString ReactorGraphic::_devName = CodeConvertor::fromLocal("µç¿¹Æ÷");

ReactorGraphic::ReactorGraphic()
{
    setType(Graphic::GRAPHIC_REACTOR);
    this->setColor(QColor(22,149,19));
    this->setDirect(Graphic::POS_UP);
    _portPoints.resize(2);
}
QPointF  ReactorGraphic::getPortPos(int pos)
{
    switch(pos)
    {
    case Graphic::JOIN_BEGIN:
        return _portPoints[Graphic::JOIN_BEGIN].getJoinPoint();
        break;
    case Graphic::JOIN_END:
        return _portPoints[Graphic::JOIN_END].getJoinPoint();
        break;
    }
    return QPointF(0,0);
}

void ReactorGraphic::loadPortPos()
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
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(0,halfHeight));
        _portPoints[Graphic::JOIN_END].setJoinPoint(QPointF(0, -halfHeight));
        return;
    case POS_LEFT:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(-halfHeight,0));
        _portPoints[Graphic::JOIN_END].setJoinPoint(QPointF(halfHeight, 0));
        return;
    }
    GraphicBase::loadPortPos();
}
void ReactorGraphic::prepareGraphic(QPainter *painter)
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

void ReactorGraphic::drawGraphic(QPainter *painter)
{
    double radius = _size.height()  / 4;


    painter->setBrush(Qt::NoBrush);
    painter->setPen(this->getColor());
    painter->drawLine(0, - _size.height() / 2,
                      0,-radius);

    painter->drawArc(-radius,-radius,
                     radius * 2,radius* 2,
                     90 * 16,270 * 16);

    painter->drawLine(0,0,radius,0);
    painter->drawLine(0,0,
                      0,  _size.height() / 2);
}
