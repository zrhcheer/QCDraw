#ifndef BUSGRAPHIC_H
#define BUSGRAPHIC_H

#include <QGraphicsLineItem>
#include <string>
using namespace std;
#include "graphicshape.h"
#include "graphicbase.h"
#include "graphicport.h"
#include "groupdeal.h"


class GraphicBase;
class BusGraphic : public GraphicShape,public QGraphicsLineItem
{
    Q_OBJECT
public:
    BusGraphic();
    BusGraphic(const QPointF& begin,const QPointF& end);
    //��ȡ���ӵ�λ��
    virtual QPointF  getPortPos(int pos)
    {
        UNUSED(pos);
        assert(false);
    }
    //ɾ������
    virtual bool delLink(int selPos,Graphic* graphic);
    virtual bool delJoin(int selPos);

    //������ɫ
    virtual void setColor(const QColor& color);
    //ȷ���ɼ�
    virtual void ensureVisible()
    {
        QGraphicsItem::ensureVisible();
    }
    //�ָ�
    virtual void restoreGraphic(QDataStream& dataStream);
    virtual void loadXML(rapidxml::xml_node<char> *node);
    //����
    virtual void saveGraphic(QDataStream& dataStream) const;
    virtual void saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic);
    //��ȡ��С
    virtual const QSize& getSize() const;
    //����ĸ��λ��
    virtual void setPosition(const QPointF& pos);
    //��ȡĸ��λ��
    QPointF getPosition() const
    {
        return this->pos();
    }
    //�Ƿ�����
    virtual bool isJointed(int selPos)
    {
        UNUSED(selPos);
        return false;
    }
    //��ѯ�յ�
    int queryKneeNode(const QPointF& point);
    //���ùյ�λ��
    void setKneePos(int kneeIndex,const QPointF& point);
    //��ͼ
    virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    //����
    virtual void updateShape()
    {
        this->update();
    }
    //��ȡ��ͼ
    virtual Graphic* parentGraphic()
    {
        return dynamic_cast<Graphic*>(this->parentItem());
    }
    //��ȡ�豸����
    virtual const QString& getDevName() const
    {
        return _devName;
    }
    //Ԫ�����ӵ�ĸ��
    void setJoinGraphic(Graphic* joinGraphic,int pos);
    //���ñ�ǩ
    virtual void setCaption(const QString& caption);
    //��ʼ������
    GroupDeal initLink(map<ulong64,Graphic*>& allElement);
    //��ȡ���ӵ�
    virtual QVector<GraphicPort>& getPorts()
    {
        return _port;
    }
private:
    //QMap<Graphic*,int> _joinGraphic;
    QVector<GraphicPort> _port;//���ڱ������ӵ�

    CaptionGraphic* _captionGraphic;//��ǩ
    static const QString _devName;//�豸����
    int _busWidth;//ĸ�߿��
    QSize _size;//���ڱ����С
};

#endif // BUSGRAPHIC_H
