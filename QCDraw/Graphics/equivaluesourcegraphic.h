#ifndef EQUIVALUESOURCEGRAPHIC_H
#define EQUIVALUESOURCEGRAPHIC_H

#include "graphicbase.h"
#define CONTROLSTYLE 3

class EquiValueSourceGraphic : public GraphicBase
{
public:
    EquiValueSourceGraphic();
    //画图
    virtual void drawGraphic(QPainter *painter);
    virtual void prepareGraphic(QPainter *painter);
    //设置大小
    void setSize(const int &height);
    //获取设备名称
    virtual const QString& getDevName() const
    {
        return _devName;
    }
    //获取链接点位置
    virtual QPointF  getPortPos(int pos);
    //设置比例大小
    virtual void setScale(const float& scale)
    {
        setSize(BASIC_RADIUS * 3 / 2 * scale);
    }
    //加载链接点位置
    virtual void loadPortPos();
private:
    bool _bOpen;//开合状态
    static const QString _devName;//设备名称
};

#endif // EQUIVALUESOURCEGRAPHIC_H
