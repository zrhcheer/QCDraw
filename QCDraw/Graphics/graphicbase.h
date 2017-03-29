#ifndef GRAPHICBASE_H
#define GRAPHICBASE_H

#include <QPainter>
#include <string>
using namespace std;
#include <QGraphicsItem>
#include "captiongraphic.h"
#include "graphicshape.h"
#include "graphicport.h"
#include "busgraphic.h"
#include "groupgraphicbase.h"
#include "groupdeal.h"
#include "tickgraphic.h"


#define ELE_MIN_SIZE 25
#define SQARE_MIN_SIZE 5

class BusGraphic;
class LineGraphic;
class GraphicBase : public GraphicShape, public QGraphicsItem
{
    Q_OBJECT
public:
    GraphicBase(QGraphicsItem * parent = 0);
    //��ͼ
    virtual void drawGraphic(QPainter *painter) = 0;
    virtual void prepareGraphic(QPainter *painter);
    //����ѡ���Ԫ��
    virtual void drawSelect(QPainter *painter);
    virtual void drawLock(QPainter *painter);
    //void drawPort(QPainter *painter);
    //ȷ���ɼ�
    virtual void ensureVisible()
    {
        QGraphicsItem::ensureVisible();
    }
    //������ɫ
    virtual void setColor(const QColor& color)
    {
        if(_color != color)
        {
            _color = color;
            this->update();
        }
    }
    //��ʾê
    virtual void showPortAnchor(int selPos);
    //����ê
    virtual void hidePortAnchor(int selPos);
    virtual void hidePortAnchor();
    //�Ƿ�����
    virtual bool isJointed(int selPos);
    //ɾ������
    virtual bool delLink(int selPos,Graphic* graphic);
    virtual bool delJoin(int selPos);

    void unlinkGraphic(); //ɾ����վ����
    //��ͼ
    virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    //��ȡ���δ�С
    virtual QRectF boundingRect() const;
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
    //�ָ�
    virtual void restoreGraphic(QDataStream& dataStream);
    virtual void loadXML(rapidxml::xml_node<char>*node);
    //����
    virtual void saveGraphic(QDataStream& dataStream) const;
    virtual void saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic);

    //��ȡ���Ƕ˵�����ӵ�λ�ø���
    virtual set<int> queryUnMountPos();
    //һ��Ϊĸ�ߣ���Ķ�Ϊ��·��������ĸ���ƶ�
    bool moveAroundBus(const QPointF& point);
    //����λ��
    virtual void setPosition(const QPointF& pos);
    //��ȡλ��
    QPointF getPosition() const
    {
        return this->pos();
    }
    //�õ��Ŵ���С�ķ���
    virtual int getSizeChangeFlag(const QPointF& point);
    //�жϸ��ĵ��Ƿ��ڴ�����
    virtual bool isPointOver(const QPointF& point) const;
    //��ȡ��С
    virtual const QSize& getSize() const
    {
        return _size;
    }
    //�������ǳ�����ķ�֮һ
    virtual void setSize(const int& height)
    {
        if(height < ELE_MIN_SIZE)
        {
            _size.setHeight(ELE_MIN_SIZE);
        }
        else
        {
            _size.setHeight(height);
        }
        _size.setWidth(height / 4);
    }
    //���ñ�����С
    virtual void setScale(const float& scale)
    {
        setSize(BASIC_SQARE * 2 * scale);
    }

    //��ȡ�豸����
    virtual const QString& getDevName()const = 0;
    //���ñ�ǩ
    virtual  void setCaption(const QString& caption);
    void setCaption(const QString& caption,const QPointF& pos);
    //���ñ�ǩλ��
    void setCaptionPos(const QPointF& pos)
    {
        if(_captionGraphic)
        {
            _captionGraphic->setPos(pos);
        }
    }
    //������·
    virtual void setLine(LineGraphic* lineGraphic,int pos)
    {
        UNUSED(lineGraphic);
        UNUSED(pos);
    }


    //�����������账����ֵ
    //Ԫ����Ԫ������
    virtual GroupDeal setPortBasic(int direct,GraphicBase* basicGraphic,int directOther);
    //busPos ��ĸ�߿�ʼ������Ϊ0-1
    virtual GroupDeal setPortBus(int direct,BusGraphic* busGraphic,const double& busPos);
    virtual GroupDeal setPortBus(int direct,BusGraphic* busGraphic);
    virtual void setPortGraphic(int pos,Graphic* joint,int posLink);
//    virtual QPointF  getPortPos(int pos)
//    {
//        return this->pos();
//    }
    //�������ӵ�λ��
    virtual void loadPortPos(){}
    //��ʼ������
    GroupDeal initLink(map<ulong64,Graphic*>& allElement);
    //��ȡ���ӵ�
    virtual QVector<GraphicPort>& getPorts()
    {
        return _port;
    }
    //���ñ��
    void setTick(bool bTick,int flag=TickGraphic::TICK_CROSS);
    //���ñ����ɫ
    void setTickColor(const QColor& clr);

protected:
    //Ԫ�����ӵ�basicGraphic
    virtual void setJointGraphic(int direct,GraphicBase* basicGraphic,int directOther);
    //Ԫ������firstItem�t�ŵ�һ���M��
    GroupDeal groupGraphicItem(BusGraphic* firstItem);
    GroupDeal groupGraphicItem(GraphicBase* firstItem);
    QVector<GraphicPort> _port;//���ڱ������ӵ�
    CaptionGraphic* _captionGraphic;//��ǩ
    QSize _size;//��С
    TickGraphic* _tickGraphic;//���
    int _ref;
};

#endif // GRAPHICBASE_H
