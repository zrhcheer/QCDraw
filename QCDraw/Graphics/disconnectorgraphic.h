#ifndef DISCONNECTORGRAPHIC_H
#define DISCONNECTORGRAPHIC_H

#include "switchgraphic.h"
#define BAR_SIZE 4
class DisconnectorGraphic  : public SwitchGraphic
{
public:
    DisconnectorGraphic();
    //��ͼ
    virtual void drawGraphic(QPainter *painter);
    virtual void prepareGraphic(QPainter *painter);
    //��ȡ�豸����
    virtual const QString& getDevName() const
    {
        return _devName;
    }
    //���ô�С
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
    //���ñ�����С
    virtual void setScale(const float& scale)
    {
        setSize(BASIC_SQARE  *  scale);
    }

    //�������ӵ�λ��
    virtual void loadPortPos();
protected:
    static const QString _devName;//�豸����
//    QPointF _beginJoin;
//    QPointF _endJoin;
};

#endif // SWITCHGRAPHIC_H
