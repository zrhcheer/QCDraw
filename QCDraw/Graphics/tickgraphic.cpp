#include "tickgraphic.h"
#include <QPainter>

const QString TickGraphic::_devName = CodeConvertor::fromLocal("±ê¼Ç");

TickGraphic::TickGraphic(QGraphicsItem* parent,int flag) :
    QGraphicsItem(parent)
{
    _flag = flag;
    this->setType(GRAPHIC_TICK);
    this->setZValue(2);
    switch(_flag)
    {
    case TICK_CROSS:
        _size = QSize(6,6);
        break;
    case TICK_EXCLA:
        _size = QSize(6,25);
        break;
    case TICK_LIGHT:
        _size = QSize(6,12);
        break;
    }


    _color = QColor(255,0,0);
}

void TickGraphic::setTickPos(const QLineF& line,bool bBegin)
{
    if(bBegin)
    {
        float len = _size.width() * 1.5;
        float percent = len / line.length();
        QPointF point = line.pointAt(percent);
        this->setPosition(point);
    }
    else
    {
        float len = _size.width() * 1.5;
        float percent = (line.length() - len) / line.length();
        QPointF point = line.pointAt(percent);
        this->setPosition(point);
    }
}

void TickGraphic::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    UNUSED(option);
    UNUSED(widget);
    painter->save();
    prepareGraphic(painter);
    drawGraphic(painter);
    painter->restore();
}
void TickGraphic::prepareGraphic(QPainter *painter)
{
    painter->setPen(QPen(QBrush(_color),2));
}

void TickGraphic::drawGraphic(QPainter *painter)
{
    float  halfWidth = _size.width() / 2;
    float halfHeight =  _size.height() / 2;
    switch(_flag)
    {
    case TICK_CROSS:
        painter->drawLine(- halfWidth,- halfHeight,halfWidth,halfHeight);
        painter->drawLine(halfWidth,- halfHeight,-halfWidth,halfHeight);
        break;
    case TICK_EXCLA:
    {
        painter->save();
        //painter->setPen(QPen(QBrush(Qt::gray),2));
        QFont  font = painter->font();
        font.setPointSize(30);
        painter->setFont(font);
        painter->drawText(-halfWidth,-halfHeight,_size.width(),_size.height(),Qt::AlignCenter,"!");
        painter->restore();
    }
        break;
    case TICK_LIGHT:
        painter->drawLine(halfWidth,- halfHeight,-halfWidth,0);
        painter->drawLine(-halfWidth,0,halfWidth,0);
        painter->drawLine(halfWidth,0,-halfWidth,halfHeight);
        break;
    }
}

QRectF TickGraphic::boundingRect() const
{
    return QRectF(- _size.width() / 2,- _size.height() / 2,_size.width(),_size.height());
}

void TickGraphic::loadXML(rapidxml::xml_node<char> *node)
{
    
}

void TickGraphic::restoreGraphic(QDataStream& dataStream)
{
    UNUSED(dataStream);
}

void TickGraphic::saveXML(rapidxml::xml_node<char> *node, rapidxml::xml_document<> &doc,Graphic* graphic)
{

}

void TickGraphic::saveGraphic(QDataStream& dataStream) const
{
    UNUSED(dataStream);
}
