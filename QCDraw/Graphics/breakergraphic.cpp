#include "breakergraphic.h"
#include <QPainter>
#include "codeconvertor.h"

const QString BreakerGraphic::_devName = CodeConvertor::fromLocal("¶ÏÂ·Æ÷");

BreakerGraphic::BreakerGraphic()
{
    setType(Graphic::GRAPHIC_BREAKER);
    this->setColor(QColor(255,0,0));
    _bOpen = true;
    this->setDirect(Graphic::POS_UP);
    _portPoints.resize(2);
}


void BreakerGraphic::loadPortPos()
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


void BreakerGraphic::prepareGraphic(QPainter *painter)
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

void BreakerGraphic::drawGraphic(QPainter *painter)
{
    painter->drawLine(0, - _size.height() / 2,
                      0,- _size.height() / 4);

    painter->save();
    painter->setPen(Qt::red);
    painter->setBrush(QBrush(Qt::red));
    if(_bOpen)
    {
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(- _size.height() / 8,- _size.height() / 4,
                           _size.height() / 4,_size.height()/2);
    }
    else
    {
        painter->drawRect(- _size.height() / 8,- _size.height() / 4,
                           _size.height() / 4,_size.height()/2);
    }
    painter->restore();
    painter->drawLine(0, _size.height() / 2,
                      0, _size.height() / 4);
}

/*
QRectF BreakerGraphic::boundingRect() const
{
    qreal adjust=0.5;
    return QRectF(-18-adjust,-22-adjust,36+adjust,60+adjust);
}
void BreakerGraphic::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    painter->drawRect(0,0,200,200);
}*/
