#include "earthgraphic.h"

const QString EarthGraphic::_devName = CodeConvertor::fromLocal("接地");

EarthGraphic::EarthGraphic(QGraphicsItem * parent) :
    GraphicBase(parent)
{
    setType(Graphic::GRAPHIC_EARTH);
    _hasBreaker = false;
    _bOpen = false;
    _lenSwitch = 0;
    _isLong = false;
    this->setColor(QColor(255,0,0));
    this->setDirect(Graphic::POS_UP);
}

QRectF EarthGraphic::boundingRect() const
{
    float halfWidth = _size.width() / 2.0;
    float halfHeight = _size.height() / 2.0;
    switch(this->getDirect())
    {
    case POS_UP:
        return QRectF(- halfWidth,0,_size.width(),_size.height());
        break;
    case POS_RIGHT:
        return QRectF(-_size.height(),- halfWidth,_size.height(),_size.width());
        break;
    case POS_DOWN:
        return QRectF(- halfWidth,-_size.height(),_size.width(),_size.height());
        break;
    case POS_LEFT:
        return QRectF(0,- halfWidth,_size.height(),_size.width());
        break;
    }
    return QRectF(- halfHeight,- halfHeight,_size.height(),_size.height());
}

QPointF  EarthGraphic::getPortPos(int pos)
{
    switch(pos)
    {
    case Graphic::JOIN_BEGIN:
        return QPointF(0,0);
        break;
    case Graphic::JOIN_END:
    default:
        assert(false);
        break;
    }
}

void EarthGraphic::prepareGraphic(QPainter *painter)
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

void EarthGraphic::drawGraphic(QPainter *painter)
{
    float halW = _size.width() / 2.0;
    float square = _size.width() / 3.0;

    //画连出柄
    if(!_bOpen)
    {
        painter->drawLine(0, _lenSwitch,
                          0,0);
    }
    int lenUp = _lenSwitch;
    if(_isLong)
    {
        painter->drawLine(0, _lenSwitch,
                          0,_lenSwitch + halW);
        lenUp += halW;
    }
    //画断路器
    if(_hasBreaker)
    {
        lenUp = _lenSwitch + square * 3;
        painter->drawLine(0, _lenSwitch,
                          0,_lenSwitch + square);
        painter->drawRect(- square / 2,_lenSwitch + halW / 2,square,square * 2);
    }
    //画接地
    painter->drawLine(0, lenUp,
                      0,lenUp + square);

    lenUp += square;
    float tanX = tan(50 * M_RADIUS);
    float lenHalfEarch =  halW * 2 / 5;
    painter->drawLine(-halW, lenUp,
                      halW,lenUp);
    painter->drawLine(-halW + lenHalfEarch  / tanX, lenUp + lenHalfEarch,
                      halW - lenHalfEarch  /  tanX, lenUp + lenHalfEarch);
    painter->drawLine(-halW + lenHalfEarch * 2  / tanX, lenUp + lenHalfEarch * 2,
                      halW - lenHalfEarch * 2  /  tanX , lenUp + lenHalfEarch * 2);

//    painter->setBrush(Qt::NoBrush);
//    painter->setPen(QPen(QBrush(Qt::blue),1,Qt::DashDotLine));
//    painter->drawRect(-_size.width() / 2,0,_size.width(),_size.height());
}
void EarthGraphic::drawSelect(QPainter *painter)
{
    painter->save();
    painter->setBrush(QBrush(Qt::green));
    painter->setPen(QPen(QBrush(Qt::black),1));
    painter->drawRect(-3,_size.height() / 2 -3,6,6);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(QBrush(Qt::blue),1,Qt::DashDotLine));
    painter->drawRect(-_size.width() / 2,0,_size.width(),_size.height());
    painter->restore();
}
