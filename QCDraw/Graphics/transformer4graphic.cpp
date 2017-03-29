#include "transformer4graphic.h"

const QString Transformer4Graphic::_devName = CodeConvertor::fromLocal("ËÄ¾í±ä");

Transformer4Graphic::Transformer4Graphic()
{
    _connLType = TEARTH_Yn;
    _connMType = TEARTH_Yn;
    _connHType = TEARTH_Yn;
    setType(Graphic::GRAPHIC_TRANS4);
    this->setDirect(Graphic::POS_UP);
    _portPoints.resize(3);
    _bMirror = false;
}


QPointF  Transformer4Graphic::getPortPos(int pos)
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

void Transformer4Graphic::loadPortPosMirror(int neg)
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
        _portPoints[Graphic::JOIN_HIGH].setJoinPoint(QPointF(neg * radius / 2
                                                             ,-_size.height() / 2));
        _portPoints[Graphic::JOIN_LOW].setJoinPoint(QPointF(-neg * radius * 2.5, 0));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(neg *radius / 2,
                                                            _size.height() / 2));
        ptHigh = QPointF(neg * radius / 2,-radius * CROSS_PERCENT);
        ptLow =  QPointF(neg * radius / 2,radius * CROSS_PERCENT);
        ptMid = QPointF(-neg * radius / 2,0);
        if(neg >0)
        {
            directPos = Graphic::POS_LEFT;
        }
        else
        {
            directPos = Graphic::POS_RIGHT;
        }
        midDirect = POS_DOWN;
        break;
    case POS_RIGHT:
        _portPoints[Graphic::JOIN_HIGH].setJoinPoint(QPointF( _size.height() / 2,
                                                              neg * radius /2));
        _portPoints[Graphic::JOIN_LOW].setJoinPoint(QPointF(0, -neg * radius * 2.5));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(-_size.height() / 2,
                                                            neg * radius / 2));

        ptHigh = QPointF(radius * CROSS_PERCENT,
                         neg * radius / 2);
        ptLow =  QPointF(-radius * CROSS_PERCENT,
                         neg * radius / 2);
        ptMid = QPoint(0,-neg * radius / 2);

        if(neg >0)
        {
            directPos = Graphic::POS_UP;
        }
        else
        {
            directPos = Graphic::POS_DOWN;
        }
        midDirect = POS_LEFT;
        break;
    case POS_DOWN:
        _portPoints[Graphic::JOIN_HIGH].setJoinPoint(QPointF(-neg * radius / 2,
                                                             _size.height() / 2));
        _portPoints[Graphic::JOIN_LOW].setJoinPoint(QPointF(neg * radius * 2.5,
                                                            0));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(-neg * radius / 2,
                                                            -_size.height() / 2));
        ptHigh = QPointF(-neg * radius / 2
                         ,radius * CROSS_PERCENT);
        ptLow =  QPointF(-neg * radius / 2,-radius * CROSS_PERCENT);
        ptMid = QPointF(neg * radius / 2,0);
        if(neg >0)
        {
            directPos = Graphic::POS_RIGHT;
        }
        else
        {
            directPos = Graphic::POS_LEFT;
        }
        midDirect = POS_UP;
        break;
    case POS_LEFT:
        _portPoints[Graphic::JOIN_HIGH].setJoinPoint(QPointF( -_size.height() / 2.0,
                                                              -neg * radius / 2.0));
        _portPoints[Graphic::JOIN_LOW].setJoinPoint(QPointF(0,neg * radius * 2.5));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(_size.height() / 2.0,
                                                            -neg * radius / 2.0 ));
        ptHigh = QPointF(-radius * CROSS_PERCENT,
                         -neg * radius / 2);
        ptLow =  QPointF(radius * CROSS_PERCENT,
                         -neg * radius / 2);
        ptMid = QPointF(0,neg * radius / 2);
        if(neg >0)
        {
            directPos = Graphic::POS_DOWN;
        }
        else
        {
            directPos = Graphic::POS_UP;
        }
        midDirect = POS_RIGHT;
        break;
    }
    posEarch(Graphic::JOIN_HIGH,ptHigh,radius,directPos,true);
    posEarch(Graphic::JOIN_LOW,ptLow,radius,directPos,true);
    posEarch(Graphic::JOIN_MID,ptMid,radius,midDirect,true);
}

void Transformer4Graphic::loadPortPos()
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
void Transformer4Graphic::prepareGraphic(QPainter *painter)
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

void Transformer4Graphic::drawMirror(QPainter *painter,int neg)
{
    double radius = _size.height()  / (4 + CROSS_PERCENT * 2);
    painter->setBrush(Qt::NoBrush);

    //»­¸ß¶Ë
    QPointF centerPoint(neg * radius /2,-radius * CROSS_PERCENT);
    painter->setPen(_highColor);

    painter->drawLine(neg * radius /2, - _size.height() / 2,
                      neg * radius /2, -radius * (1 + CROSS_PERCENT));
    drawTrans(painter,centerPoint,radius,_connHType);

    //»­×ó¶Ë
    centerPoint = QPoint(neg * radius * (1.5 / 2 + 1),0);
    painter->setPen(_leftColor);
    drawTrans(painter,centerPoint,
              radius * 1.5 / 2,TEARTH_D);

    //»­µÍ¶Ë
    painter->setPen(_lowColor);
    centerPoint = QPoint(neg * radius /2,
                         radius * CROSS_PERCENT);

    drawTrans(painter,centerPoint,radius,_connLType);
    painter->drawLine(neg * radius /2, _size.height() / 2,
                      neg * radius /2, radius * (1 + CROSS_PERCENT));

    // »­ÖÐ¶Ë
    painter->setPen(_midColor);
    centerPoint = QPoint(-neg * radius / 2  ,0);

    drawTrans(painter,centerPoint,radius,_connMType);
    painter->drawLine(-neg * radius * 3 / 2, 0,
                      -neg * radius * 5/ 2, 0);
}

void Transformer4Graphic::drawGraphic(QPainter *painter)
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
