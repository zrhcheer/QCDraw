#ifndef GROUPGRAPHICBASE_H
#define GROUPGRAPHICBASE_H

#include <QGraphicsItemGroup>
#include "graphicshape.h"

class GroupGraphicBase : public GraphicShape,public QGraphicsItemGroup
{
    Q_OBJECT
public:
    GroupGraphicBase();
    //��ȡ���ӵ�λ��
    virtual QPointF  getPortPos(int pos)
    {
        UNUSED(pos);
        assert(false);
    }
    //ɾ������
    virtual bool delLink(int selPos,Graphic* graphic)
    {
        UNUSED(selPos);
        UNUSED(graphic);
        return true;
    }
    //ɾ������
    virtual bool delJoin(int selPos)
    {
        UNUSED(selPos);
        return  true;
    }
    //ȷ���ɼ�
    virtual void ensureVisible();
    //�ָ�
    virtual void restoreGraphic(QDataStream& dataStream)
    {
        UNUSED(dataStream);
        assert(false);
    }
    virtual void loadXML(rapidxml::xml_node<char> *node)
    {
        UNUSED(node);
    }
    //����
    virtual void saveGraphic(QDataStream& dataStream) const
    {
        UNUSED(dataStream);
        assert(false);
    }
    virtual void saveXML(rapidxml::xml_node<char> *node, rapidxml::xml_document<> &doc,Graphic* graphic)
    {
        UNUSED(node);
        UNUSED(doc);
        UNUSED(graphic);
    }
    //����λ��
    virtual void setPosition(const QPointF& pos)
    {
        UNUSED(pos);
        //assert(false);
    }
    //��ȡλ��
    virtual QPointF getPosition()const
    {
        assert(false);
    }
    //���ô�С
    virtual const QSize& getSize() const
    {
        assert(false);
    }
    //����
    virtual void updateShape()
    {
        this->update();
    }
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
    //��ȡ���ӵ�
    virtual QVector<GraphicPort>& getPorts()
    {
        return _port;
    }
    //�ƶ�ͼ��
    void moveGraphic(const QPointF& point);
private:
    static const QString _devName;//�豸����
    QVector<GraphicPort> _port;//���ڱ������ӵ�
};

#endif // GROUPGRAPHICBASE_H
