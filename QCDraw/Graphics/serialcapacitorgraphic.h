#ifndef SERIALCAPACITORGRAPHIC_H
#define SERIALCAPACITORGRAPHIC_H
#include "graphicbase.h"

class SerialCapacitorGraphic : public GraphicBase
{
public:
    SerialCapacitorGraphic();
    //��ͼ
    virtual void drawGraphic(QPainter *painter);
    virtual void prepareGraphic(QPainter *painter);
    //��ȡ�豸����
    virtual const QString& getDevName() const
    {
        return _devName;
    }
    //��ȡ���ӵ�λ��
    virtual QPointF  getPortPos(int pos);
    //���������ӵ�λ��
    virtual void loadPortPos();
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
        _size.setWidth(height / 3);
    }
private:
    static const QString _devName;//�豸����
};

#endif // SERIALCAPACITORGRAPHIC_H
