#ifndef CAPTIONGRAPHIC_H
#define CAPTIONGRAPHIC_H

#include <QGraphicsItem>
#include <QFont>
#include "graphic.h"


class CaptionGraphic : public Graphic,public QGraphicsItem
{
public:
    CaptionGraphic();
    CaptionGraphic(QGraphicsItem* parent = 0);
    CaptionGraphic(const QString& strText,QGraphicsItem* parent = 0);
    //��ͼ
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    //��ȡ���δ�С
    virtual QRectF boundingRect() const;
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
        return true;
    }
    //ȷ���ɼ�
    virtual void ensureVisible()
    {
        QGraphicsItem::ensureVisible();
    }

    int fontWidth();//������
    int fonrHeight();//����߶�
    //��ȡ���ӵ�λ��
    virtual QPointF  getPortPos(int pos)
    {
        UNUSED(pos);
        assert(false);
    }
    //�ָ�
    virtual void restoreGraphic(QDataStream& dataStream);
    virtual void loadXML(rapidxml::xml_node<char> *node);
    //����
    virtual void saveGraphic(QDataStream& dataStream) const;
    virtual void saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic);
    //����
    virtual void updateShape()
    {
        this->update();
    }
    //��ȡ���ӵ�
    virtual QVector<GraphicPort>& getPorts()
    {
        return _port;
    }
    //��ȡ��ǩ��С
    virtual const QSize& getSize() const
    {
        return _size;
    }
    //���ñ�ǩλ��
    virtual void setPosition(const QPointF& pos)
    {
        this->setPos(pos);
    }
    //��ȡ��ǩλ��
    QPointF getPosition() const
    {
        return this->pos();
    }
    //��ȡ��ͼ
    virtual Graphic* parentGraphic()
    {
        return dynamic_cast<Graphic*>(this->parentItem());
    }
    //���ñ�ǩ�ı�
    void setText(const QString& strText);
    //��ȡ��ǩ�ı�
    const QString& getText() const
    {
        return _text;
    }
    //��ȡ�豸����
    virtual const QString& getDevName() const
    {
        return _devName;
    }
protected:
    //��ͼ
    virtual void prepareGraphic(QPainter *painter);
    virtual void drawGraphic(QPainter *painter);
private:
    //QString _caption;
    QSize _size;//��ǩ��С
    QFont _font;//��ǩ����
    QString _text;//��ǩ�ı�
    static const QString _devName;//�豸����
    QVector<GraphicPort> _port;//���ڱ������ӵ�
};

#endif // CAPTIONGRAPHIC_H
