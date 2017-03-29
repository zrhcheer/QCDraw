#ifndef WIDGETGRAPHICBASE_H
#define WIDGETGRAPHICBASE_H

#include "Graphics/graphic.h"
#include <QWidget>
#include <QHBoxLayout>

class WidgetGraphicBase : public QWidget,public Graphic
{
public:
    WidgetGraphicBase(QWidget* parent = 0);
    //ȷ�Ͽɼ�
    virtual void ensureVisible()
    {
    }

//    virtual void restoreGraphic(QDataStream& dataStream) = 0;
//    virtual void saveGraphic(QDataStream& dataStream) const=0;
    //��ȡ���ӵ�
    virtual QVector<GraphicPort>& getPorts()
    {
        return _vecPort;
    }
    //��ȡ���ӵ�λ��
    virtual QPointF  getPortPos(int pos)
    {
        UNUSED(pos);
        return QPointF(0,0);
    }
    //ɾ������
    virtual bool  delLink(int selPos,Graphic* graphic)
    {
        UNUSED(selPos);
        UNUSED(graphic);
        return false;
    }
    //ɾ������
    virtual bool delJoin(int selPos)
    {
        UNUSED(selPos);
        return false;
    }

    //��ȡ��С
    virtual const QSize& getSize() const
    {
        assert(false);
        return _minSize;
    }
    //����λ��
    virtual void setPosition(const QPointF& pos)
    {
        this->move(pos.toPoint());
    }
    //��ȡλ��
    virtual QPointF getPosition() const
    {
        return QPointF(this->pos());
    }
    //����
    virtual void updateShape()
    {
        this->update();
    }
    //�жϸ��ĵ��Ƿ��ڴ�����
    virtual bool isPointOver(const QPointF& point) const;
    //��ȡ��ͼ
    virtual Graphic* parentGraphic()
    {
        return NULL;
    }
     //��ȡ�豸����
    virtual const QString& getDevName() const = 0;
    //�õ��Ŵ���С�ķ���
    virtual int getSizeChangeFlag(const QPointF& point);
//    //���ù��
//    virtual bool setCursorForSize(int sizeFlag);
//    //���ù��
//    virtual bool setCursorForID(int id);
    //��ĳһ����ı��С
    virtual void changeSizeFromSide(const QPointF& curPoint,const int& sizeFlag);

    //���õ�ǰ�ؼ�
    void setCurWidget(QWidget* curWidget);
protected:
    virtual void	paintEvent ( QPaintEvent * event );
    bool _bHorChange;
    bool _bVerChange;
    QSize _minSize;//���ڱ�����С��С
    QWidget* _curWidget;//���ڱ��浱ǰ�ؼ�
    QHBoxLayout* _topLayout;//��������ˮƽ����

    QVector<GraphicPort> _vecPort;//���ڱ������ӵ�
};

#endif // WIDGETGRAPHICBASE_H
