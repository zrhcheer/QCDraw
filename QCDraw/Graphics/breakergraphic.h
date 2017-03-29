#ifndef BREAKERGRAPITEM_H
#define BREAKERGRAPITEM_H

#include "switchgraphic.h"

class BreakerGraphic : public SwitchGraphic
{
    Q_OBJECT
public:
    BreakerGraphic();
    //��ͼ
    virtual void drawGraphic(QPainter *painter);
    virtual void prepareGraphic(QPainter *painter);
    //��ȡ�豸����
    virtual const QString& getDevName() const
    {
        return _devName;
    }
    //�����豸����
    virtual void loadPortPos();
private:
    static const QString _devName;//�豸����
//    QPointF _beginJoin;
//    QPointF _endJoin;
};

#endif // BREAKERGRAPITEM_H
