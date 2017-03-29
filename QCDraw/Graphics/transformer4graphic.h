#ifndef TRANSFORMER4GRAPHIC_H
#define TRANSFORMER4GRAPHIC_H

#include "transgraphic.h"

class Transformer4Graphic : public TransGraphic
{
    Q_OBJECT
public:
    Transformer4Graphic();
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
    //�Ƿ���Ծ���
    virtual bool hasMirror()
    {
        return true;
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
        _size.setWidth(height / (4 + 2 * CROSS_PERCENT) * 5);
    }
    //���ñ�����С
    virtual void setScale(const float& scale)
    {
        setSize(BASIC_RADIUS * 3 * scale);
    }
private:
    //���ؾ������ӵ�
    void loadPortPosMirror(int neg);
    //��þ���
    void drawMirror(QPainter *painter,int neg);
    static const QString _devName;//�豸����
};

#endif // TRANSFORMER4GRAPHIC_H
