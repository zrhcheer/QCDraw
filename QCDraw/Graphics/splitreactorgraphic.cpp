#include "splitreactorgraphic.h"

const QString SplitReactorGraphic::_devName = CodeConvertor::fromLocal("·ÖÁÑµç¿¹Æ÷");

SplitReactorGraphic::SplitReactorGraphic()
{
    setType(Graphic::GRAPHIC_SPLITREACTOR);
    _bMirror = false;
    this->setColor(QColor(22,149,19));
    this->setDirect(Graphic::POS_UP);
    _portPoints.resize(3);
}
QPointF  SplitReactorGraphic::getPortPos(int pos)
{
    switch(pos)
    {
    case Graphic::JOIN_BEGIN:
        return _portPoints[Graphic::JOIN_BEGIN].getJoinPoint();
        break;
    case Graphic::JOIN_END:
        return _portPoints[Graphic::JOIN_END].getJoinPoint();
        break;
   case Graphic::JOIN_MID:
        return _portPoints[Graphic::JOIN_MID].getJoinPoint();
        break;
    }
    return QPointF(0,0);
}
void SplitReactorGraphic::loadPortPosMirror(int neg)
{
    double radius = _size.height() / 4;
    switch(this->getDirect())
    {
    case POS_UP:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(-radius * neg / 2, -_size.height() / 2));
        _portPoints[Graphic::JOIN_END].setJoinPoint(QPointF(-radius * neg / 2 , _size.height() / 2));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(radius * neg * 3 / 2,0));
        return;
    case POS_RIGHT:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(_size.height() / 2, -radius * neg / 2));
        _portPoints[Graphic::JOIN_END].setJoinPoint(QPointF(-_size.height() / 2, -radius * neg / 2));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(0,radius * neg * 3 / 2));
        return;
    case POS_DOWN:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(radius * neg / 2, -_size.height() / 2));
        _portPoints[Graphic::JOIN_END].setJoinPoint(QPointF(radius * neg  / 2, _size.height() / 2));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(-radius * neg * 3 / 2,0));
        return;
    case POS_LEFT:
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(QPointF(-_size.height() / 2, radius * neg / 2));
        _portPoints[Graphic::JOIN_END].setJoinPoint(QPointF(_size.height() / 2, radius * neg / 2));
        _portPoints[Graphic::JOIN_MID].setJoinPoint(QPointF(0,-radius * neg * 3 / 2));
        return;
    }
}

void SplitReactorGraphic::loadPortPos()
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
void SplitReactorGraphic::prepareGraphic(QPainter *painter)
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

void SplitReactorGraphic::drawMirror(QPainter *painter,int neg)
{
    double radius = _size.height()  / 4;

    painter->setBrush(Qt::NoBrush);
    painter->setPen(this->getColor());
    painter->drawLine(-radius * neg  / 2, - _size.height() / 2,
                      -radius  * neg / 2 ,-radius / 2);

    if(neg > 0)
    {
        painter->drawArc(-radius  / 2 -  radius,-radius,
                         radius * 2,radius* 2,
                         210 * 16,300 * 16);
    }
    else
    {
        painter->drawArc( radius / 2 -  radius,-radius,
                         radius * 2,radius* 2,
                         30 * 16,300 * 16);
    }

    painter->drawLine(radius  * neg  / 2,0,radius * neg * 3 /  2,0);

    painter->drawLine(- radius  * neg / 2,  -radius / 2,
                      radius  * neg * cos(210 * M_RADIUS) - radius * neg / 2,radius * sin(210 * M_RADIUS) );
    painter->drawLine(- radius  * neg  / 2,  radius / 2,
                      radius  * neg * cos(150 * M_RADIUS) - radius *  neg / 2,radius * sin(150 * M_RADIUS));

    painter->drawLine(-radius  * neg / 2,_size.height() / 2,
                      -radius  * neg / 2,  radius / 2);
}

void SplitReactorGraphic::drawGraphic(QPainter *painter)
{
    if(_bMirror)
    {
        drawMirror(painter,-1);
    }
    else
    {
        drawMirror(painter,1);
    }
}
