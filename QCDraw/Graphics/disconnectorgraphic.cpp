#include "disconnectorgraphic.h"

const QString DisconnectorGraphic::_devName = CodeConvertor::fromLocal("µ¶Õ¢");
DisconnectorGraphic::DisconnectorGraphic()
{
    setType(Graphic::GRAPHIC_DISCONNECTOR);
    this->setColor(QColor(255,0,0));
    _bOpen = false;
    this->setDirect(Graphic::POS_UP);
    _portPoints.resize(2);
}


void DisconnectorGraphic::loadPortPos()
{
    float halfHeight = _size.height() / 2;
    switch(this->getDirect())
    {
    case POS_UP:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(0, -halfHeight));
        _portPoints[Graphic::JOIN_END].setJoinPoint(QPointF(0, halfHeight));
        return;
    case POS_RIGHT:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(halfHeight,0));
        _portPoints[Graphic::JOIN_END].setJoinPoint(QPointF(- halfHeight, 0));
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

void DisconnectorGraphic::prepareGraphic(QPainter *painter)
{
    GraphicBase::prepareGraphic(painter);
    switch(this->getDirect())
    {
    case POS_UP:
        break;
    case POS_RIGHT:
    case POS_LEFT:
        painter->rotate(90);
        break;
    case POS_DOWN:
        painter->rotate(180);
        break;
//    case POS_LEFT:
//        painter->rotate(270);
//        break;
    }
}

void DisconnectorGraphic::drawGraphic(QPainter *painter)
{
   painter->setBrush(Qt::NoBrush);
   painter->drawEllipse(-BAR_SIZE / 2, - _size.height() / 2,
                      BAR_SIZE,BAR_SIZE);

   painter->save();
   painter->setPen(Qt::red);
    if(_bOpen)
    {

        QPoint pointDown(0, _size.height() / 2 - BAR_SIZE / 2);
        QPoint pointUp(- _size.width() / 2,-_size.height() / 2 + 5);

        painter->drawLine(pointDown,
                           pointUp);
    }
    else
    {
        //painter->setPen(QPen(Qt::red));
        painter->drawLine(0, -_size.height() / 2 +  BAR_SIZE / 2,
                           0, _size.height() / 2 - BAR_SIZE / 2);
    }
    painter->restore();
    painter->drawEllipse(-BAR_SIZE / 2, _size.height() / 2 - BAR_SIZE,
                      BAR_SIZE,BAR_SIZE);
}
