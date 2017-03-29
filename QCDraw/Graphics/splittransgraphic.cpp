#include "splittransgraphic.h"

#include "earthgraphic.h"

const QString SplitTransGraphic::_devName = CodeConvertor::fromLocal("·ÖÁÑ±äÑ¹Æ÷");

SplitTransGraphic::SplitTransGraphic()
{
    setType(Graphic::GRAPHIC_SPLITTRANS);
    this->setDirect(Graphic::POS_UP);
    _portPoints.resize(3);
}

QPointF  SplitTransGraphic::getPortPos(int pos)
{
    switch(pos)
    {
    case Graphic::JOIN_HIGH:
        return _portPoints[Graphic::JOIN_HIGH].getJoinPoint();
        break;
    case Graphic::JOIN_LOW:
        return _portPoints[Graphic::JOIN_LOW].getJoinPoint();
        break;
    case Graphic::JOIN_MID:
        return _portPoints[Graphic::JOIN_MID].getJoinPoint();
        break;
    }
    assert(false);
    return QPointF();
}
void SplitTransGraphic::loadPortPosMirror(int neg)
{
    double radius = _size.height()  / (4 + CROSS_PERCENT * 2);
    int earchDirect;
    int directLow;
    QPointF pointHigh;
    QPointF pointMid;
    QPointF pointLow;
    switch(this->getDirect())
    {
    case POS_UP:
        _portPoints[Graphic::JOIN_HIGH].setJoinPoint(QPointF(0,- _size.height() / 2));
        _portPoints[Graphic::JOIN_LOW].setJoinPoint(QPointF(-radius * neg * HORIZONTAL_PERCENT, _size.height() / 2));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(radius * neg * HORIZONTAL_PERCENT,  _size.height() / 2));

        if(neg > 0)
        {
            earchDirect = Graphic::POS_RIGHT;
            directLow = Graphic::POS_LEFT;
            pointMid =  QPoint(-radius * HORIZONTAL_PERCENT,radius * CROSS_PERCENT);
            pointLow =  QPoint(radius * HORIZONTAL_PERCENT,radius * CROSS_PERCENT);
        }
        else
        {
            earchDirect = Graphic::POS_LEFT;
            directLow = Graphic::POS_RIGHT;
            pointMid =  QPoint(radius * HORIZONTAL_PERCENT,radius * CROSS_PERCENT);
            pointLow =  QPoint(-radius * HORIZONTAL_PERCENT,radius * CROSS_PERCENT);
        }
        pointHigh = QPointF(0,-radius * CROSS_PERCENT);

        break;
    case POS_RIGHT:
        _portPoints[Graphic::JOIN_HIGH].setJoinPoint(QPointF(_size.height() / 2,0));
        _portPoints[Graphic::JOIN_LOW].setJoinPoint(QPointF(-_size.height() / 2, -radius * neg * HORIZONTAL_PERCENT));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(-_size.height() / 2,  radius * neg * HORIZONTAL_PERCENT));
        if(neg > 0)
        {
            earchDirect = Graphic::POS_DOWN;
            directLow = Graphic::POS_UP;
            pointMid =  QPoint(-radius * CROSS_PERCENT,-radius * HORIZONTAL_PERCENT);
            pointLow =  QPoint(-radius * CROSS_PERCENT,radius * HORIZONTAL_PERCENT);
        }
        else
        {
            earchDirect = Graphic::POS_UP;
            directLow = Graphic::POS_DOWN;
            pointMid =  QPoint(-radius * CROSS_PERCENT,radius * HORIZONTAL_PERCENT);
            pointLow =  QPoint(-radius * CROSS_PERCENT,-radius * HORIZONTAL_PERCENT);
        }
        pointHigh = QPointF(radius * CROSS_PERCENT,0);

        break;
    case POS_DOWN:
        _portPoints[Graphic::JOIN_HIGH].setJoinPoint(QPointF(0, _size.height() / 2));
        _portPoints[Graphic::JOIN_LOW].setJoinPoint(QPointF(radius * neg * HORIZONTAL_PERCENT, -_size.height() / 2));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(-radius * neg * HORIZONTAL_PERCENT, -_size.height() / 2));

        if(neg > 0)
        {
            earchDirect = Graphic::POS_LEFT;
            directLow = Graphic::POS_RIGHT;
            pointMid =  QPoint(radius * HORIZONTAL_PERCENT,-radius * CROSS_PERCENT);
            pointLow =  QPoint(-radius * HORIZONTAL_PERCENT,-radius * CROSS_PERCENT);
        }
        else
        {
            earchDirect = Graphic::POS_RIGHT;
            directLow = Graphic::POS_LEFT;
            pointMid =  QPoint(-radius * HORIZONTAL_PERCENT,-radius * CROSS_PERCENT);
            pointLow =  QPoint(radius * HORIZONTAL_PERCENT,-radius * CROSS_PERCENT);
        }
        pointHigh = QPointF(0,radius * CROSS_PERCENT);

        break;
    case POS_LEFT:
        _portPoints[Graphic::JOIN_HIGH].setJoinPoint(QPointF(-_size.height() / 2, 0));
        _portPoints[Graphic::JOIN_LOW].setJoinPoint(QPointF(_size.height() / 2, radius * neg * HORIZONTAL_PERCENT));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(_size.height() / 2, -radius * neg * HORIZONTAL_PERCENT));

        if(neg > 0)
        {
            earchDirect = Graphic::POS_UP;
            directLow = Graphic::POS_DOWN;
            pointMid =  QPoint(radius * CROSS_PERCENT,radius * HORIZONTAL_PERCENT);
            pointLow =  QPoint(radius * CROSS_PERCENT,-radius * HORIZONTAL_PERCENT);
        }
        else
        {
            earchDirect = Graphic::POS_DOWN;
            directLow = Graphic::POS_UP;
            pointMid =  QPoint(radius * CROSS_PERCENT,-radius * HORIZONTAL_PERCENT);
            pointLow =  QPoint(radius * CROSS_PERCENT,radius * HORIZONTAL_PERCENT);
        }
        pointHigh = QPointF(-radius * CROSS_PERCENT,0);

        break;
    }
    posEarch(JOIN_BEGIN,pointHigh,radius,earchDirect);
    posEarch(JOIN_LOW,pointLow,radius,directLow);
    posEarch(JOIN_MID,pointMid,radius,earchDirect);
}

void SplitTransGraphic::loadPortPos()
{
    if(_bMirror)
    {
        loadPortPosMirror(1);
    }
    else
    {
        loadPortPosMirror(-1);
    }
    GraphicBase::loadPortPos();
}
void SplitTransGraphic::prepareGraphic(QPainter *painter)
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

void SplitTransGraphic::drawGraphic(QPainter *painter)
{
    double radius = _size.height()  / (4 + CROSS_PERCENT * 2);
    painter->setBrush(Qt::NoBrush);
    //»­¸ß¶Ë
    QPointF centerPoint(0,-radius * CROSS_PERCENT);
    painter->setPen(_highColor);
    painter->drawLine(0, - _size.height() / 2,
                      0,- _size.height() / 2 + radius);

    drawTrans(painter,centerPoint,radius,_connHType);

    //»­ÖÐ¶Ë I (ÓÒ²àÔ²)
    painter->setPen(_midColor);
    centerPoint = QPoint(radius * HORIZONTAL_PERCENT, radius * CROSS_PERCENT);

    drawTrans(painter,centerPoint,radius,_connLType);

    painter->drawLine(radius * HORIZONTAL_PERCENT,  _size.height() / 2,
                      radius * HORIZONTAL_PERCENT,  _size.height() / 2 - radius);

    //»­µÍ¶Ë II(×ó²àÔ²)
    painter->setPen(_lowColor);
    centerPoint = QPoint(- radius * HORIZONTAL_PERCENT,radius * CROSS_PERCENT);
    drawTrans(painter,centerPoint,radius,_connMType);

    painter->drawLine(-radius * HORIZONTAL_PERCENT, _size.height() / 2,
                      -radius * HORIZONTAL_PERCENT, _size.height() / 2 - radius);
}
