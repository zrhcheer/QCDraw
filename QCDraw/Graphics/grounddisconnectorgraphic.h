#ifndef GROUNDDISCONNECTORGRAPHIC_H
#define GROUNDDISCONNECTORGRAPHIC_H

#include "disconnectorgraphic.h"
#include "earthgraphic.h"

class GroundDisconnectorGraphic: public DisconnectorGraphic
{
public:
    GroundDisconnectorGraphic();
    //获取链接点类型
    virtual QPointF  getPortPos(int pos);
    //加载链接点类型
    virtual void loadPortPos();

    //virtual set<int> queryUnMountPos();
    //获取设备名称
    virtual const QString& getDevName() const
    {
        return _devName;
    }
    //获取链接点及其类型
    virtual QVector<GraphicPortPoint>&  getJoinPortPoint()
    {
        if(_vecPortPoint.empty())
        {
            _vecPortPoint.resize(1);
            _vecPortPoint[0] = _portPoints[0];
        }
        return _vecPortPoint;
    }
private:
    QVector<GraphicPortPoint> _vecPortPoint;//用于保存链接点及其类型
    static const QString _devName;//设备名称
    EarthGraphic* earthGraphic;//接地点
};

#endif // GROUNDDISCONNECTORGRAPHIC_H
