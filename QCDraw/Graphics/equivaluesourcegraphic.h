#ifndef EQUIVALUESOURCEGRAPHIC_H
#define EQUIVALUESOURCEGRAPHIC_H

#include "graphicbase.h"
#define CONTROLSTYLE 3

class EquiValueSourceGraphic : public GraphicBase
{
public:
    EquiValueSourceGraphic();
    //��ͼ
    virtual void drawGraphic(QPainter *painter);
    virtual void prepareGraphic(QPainter *painter);
    //���ô�С
    void setSize(const int &height);
    //��ȡ�豸����
    virtual const QString& getDevName() const
    {
        return _devName;
    }
    //��ȡ���ӵ�λ��
    virtual QPointF  getPortPos(int pos);
    //���ñ�����С
    virtual void setScale(const float& scale)
    {
        setSize(BASIC_RADIUS * 3 / 2 * scale);
    }
    //�������ӵ�λ��
    virtual void loadPortPos();
private:
    bool _bOpen;//����״̬
    static const QString _devName;//�豸����
};

#endif // EQUIVALUESOURCEGRAPHIC_H
