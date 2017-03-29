#ifndef SELFTRANSGRAPHIC_H
#define SELFTRANSGRAPHIC_H

#include "transgraphic.h"

class EarthGraphic;
class SelfTransGraphic : public TransGraphic
{
public:
    SelfTransGraphic();
    //��ͼ
    virtual void drawGraphic(QPainter *painter);
    virtual void prepareGraphic(QPainter *painter);
    //��ȡ���ӵ�λ��
    virtual QPointF  getPortPos(int pos);
    //�������ӵ�λ��
    virtual void loadPortPos();
    //�Ƿ���Ծ���
    virtual bool hasMirror()
    {
        return true;
    }
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
        _size.setWidth(height * 4 / (5 + CROSS_PERCENT));
    }
    //���ñ�����С
    virtual void setScale(const float& scale)
    {
        setSize(BASIC_RADIUS * 3 * scale);
    }

private:
    //��þ���
    void drawMirror(QPainter *painter,int neg);
    //���ؾ�������ӵ�λ��
    void loadPortPosMirror(int neg);
    static const QString _devName;//�豸����
};

#endif // SELFTRANSGRAPHIC_H
