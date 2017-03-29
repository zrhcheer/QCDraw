#ifndef GROUNDDISCONNECTORGRAPHIC_H
#define GROUNDDISCONNECTORGRAPHIC_H

#include "disconnectorgraphic.h"
#include "earthgraphic.h"

class GroundDisconnectorGraphic: public DisconnectorGraphic
{
public:
    GroundDisconnectorGraphic();
    //��ȡ���ӵ�����
    virtual QPointF  getPortPos(int pos);
    //�������ӵ�����
    virtual void loadPortPos();

    //virtual set<int> queryUnMountPos();
    //��ȡ�豸����
    virtual const QString& getDevName() const
    {
        return _devName;
    }
    //��ȡ���ӵ㼰������
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
    QVector<GraphicPortPoint> _vecPortPoint;//���ڱ������ӵ㼰������
    static const QString _devName;//�豸����
    EarthGraphic* earthGraphic;//�ӵص�
};

#endif // GROUNDDISCONNECTORGRAPHIC_H
