#ifndef TICKGRAPHIC_H
#define TICKGRAPHIC_H
#include "graphic.h"
class TickGraphic : public Graphic,public QGraphicsItem
{
public:
    enum
    {
        TICK_CROSS,//���
        TICK_EXCLA,//��̾��
        TICK_LIGHT//����
    };
    TickGraphic(QGraphicsItem* parent = 0,int flag = TICK_CROSS);
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    //��ȡ���δ�С
    virtual QRectF boundingRect() const;
    //���ñ��λ��
    void setTickPos(const QLineF& line,bool bBegin);
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
    //��ȡ��С
    virtual const QSize& getSize() const
    {
        return _size;
    }
    //����λ��
    virtual void setPosition(const QPointF& pos)
    {
        this->setPos(pos);
    }
    //��ȡλ��
    QPointF getPosition() const
    {
        return this->pos();
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
    //���÷�������
    void setFlag(const int& flag)
    {
        if(flag != _flag)
        {
            _flag = flag;
            update();
        }
    }

protected:
    //���û���
    virtual void prepareGraphic(QPainter *painter);
    //��ͼ
    virtual void drawGraphic(QPainter *painter);
private:
    QSize _size;//��С
    static const QString _devName;//�豸����
    QVector<GraphicPort> _port;//���ڱ������ӵ�
    int _flag;//��������
};

#endif // TICKGRAPHIC_H
