#ifndef ANCHORGRAPHIC_H
#define ANCHORGRAPHIC_H

#include <QGraphicsItem>

class AnchorGraphic : public QGraphicsItem//锚
{
public:
    AnchorGraphic(bool bBig,QGraphicsItem *parent = 0);
    virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    //获取矩形大小
    virtual QRectF boundingRect() const;

    void setIsBig(const bool& bGig);

private:
    bool _bGig;
    int _width;//锚的宽度
};

#endif // ANCHORGRAPHIC_H
