#ifndef WIDTHGRAPHICLINEITEM_H
#define WIDTHGRAPHICLINEITEM_H

#include <QGraphicsLineItem>
#include <QPen>
#include "lineflow.h"
#include <QSet>

class LineFlow;
class WidthGraphicLineItem : public QGraphicsLineItem
{
public:
    WidthGraphicLineItem(qreal x1, qreal y1, qreal x2, qreal y2,QGraphicsItem * parent = 0);
    virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);

    //virtual QRectF boundingRect() const;
    //���û�����ɫ
    void setColor(const QColor& color);
//    const QColor& getColor()const
//    {
//        return _color;
//    }

//    void setMagic(bool bMagic);
//    int getMagic()const
//    {
//        return _bMagic;
//    }
    //������·����/������ɫ��ģʽ
    void setPattern(int outType,const QColor& color,bool bShowOut);

    void setIsFirst(bool bFirst)
    {
        _bFirst = bFirst;
    }
    bool isFirst()
    {
        return _bFirst;
    }
    //����ѡ��״̬
    void setIsSelect(bool bSelect )
    {
        _bSelect = bSelect ;
    }
    //��ȡѡ��״̬
    bool isSelect()
    {
        return _bSelect;
    }

//    void setIsConsumer(bool bConsumer )
//    {
//        _bConsumer = bConsumer;
//    }
//    bool isConsumer()
//    {
//        return _bConsumer;
//    }
    //������·���ͺͻ�������
    void setLineType(int type);
    //���ó�������
    void setOutType(int outType);
    void setIsShowOut(bool bShowOut)
    {
        _bShowOut = bShowOut;
    }

//    void initMove(const QColor& clr,float len,bool bBegin);
//    void initMove(const QColor& clr,bool bBegin);

    bool delMove(LineFlow* flow);
    void addMode(LineFlow* flow);

    //void beginMove(float curPos);
    //bool moveStep(float step);

//    bool isMoveOn()
//    {
//        switch(_moveFlag)
//        {
//        case MOVE_FULL:
//        case MOVE_HALF:
//            return _bOnMove;
//        }
//        return false;
//    }
//    bool isMove()
//    {
//        switch(_moveFlag)
//        {
//        case MOVE_FULL:
//        case MOVE_HALF:
//            return true;
//        }
//        return false;
//    }

//    enum
//    {
//        MOVE_FULL,
//        MOVE_HALF,
//        MOVE_NO
//    };
private:
    void drawMove(QPainter *painter);
    bool _bFirst;
    bool _bSelect;//ѡ��״̬
    //int _lineWidth;
    int _type;//����
    int _outType;//��������
    bool _bShowOut;
    QPen _pen;//����

    //�ƶ����
    QSet<LineFlow*> _flow;
//    QColor _clrMove;
//    int _moveFlag;
//    bool _bBegin;
//    bool _bOnMove;
//    float _lenMove;
//    float _curPos;

//    QColor _color;
//    Qt::PenStyle _penStyle;
};

#endif // WIDTHGRAPHICLINEITEM_H
