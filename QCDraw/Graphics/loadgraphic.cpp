#include "loadgraphic.h"

const QString LoadGraphic::_devName = CodeConvertor::fromLocal("¸ººÉ");

LoadGraphic::LoadGraphic()
{
    setType(Graphic::GRAPHIC_LOAD);
    this->setColor(QColor(255,0,0));
    this->setDirect(Graphic::POS_UP);
    _portPoints.resize(1);
}

QPointF  LoadGraphic::getPortPos(int pos)
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

void LoadGraphic::loadPortPos()
{
//    float halfHeight = _size.height() / 2.0;
    switch(this->getDirect())
    {
    case POS_UP:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(0, _size.height() / 2));
        return;
    case POS_RIGHT:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(-_size.height() / 2,0));
        return;
    case POS_DOWN:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(0, -_size.height() / 2));
        return;
    case POS_LEFT:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(_size.height() / 2,0));
        return;
    }
    GraphicBase::loadPortPos();
}

void LoadGraphic::prepareGraphic(QPainter *painter)
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

void LoadGraphic::drawGraphic(QPainter *painter)
{
    painter->drawLine(0, - _size.height() / 2,
                      0, _size.height() / 2);
    painter->drawLine(0, - _size.height() / 2,
                      -_size.height() / 4, - _size.height() / 4);
    painter->drawLine(0, - _size.height() / 2,
                      _size.height() / 4, - _size.height() / 4);
}














