#include "transformer2graphic.h"

#include <math.h>
#include "earthgraphic.h"

const QString Transformer2Graphic::_devName = CodeConvertor::fromLocal("¶þ¾í±ä");

Transformer2Graphic::Transformer2Graphic()
{
    _connLType = TEARTH_D;
    _connHType = TEARTH_Yn;
    setType(Graphic::GRAPHIC_TRANS2);
    this->setDirect(Graphic::POS_UP);
    _portPoints.resize(2);
}
QPointF  Transformer2Graphic::getPortPos(int pos)
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
    assert(false);
    return QPointF(0,0);
}

void Transformer2Graphic::loadPortPos()
{
    float halfHeight = _size.height() / 2.0;
    int earchDirect = Graphic::POS_LEFT;
    double radius = _size.height()  / (4 + CROSS_PERCENT * 2);
    QPointF pointHigh;
    QPointF pointLow;
    switch(this->getDirect())
    {
    case POS_UP:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(0, -halfHeight));
        _portPoints[Graphic::JOIN_END].setJoinPoint(QPointF(0, halfHeight));
        earchDirect = Graphic::POS_RIGHT;
        pointHigh = QPointF(0, - radius * CROSS_PERCENT);
        pointLow = QPointF(0,  radius * CROSS_PERCENT);
        break;
    case POS_RIGHT:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(halfHeight,0));
        _portPoints[Graphic::JOIN_END].setJoinPoint(QPointF(- halfHeight, 0));
        earchDirect = Graphic::POS_DOWN;
        pointHigh = QPointF(radius * CROSS_PERCENT,0);
        pointLow = QPointF(-radius * CROSS_PERCENT,0);
        break;
    case POS_DOWN:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(0, halfHeight));
        _portPoints[Graphic::JOIN_END].setJoinPoint(QPointF(0, -halfHeight));
        earchDirect = Graphic::POS_LEFT;
        pointHigh = QPointF(0, radius * CROSS_PERCENT);
        pointLow = QPointF(0, -radius * CROSS_PERCENT);
        break;
    case POS_LEFT:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(-halfHeight,0));
        _portPoints[Graphic::JOIN_END].setJoinPoint(QPointF(halfHeight, 0));
        earchDirect = Graphic::POS_UP;
        pointHigh = QPointF(-radius * CROSS_PERCENT,0);
        pointLow = QPointF(radius * CROSS_PERCENT,0);
        break;
    }

    posEarch(Graphic::JOIN_HIGH,pointHigh,radius,earchDirect);
    posEarch(Graphic::JOIN_LOW,pointLow,radius,earchDirect);

    GraphicBase::loadPortPos();
}

void Transformer2Graphic::prepareGraphic(QPainter *painter)
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

void Transformer2Graphic::drawGraphic(QPainter *painter)
{
    double radius = _size.height()  / (4 + CROSS_PERCENT * 2);


    painter->setBrush(Qt::NoBrush);
    //»­¸ß¶Ë
    painter->setPen(_highColor);
    painter->drawLine(0, - _size.height() / 2,
                      0,- _size.height() / 2 + radius);

    QPointF centerPoint(0,-radius * CROSS_PERCENT);
    drawTrans(painter,centerPoint,radius,_connHType);

    //»­µÍ¶Ë
    painter->setPen(_lowColor);
    centerPoint = QPoint(0,radius * CROSS_PERCENT);

    drawTrans(painter,centerPoint,radius,_connLType);

    painter->drawLine(0, _size.height() / 2,
                      0, _size.height() / 2 - radius);
}
