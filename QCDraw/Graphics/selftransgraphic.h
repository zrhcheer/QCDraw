#ifndef SELFTRANSGRAPHIC_H
#define SELFTRANSGRAPHIC_H

#include "transgraphic.h"

class EarthGraphic;
class SelfTransGraphic : public TransGraphic
{
public:
    SelfTransGraphic();
    //画图
    virtual void drawGraphic(QPainter *painter);
    virtual void prepareGraphic(QPainter *painter);
    //获取链接点位置
    virtual QPointF  getPortPos(int pos);
    //加载链接点位置
    virtual void loadPortPos();
    //是否可以镜像
    virtual bool hasMirror()
    {
        return true;
    }
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
        _size.setWidth(height * 4 / (5 + CROSS_PERCENT));
    }
    //设置比例大小
    virtual void setScale(const float& scale)
    {
        setSize(BASIC_RADIUS * 3 * scale);
    }

private:
    //获得镜像
    void drawMirror(QPainter *painter,int neg);
    //加载镜像的链接点位置
    void loadPortPosMirror(int neg);
    static const QString _devName;//设备名称
};

#endif // SELFTRANSGRAPHIC_H
