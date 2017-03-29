#ifndef ANCHORGRAPHIC_H
#define ANCHORGRAPHIC_H

#include <QGraphicsItem>

class AnchorGraphic : public QGraphicsItem//ê
{
public:
    AnchorGraphic(bool bBig,QGraphicsItem *parent = 0);
    virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    //��ȡ���δ�С
    virtual QRectF boundingRect() const;

    void setIsBig(const bool& bGig);

private:
    bool _bGig;
    int _width;//ê�Ŀ��
};

#endif // ANCHORGRAPHIC_H
