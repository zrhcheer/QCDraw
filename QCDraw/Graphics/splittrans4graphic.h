#ifndef SPLITTRANS4GRAPHIC_H
#define SPLITTRANS4GRAPHIC_H

#include "transgraphic.h"

class SplitTrans4Graphic : public TransGraphic
{
    Q_OBJECT
public:
    SplitTrans4Graphic();
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
    //是否可以镜像
    virtual bool hasMirror()
    {
        return true;
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
        _size.setWidth((height*2 / (4 + CROSS_PERCENT*2))*(1 + RADIUS2_PERCENT));
    }
    //设置比例大小
    virtual void setScale(const float& scale)
    {
        setSize(BASIC_RADIUS * 3 * scale);
    }
private:
    //加载镜像链接点
    void loadPortPosMirror(int neg);
    //获得镜像
    void drawMirror(QPainter *painter,int neg);
    static const QString _devName;//设备名称
};

#endif // SPLITTRANS4GRAPHIC_H
