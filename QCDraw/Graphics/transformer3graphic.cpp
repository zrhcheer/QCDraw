#include "transformer3graphic.h"

#include "earthgraphic.h"

const QString Transformer3Graphic::_devName = CodeConvertor::fromLocal("三卷变");

Transformer3Graphic::Transformer3Graphic()
{
    setType(Graphic::GRAPHIC_TRANS3);

    this->setDirect(Graphic::POS_UP);
    _portPoints.resize(3);
    _bMirror = false;
}


QPointF  Transformer3Graphic::getPortPos(int pos)
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

void Transformer3Graphic::loadPortPosMirror(int neg)
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
        _portPoints[Graphic::JOIN_HIGH].setJoinPoint(QPointF(radius * neg, -_size.height() / 2));
        _portPoints[Graphic::JOIN_LOW].setJoinPoint(QPointF(radius  * neg, _size.height() / 2));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(-radius  * neg * 2, 0));

        ptHigh = QPointF(radius * neg,-radius * CROSS_PERCENT);
        ptLow =  QPointF(radius * neg,radius * CROSS_PERCENT);
        ptMid = QPointF(0,0);
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
        _portPoints[Graphic::JOIN_HIGH].setJoinPoint(QPointF(_size.height() / 2, radius * neg));
        _portPoints[Graphic::JOIN_LOW].setJoinPoint(QPointF(-_size.height() / 2, radius * neg));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(0, -radius * neg * 2));

//        ptHigh = QPointF(-radius * CROSS_PERCENT,radius * neg);
//        ptLow =  QPointF(radius * CROSS_PERCENT,radius * neg);

         ptLow= QPointF(-radius * CROSS_PERCENT,radius * neg);
         ptHigh =  QPointF(radius * CROSS_PERCENT,radius * neg);

        ptMid = QPointF(0,0);
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
        _portPoints[Graphic::JOIN_HIGH].setJoinPoint(QPointF(-radius* neg, _size.height() / 2));
        _portPoints[Graphic::JOIN_LOW].setJoinPoint(QPointF(-radius* neg, -_size.height() / 2));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(radius * neg * 2, 0));

        ptHigh = QPointF(-radius * neg,radius * CROSS_PERCENT);
        ptLow =  QPointF(-radius * neg,-radius * CROSS_PERCENT);
        ptMid = QPointF(0,0);
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
        _portPoints[Graphic::JOIN_HIGH].setJoinPoint(QPointF(-_size.height() / 2, -radius * neg));
        _portPoints[Graphic::JOIN_LOW].setJoinPoint(QPointF(_size.height() / 2, -radius * neg));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(0, radius * neg * 2));

        ptHigh = QPointF(-radius * CROSS_PERCENT,-radius * neg);
        ptLow =  QPointF(radius * CROSS_PERCENT,-radius * neg);
        ptMid = QPointF(0,0);
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
    posEarch(Graphic::JOIN_HIGH,ptHigh,radius,directPos);
    posEarch(Graphic::JOIN_LOW,ptLow,radius,directPos);
    posEarch(Graphic::JOIN_MID,ptMid,radius,midDirect,true);
}

void Transformer3Graphic::loadPortPos()
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
void Transformer3Graphic::prepareGraphic(QPainter *painter)
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

void Transformer3Graphic::drawMirror(QPainter *painter,int neg)  //镜像 关于X 的取反
{
    double radius = _size.height()  / (4 + CROSS_PERCENT * 2);   //类似2卷变 x   0 -> radius
    painter->setBrush(Qt::NoBrush);

    //画高端
    QPointF centerPoint(neg * radius,-radius * CROSS_PERCENT);
    painter->setPen(_highColor);
    painter->drawLine(neg * radius, - _size.height() / 2,
                      neg * radius,- _size.height() / 2 + radius);

    drawTrans(painter,centerPoint,radius,_connHType);    

    //画低端
    painter->setPen(_lowColor);
    centerPoint = QPoint(neg * radius,radius * CROSS_PERCENT);
    drawTrans(painter,centerPoint,radius,_connLType);


    painter->drawLine(neg * radius, _size.height() / 2,
                      neg * radius, _size.height() / 2 - radius);

    // 画中端
    painter->setPen(_midColor);
    centerPoint = QPoint(0,0);
    drawTrans(painter,centerPoint,radius,_connMType);

    painter->drawLine(- neg *radius, 0,
                     -neg * radius * 2, 0);
}

void Transformer3Graphic::drawGraphic(QPainter *painter)
{
    if(_bMirror) //默认=false
    {
        drawMirror(painter,1);
    }
    else
    {
        drawMirror(painter,-1);
    }
}
