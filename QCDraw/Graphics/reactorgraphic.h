#ifndef REACTORGRAPHIC_H
#define REACTORGRAPHIC_H

#include "graphicbase.h"

class ReactorGraphic  : public GraphicBase
{
    Q_OBJECT
public:
    ReactorGraphic();
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
        _size.setWidth(height / 2);
    }
    //���ñ�����С
    virtual void setScale(const float& scale)
    {
        setSize(BASIC_RADIUS * 1.2 * scale);
    }
protected:
    static const QString _devName;//�豸����
//    QPointF _beginJoin;
//    QPointF _endJoin;
};

#endif // REACTORGRAPHIC_H
