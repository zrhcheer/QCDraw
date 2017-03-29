#ifndef LOADGRAPHIC_H
#define LOADGRAPHIC_H

#include"graphicbase.h"

class LoadGraphic : public GraphicBase
{
    Q_OBJECT
public:
    LoadGraphic();
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
    //�������ӵ�λ��
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
        _size.setWidth(height / 2);
    }
private:
    static const QString _devName;//�豸����
};

#endif // LOADGRAPHIC_H
