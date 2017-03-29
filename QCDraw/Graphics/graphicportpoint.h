#ifndef GRAPHICPORTPOINT_H
#define GRAPHICPORTPOINT_H

#include "anchorgraphic.h"

#include <QPointF>
class Graphic;
class GraphicPortPoint
{
public:
    enum
    {
        JOIN_ALL,//元件上所有点
        JOIN_SINLE,//元件上此点可连接一个
        JOIN_MUTI//元件上此点可连接多个
    };
    GraphicPortPoint() :
        _joinPoint(0,0)
    {
        _joinType = JOIN_SINLE;
        //_isNeedJoin = false;
        _anchor = NULL;
    }
    //获取链接类型
    const int& getJoinType()
    {
        return _joinType;
    }
    //设置链接类型
    void setJoinType(const int& selPos)
    {
        _joinType = selPos;
    }
    //获取链接点
    const QPointF& getJoinPoint()
    {
        return _joinPoint;
    }
    //设置链接点
    void setJoinPoint(const QPointF& joinPoint);

//    bool getIsNeedJoin()
//    {
//        return _isNeedJoin;
//    }
//    void setIsNeedJoin(const bool isNeedJoin)
//    {
//        _isNeedJoin = isNeedJoin;
//    }
    //隐藏锚
    void hideAnchor()
    {
        if(_anchor)
        {
            _anchor->hide();
        }
    }
    //显示锚
    void showAnchor(Graphic* parent,int selPos);

private:
    AnchorGraphic* _anchor;//锚
    //bool _isNeedJoin;
    int _joinType;//链接类型
    QPointF _joinPoint;//链接点
};

#endif // GRAPHICPORTPOINT_H
