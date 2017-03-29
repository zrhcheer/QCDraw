#ifndef TRANSFORMER2GRAPHIC_H
#define TRANSFORMER2GRAPHIC_H

#include "transgraphic.h"

class EarthGraphic;
class Transformer2Graphic  : public TransGraphic
{
    Q_OBJECT
public:
    Transformer2Graphic();
    //��ͼ
    virtual void drawGraphic(QPainter *painter);
    virtual void prepareGraphic(QPainter *painter);
    //��ȡ���ӵ�λ��
    virtual QPointF  getPortPos(int pos);
    //�������ӵ�λ��
    virtual void loadPortPos();
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
        _size.setWidth(height * 2 / (4 + CROSS_PERCENT*2));
    }
    //���ñ�����С
    virtual void setScale(const float& scale)
    {
        setSize(BASIC_RADIUS * 3 * scale);
    }
private:
    static const QString _devName;//�豸����
};

#endif // TRANSFORMER2GRAPHIC_H
