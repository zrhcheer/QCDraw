#include "selftransgraphic.h"
#include "earthgraphic.h"

const QString SelfTransGraphic::_devName = CodeConvertor::fromLocal("×Ôñî±ä");

class EarthGraphic;
SelfTransGraphic::SelfTransGraphic()
{
    earthHGraphic = NULL;
    _bMirror = false;
    setType(Graphic::GRAPHIC_SELFTRANS);
    this->setDirect(Graphic::POS_UP);
    _portPoints.resize(3);
}

QPointF  SelfTransGraphic::getPortPos(int pos)
{
    switch(pos)
    {
    case Graphic::JOIN_BEGIN:
        return _portPoints[Graphic::JOIN_BEGIN].getJoinPoint();
        break;
    case Graphic::JOIN_MID:
        return _portPoints[Graphic::JOIN_MID].getJoinPoint();
        break;
    case Graphic::JOIN_END:
        return _portPoints[Graphic::JOIN_END].getJoinPoint();
        break;
    }
    assert(false);
    return QPointF(0,0);
}
void SelfTransGraphic::loadPortPosMirror(int neg)
{
    float radius = _size.height()  / (4 + CROSS_PERCENT * 2);

    int directPos = Graphic::POS_LEFT;
    QPointF ptHigh;
    QPointF ptLow;
    switch(this->getDirect())
    {
    case POS_UP:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF( - radius * neg, - _size.height() / 2));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(radius  * neg *2,-radius * CROSS_PERCENT));
        _portPoints[Graphic::JOIN_END].setJoinPoint(QPointF(- radius  * neg, _size.height() / 2));

        ptHigh = QPointF(-radius * neg,-radius * CROSS_PERCENT);
        ptLow = QPointF(-radius * neg,radius * CROSS_PERCENT);
        if(neg >0)
        {
            directPos = Graphic::POS_RIGHT;
        }
        else
        {
            directPos = Graphic::POS_LEFT;
        }
        break;
    case POS_RIGHT:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF (_size.height() / 2,- radius  * neg));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(radius * CROSS_PERCENT,radius  * neg * 2));
        _portPoints[Graphic::JOIN_END].setJoinPoint(QPointF(-_size.height() / 2, - radius  * neg));

        ptLow = QPointF(-radius * CROSS_PERCENT,-radius * neg);
        ptHigh  = QPointF(radius * CROSS_PERCENT,-radius * neg);
        if(neg >0)
        {
            directPos = Graphic::POS_DOWN;
        }
        else
        {
            directPos = Graphic::POS_UP;
        }
        break;
    case POS_DOWN:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(radius  * neg,_size.height() / 2));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(-2*radius  * neg, radius));
        _portPoints[Graphic::JOIN_END].setJoinPoint(QPointF(radius  * neg,- _size.height() / 2));


        ptHigh = QPointF(radius * neg,radius * CROSS_PERCENT);
        ptLow = QPointF(radius * neg,-radius * CROSS_PERCENT);
        if(neg >0)
        {
            directPos = Graphic::POS_LEFT;
        }
        else
        {
            directPos = Graphic::POS_RIGHT;
        }
        break;
    case POS_LEFT:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(-_size.height() / 2,radius  * neg));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(-radius  * CROSS_PERCENT,- 2*radius  * neg));
        _portPoints[Graphic::JOIN_END].setJoinPoint(QPointF( _size.height() / 2,radius  * neg));

        ptHigh = QPointF(-radius * CROSS_PERCENT,radius * neg);
        ptLow =  QPointF(radius * CROSS_PERCENT,radius * neg);
        if(neg >0)
        {
            directPos = Graphic::POS_UP;
        }
        else
        {
            directPos = Graphic::POS_DOWN;
        }
        break;
    }

    posEarch(Graphic::JOIN_HIGH,ptHigh,radius,directPos);
    posEarch(Graphic::JOIN_LOW,ptLow,radius,directPos);
}

void SelfTransGraphic::loadPortPos()
{
    if(_bMirror)
    {
        loadPortPosMirror(-1);
    }
    else
    {
        loadPortPosMirror(1);
    }
    GraphicBase::loadPortPos();
}
void SelfTransGraphic::prepareGraphic(QPainter *painter)
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

void SelfTransGraphic::drawMirror(QPainter *painter,int neg)
{
    double radius = _size.height()  / (4 + CROSS_PERCENT * 2);

    painter->setBrush(Qt::NoBrush);
    //»­¸ß¶Ë
    painter->setPen(_highColor);
    painter->drawLine( - radius * neg, - _size.height() / 2,
                       - radius * neg, - _size.height() / 2 + radius*2/3); //Line=radius*2/3

    QPointF centerPoint(- radius  * neg,-radius * CROSS_PERCENT);
    drawTrans(painter,centerPoint,radius,_connHType);

    double angle = 210*M_RADIUS;
    //    »æÖÆ±´Èû¶ûÇúÏß
    QPoint start_pos(centerPoint.x() + radius * cos(angle) * neg,centerPoint.y() + radius * sin(angle));
    QPoint end_pos(- radius * neg,   - _size.height() / 2 + radius*2/3);  //shang fang
    //drawPath;
    QPainterPath path(start_pos);
    QPoint c1 = start_pos;  //
    QPoint c2((end_pos.x() + start_pos.x())/2 - radius  * neg,   (end_pos.y() + start_pos.y())/2);
    path.cubicTo(c1 ,c2 ,end_pos);
    painter->drawPath(path);

    //»æÖ±Ïß
    painter->setPen(_midColor);
    painter->drawLine(- radius * neg, -radius * CROSS_PERCENT, radius * neg * 2, -radius * CROSS_PERCENT);

    //»­µÍ¶Ë
    painter->setPen(_lowColor);
    centerPoint = QPoint(- radius * neg,radius * CROSS_PERCENT);
    drawTrans(painter,centerPoint,radius,_connLType);

    painter->drawLine(- radius * neg, _size.height() / 2,
                      - radius * neg , _size.height() / 2 - radius);
}

void SelfTransGraphic::drawGraphic(QPainter *painter)
{
    if(_bMirror)  //false
    {
        drawMirror(painter,-1);
    }
    else
    {
        drawMirror(painter,1);
    }
}
