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
        JOIN_ALL,//Ԫ�������е�
        JOIN_SINLE,//Ԫ���ϴ˵������һ��
        JOIN_MUTI//Ԫ���ϴ˵�����Ӷ��
    };
    GraphicPortPoint() :
        _joinPoint(0,0)
    {
        _joinType = JOIN_SINLE;
        //_isNeedJoin = false;
        _anchor = NULL;
    }
    //��ȡ��������
    const int& getJoinType()
    {
        return _joinType;
    }
    //������������
    void setJoinType(const int& selPos)
    {
        _joinType = selPos;
    }
    //��ȡ���ӵ�
    const QPointF& getJoinPoint()
    {
        return _joinPoint;
    }
    //�������ӵ�
    void setJoinPoint(const QPointF& joinPoint);

//    bool getIsNeedJoin()
//    {
//        return _isNeedJoin;
//    }
//    void setIsNeedJoin(const bool isNeedJoin)
//    {
//        _isNeedJoin = isNeedJoin;
//    }
    //����ê
    void hideAnchor()
    {
        if(_anchor)
        {
            _anchor->hide();
        }
    }
    //��ʾê
    void showAnchor(Graphic* parent,int selPos);

private:
    AnchorGraphic* _anchor;//ê
    //bool _isNeedJoin;
    int _joinType;//��������
    QPointF _joinPoint;//���ӵ�
};

#endif // GRAPHICPORTPOINT_H
