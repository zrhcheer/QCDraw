#ifndef SPLITREACTORGRAPHIC_H
#define SPLITREACTORGRAPHIC_H

#include "graphicbase.h"

class SplitReactorGraphic  : public GraphicBase
{
public:
    SplitReactorGraphic();
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
        _size.setWidth(_size.height() * 3 / 4);
    }
    //���ñ�����С
    virtual void setScale(const float& scale)
    {
        setSize(BASIC_RADIUS * 1.5 * scale);
    }
private:
    //��þ���
    void drawMirror(QPainter *painter,int neg);
    //���ؾ������ӵ�λ��
    void loadPortPosMirror(int neg);
    static const QString _devName;//�豸����
//    QPointF _beginJoin;
//    QPointF _endJoin;
//    QPointF _midJoin;
};

#endif // SPLITREACTORGRAPHIC_H
