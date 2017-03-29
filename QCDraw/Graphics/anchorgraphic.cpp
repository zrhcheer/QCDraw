#include "anchorgraphic.h"
#include "graphic.h"
#include <QPainter>

AnchorGraphic::AnchorGraphic(bool bBig,QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    this->setZValue(0.1);
    _bGig = bBig;
    if(_bGig)
    {
        _width = PORTSIZE * 2;
    }
    else
    {
        _width = PORTSIZE;
    }
}
void AnchorGraphic::setIsBig(const bool& bGig)
{
    if(_bGig != bGig)
    {
        bool bChange = false;
        if(this->isVisible())
        {
            this->hide();
            bChange = true;
        }
        _bGig = bGig;
        if(_bGig)
        {
            _width = PORTSIZE * 2;
        }
        else
        {
            _width = PORTSIZE;
        }
        if(bChange)
        {
            this->show();
        }
    }
}

QRectF AnchorGraphic::boundingRect() const
{
    return QRectF(-_width,-_width,_width * 2,_width* 2);
}
void AnchorGraphic::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    UNUSED(option);
    UNUSED(widget);
    painter->save();
    painter->setBrush(QBrush(Qt::red));

    painter->drawRect(- _width,- _width,_width * 2, _width * 2);
    painter->drawLine(0, - _width / 2,0,_width / 2);
    painter->drawLine( - _width / 2,0, _width / 2,0);

    painter->restore();
}
