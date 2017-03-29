#ifndef GROUNDREACTORGRAPHIC_H
#define GROUNDREACTORGRAPHIC_H

#include "reactorgraphic.h"
#include "earthgraphic.h"

class GroundReactorGraphic : public ReactorGraphic
{
    Q_OBJECT
public:
    GroundReactorGraphic();
    //获取链接点位置
    virtual QPointF  getPortPos(int pos);
    //加载链接点位置
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

#endif // GROUNDREACTOR_H
