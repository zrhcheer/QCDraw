#include "splittrans4graphic.h"

const QString SplitTrans4Graphic::_devName = CodeConvertor::fromLocal("·ÖÁÑËÄ¾í±ä");

SplitTrans4Graphic::SplitTrans4Graphic()
{
    _connLType = TEARTH_Yn;
    _connMType = TEARTH_Yn;
    _connHType = TEARTH_Yn;
    setType(Graphic::GRAPHIC_SPLITTRANS4);
    this->setDirect(Graphic::POS_UP);
    _portPoints.resize(3);
    _bMirror = false;
}

QPointF  SplitTrans4Graphic::getPortPos(int pos)
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

void SplitTrans4Graphic::loadPortPosMirror(int neg)
{
    double radius = _size.height()  / (4 + CROSS_PERCENT * 2);
    int directPos;
    int midDirect;
    QPointF ptHigh;
    QPointF ptLow;
    QPointF ptMid;
    switch(this->getDirect())
    {
    case POS_UP:
        _portPoints[Graphic::JOIN_HIGH].setJoinPoint(QPointF(0,-_size.height() / 2));
        _portPoints[Graphic::JOIN_LOW].setJoinPoint(QPointF(-neg *radius *RADIUS2_PERCENT,
                                                            _size.height() / 2));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(neg *radius *RADIUS2_PERCENT,
                                                            _size.height() / 2));

        ptHigh = QPointF(0,-radius * CROSS_PERCENT);
        ptLow = QPoint(neg * radius *RADIUS2_PERCENT,
                             radius * CROSS_PERCENT);
        ptMid = QPoint(-neg * radius *RADIUS2_PERCENT,
                             radius * CROSS_PERCENT);

        if(neg >0)
        {
            directPos = Graphic::POS_LEFT;
            midDirect = Graphic::POS_RIGHT;
        }
        else
        {
            directPos = Graphic::POS_RIGHT;
            midDirect = Graphic::POS_LEFT;
        }
        break;
    case POS_RIGHT:
        _portPoints[Graphic::JOIN_HIGH].setJoinPoint(QPointF(_size.height() / 2,0));
        _portPoints[Graphic::JOIN_LOW].setJoinPoint(QPointF(-_size.height() / 2,
                                                            -neg *radius *RADIUS2_PERCENT));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(-_size.height() / 2,
                                                            neg *radius *RADIUS2_PERCENT));
        ptHigh = QPointF(radius * CROSS_PERCENT,0);
        ptLow = QPoint(-radius * CROSS_PERCENT,
                       neg * radius *RADIUS2_PERCENT);
        ptMid = QPoint(-radius * CROSS_PERCENT,
                       -neg * radius *RADIUS2_PERCENT);

        if(neg >0)
        {
            directPos = Graphic::POS_UP;
            midDirect = Graphic::POS_DOWN;
        }
        else
        {
            directPos = Graphic::POS_DOWN;
            midDirect = Graphic::POS_UP;
        }

        break;
    case POS_DOWN:
        _portPoints[Graphic::JOIN_HIGH].setJoinPoint(QPointF(0,_size.height() / 2));
        _portPoints[Graphic::JOIN_LOW].setJoinPoint(QPointF(neg *radius *RADIUS2_PERCENT,
                                                            -_size.height() / 2));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(-neg *radius *RADIUS2_PERCENT,
                                                            -_size.height() / 2));
        ptHigh = QPointF(0,radius * CROSS_PERCENT);
        ptLow = QPoint(-neg * radius *RADIUS2_PERCENT,
                       -radius * CROSS_PERCENT);
        ptMid = QPoint(neg * radius *RADIUS2_PERCENT,
                      - radius * CROSS_PERCENT);

        if(neg >0)
        {
            directPos = Graphic::POS_RIGHT;
            midDirect = Graphic::POS_LEFT;
        }
        else
        {
            directPos = Graphic::POS_LEFT;
            midDirect = Graphic::POS_RIGHT;
        }
        break;
    case POS_LEFT:
        _portPoints[Graphic::JOIN_HIGH].setJoinPoint(QPointF(-_size.height() / 2,0));
        _portPoints[Graphic::JOIN_LOW].setJoinPoint(QPointF(_size.height() / 2,
                                                            neg *radius *RADIUS2_PERCENT));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(_size.height() / 2,
                                                            -neg *radius *RADIUS2_PERCENT));

        ptHigh = QPointF(-radius * CROSS_PERCENT,0);
        ptLow = QPoint(radius * CROSS_PERCENT,
                       -neg * radius *RADIUS2_PERCENT);
        ptMid = QPoint( radius * CROSS_PERCENT,
                        neg * radius *RADIUS2_PERCENT);

        if(neg >0)
        {
            directPos = Graphic::POS_DOWN;
            midDirect = Graphic::POS_UP;
        }
        else
        {
            directPos = Graphic::POS_UP;
            midDirect = Graphic::POS_DOWN;
        }
        break;

    }
    posEarch(Graphic::JOIN_HIGH,ptHigh,radius,directPos,true);
    posEarch(Graphic::JOIN_LOW,ptLow,radius,directPos,true);
    posEarch(Graphic::JOIN_MID,ptMid,radius,midDirect,true);
}

void SplitTrans4Graphic::loadPortPos()
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
void SplitTrans4Graphic::prepareGraphic(QPainter *painter)
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

void SplitTrans4Graphic::drawMirror(QPainter *painter,int neg)
{
    double radius = _size.height()  / (4 + CROSS_PERCENT * 2);
    painter->setBrush(Qt::NoBrush);

    //»­¸ß¶Ë
    QPointF centerPoint(0,-radius * CROSS_PERCENT);
    painter->setPen(_highColor);

    painter->drawLine(0, - _size.height() / 2,0,- 2*radius);
    drawTrans(painter,centerPoint,radius,_connHType);

    //»­×ó¶Ë
    painter->setPen(_lowColor);
    centerPoint = QPoint(neg * radius *RADIUS2_PERCENT,
                         radius * CROSS_PERCENT);

    drawTrans(painter,centerPoint,radius,_connLType);
    painter->drawLine(neg *radius *RADIUS2_PERCENT, _size.height() / 2,
                      neg *radius *RADIUS2_PERCENT, _size.height() / 2 - 2*radius);

    // »­ÖÐ¶Ë
    painter->setPen(_midColor);
    centerPoint = QPoint(-neg * radius *RADIUS2_PERCENT,
                         radius * CROSS_PERCENT);

    drawTrans(painter,centerPoint,radius,_connLType);
    painter->drawLine(-neg *radius *RADIUS2_PERCENT, _size.height() / 2,
                      -neg *radius *RADIUS2_PERCENT, _size.height() / 2 - 2*radius);

    //»­Ð¡Ô²
    painter->setPen(_lowColor);
    centerPoint = QPoint(-neg * radius*(1 + RADIUS2_PERCENT- RADIUS_PERCENT*(3 / 2 - 5 / 4 * HORIZONTAL2_PERCENT)),
                         -radius * CROSS_PERCENT/3);

    drawTrans(painter,centerPoint,
              RADIUS_PERCENT*radius * (3 / 2 - 5 / 4 * HORIZONTAL2_PERCENT),
              TEARTH_D);
}

void SplitTrans4Graphic::drawGraphic(QPainter *painter)
{
    if(_bMirror)
    {
        drawMirror(painter,1);
    }
    else
    {
        drawMirror(painter,-1);
    }
}
