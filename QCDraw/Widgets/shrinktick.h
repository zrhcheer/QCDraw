#ifndef SHRINKTICK_H
#define SHRINKTICK_H

#include <QWidget>
#include <QTableWidget>
#include "ChaDong/roundandquardrangle.h"
#include <QGraphicsProxyWidget>

#include "shrinkwidget.h"
#include "Graphics/graphic.h"

class ShrinkTick : public QGraphicsProxyWidget ,public Graphic
{
    Q_OBJECT
public:
    explicit ShrinkTick(QGraphicsItem *parent=0);
    virtual ~ShrinkTick();
    void addShrink(const QString& name,const CdData& shrinkData);


    //�ָ�
    virtual void restoreGraphic(QDataStream& dataStream);
    virtual void loadXML(rapidxml::xml_node<char> *node);
    //����
    virtual void saveGraphic(QDataStream& dataStream) const;
    virtual void saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic);

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
        this->setPos(pos.toPoint());
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
    virtual const QString& getDevName() const
    {
        return _devName;
    }

protected:
    virtual void	mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event );
signals:
public slots:

private:
    ShrinkWidget* _tabWid;

    QSize _minSize;//���ڱ�����С��С
     QVector<GraphicPort> _vecPort;//���ڱ������ӵ�
     static const QString _devName;//�豸����

     bool _bTiny;
};

#endif // SHRINKTICK_H
