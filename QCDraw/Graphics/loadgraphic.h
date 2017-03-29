#ifndef LOADGRAPHIC_H
#define LOADGRAPHIC_H

#include"graphicbase.h"

class LoadGraphic : public GraphicBase
{
    Q_OBJECT
public:
    LoadGraphic();
    //画图
    virtual void drawGraphic(QPainter *painter);
    virtual void prepareGraphic(QPainter *painter);
    //获取设备名称
    virtual const QString& getDevName() const
    {
        return _devName;
    }
    //获取链接点位置
    virtual QPointF  getPortPos(int pos);
    //加载链接点位置
    virtual void loadPortPos();
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
        _size.setWidth(height / 2);
    }
private:
    static const QString _devName;//设备名称
};

#endif // LOADGRAPHIC_H
