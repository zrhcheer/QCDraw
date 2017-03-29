#ifndef TRANSFORMER2GRAPHIC_H
#define TRANSFORMER2GRAPHIC_H

#include "transgraphic.h"

class EarthGraphic;
class Transformer2Graphic  : public TransGraphic
{
    Q_OBJECT
public:
    Transformer2Graphic();
    //画图
    virtual void drawGraphic(QPainter *painter);
    virtual void prepareGraphic(QPainter *painter);
    //获取链接点位置
    virtual QPointF  getPortPos(int pos);
    //加载链接点位置
    virtual void loadPortPos();
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
        _size.setWidth(height * 2 / (4 + CROSS_PERCENT*2));
    }
    //设置比例大小
    virtual void setScale(const float& scale)
    {
        setSize(BASIC_RADIUS * 3 * scale);
    }
private:
    static const QString _devName;//设备名称
};

#endif // TRANSFORMER2GRAPHIC_H
