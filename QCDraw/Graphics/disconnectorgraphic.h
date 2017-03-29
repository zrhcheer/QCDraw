#ifndef DISCONNECTORGRAPHIC_H
#define DISCONNECTORGRAPHIC_H

#include "switchgraphic.h"
#define BAR_SIZE 4
class DisconnectorGraphic  : public SwitchGraphic
{
public:
    DisconnectorGraphic();
    //画图
    virtual void drawGraphic(QPainter *painter);
    virtual void prepareGraphic(QPainter *painter);
    //获取设备名称
    virtual const QString& getDevName() const
    {
        return _devName;
    }
    //设置大小
    virtual void setSize(const int& height)
    {
        if(height < ELE_MIN_SIZE)
        {
            _size.setHeight(ELE_MIN_SIZE);
        }
        else
        {
            _size.setHeight(height);
        }
        _size.setWidth(height -BAR_SIZE);
    }
    //设置比例大小
    virtual void setScale(const float& scale)
    {
        setSize(BASIC_SQARE  *  scale);
    }

    //加载链接点位置
    virtual void loadPortPos();
protected:
    static const QString _devName;//设备名称
//    QPointF _beginJoin;
//    QPointF _endJoin;
};

#endif // SWITCHGRAPHIC_H
