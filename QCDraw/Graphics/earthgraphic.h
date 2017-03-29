#ifndef EARTHGRAPHIC_H
#define EARTHGRAPHIC_H

#include <QGraphicsItem>
#include "graphicbase.h"

class EarthGraphic : public GraphicBase
{
    Q_OBJECT
public:
    EarthGraphic(QGraphicsItem * parent = 0);
    //画图
    virtual void drawGraphic(QPainter *painter);
    virtual void prepareGraphic(QPainter *painter);
    //画被选择的元件
    virtual void drawSelect(QPainter *painter);
    //获取矩形大小
    virtual QRectF boundingRect() const;
    //获取设备名称
    virtual const QString& getDevName() const
    {
        return _devName;
    }
    //设置大小
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
    //设置长度及大小
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
    //获取链接点位置
    virtual QPointF  getPortPos(int pos);
    //设置开合状态
    void setIsOpen(bool bOpen)
    {
        if(  _bOpen != bOpen)
        {
            _bOpen = bOpen;
            update();
        }
    }
    //设置是否是断路器
    void setHasBreaker(bool bBreaker)
    {
        _hasBreaker = bBreaker;
    }
    //设置是否有连出柄
    void setIsLong(const bool isLong)
    {
        _isLong = isLong;
    }

private:
    static const QString _devName;//设备名称
    bool _hasBreaker;//是否是断路器
    bool _bOpen;//开合状态
    int _lenSwitch;//长度
    bool _isLong;//是否有连出柄
    //QPointF _beginJoin;
};

#endif // EARTHGRAPHIC_H
