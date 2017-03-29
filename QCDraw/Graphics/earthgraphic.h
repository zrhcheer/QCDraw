#ifndef EARTHGRAPHIC_H
#define EARTHGRAPHIC_H

#include <QGraphicsItem>
#include "graphicbase.h"

class EarthGraphic : public GraphicBase
{
    Q_OBJECT
public:
    EarthGraphic(QGraphicsItem * parent = 0);
    //��ͼ
    virtual void drawGraphic(QPainter *painter);
    virtual void prepareGraphic(QPainter *painter);
    //����ѡ���Ԫ��
    virtual void drawSelect(QPainter *painter);
    //��ȡ���δ�С
    virtual QRectF boundingRect() const;
    //��ȡ�豸����
    virtual const QString& getDevName() const
    {
        return _devName;
    }
    //���ô�С
    virtual void setSize(const int& width)
    {
        if(width < SQARE_MIN_SIZE )
        {
            _size.setWidth(SQARE_MIN_SIZE);
        }
        else
        {
            _size.setWidth(width + 5);
        }
        float square = _size.width() / 3.0;
        int height;
        if(_hasBreaker)
        {
            height = _lenSwitch + square * 7;
        }
        else
        {
            height = _lenSwitch + square * 4;
        }

        _size.setHeight(height);
    }
    //���ó��ȼ���С
    void setSwitchLen(const int& lenSwitch)
    {
        if(_lenSwitch != lenSwitch)
        {
            _lenSwitch = lenSwitch;
            float square = _size.width() / 3.0;
           int height;
           if(_hasBreaker)
           {
               height = _lenSwitch + square * 7;
           }
           else
           {
               height = _lenSwitch + square * 4;
           }
           _size.setHeight(height);
        }
    }
    //��ȡ���ӵ�λ��
    virtual QPointF  getPortPos(int pos);
    //���ÿ���״̬
    void setIsOpen(bool bOpen)
    {
        if(  _bOpen != bOpen)
        {
            _bOpen = bOpen;
            update();
        }
    }
    //�����Ƿ��Ƕ�·��
    void setHasBreaker(bool bBreaker)
    {
        _hasBreaker = bBreaker;
    }
    //�����Ƿ���������
    void setIsLong(const bool isLong)
    {
        _isLong = isLong;
    }

private:
    static const QString _devName;//�豸����
    bool _hasBreaker;//�Ƿ��Ƕ�·��
    bool _bOpen;//����״̬
    int _lenSwitch;//����
    bool _isLong;//�Ƿ���������
    //QPointF _beginJoin;
};

#endif // EARTHGRAPHIC_H
