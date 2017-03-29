#ifndef BREAKERGRAPITEM_H
#define BREAKERGRAPITEM_H

#include "switchgraphic.h"

class BreakerGraphic : public SwitchGraphic
{
    Q_OBJECT
public:
    BreakerGraphic();
    //画图
    virtual void drawGraphic(QPainter *painter);
    virtual void prepareGraphic(QPainter *painter);
    //获取设备名称
    virtual const QString& getDevName() const
    {
        return _devName;
    }
    //加载设备名称
    virtual void loadPortPos();
private:
    static const QString _devName;//设备名称
//    QPointF _beginJoin;
//    QPointF _endJoin;
};

#endif // BREAKERGRAPITEM_H
