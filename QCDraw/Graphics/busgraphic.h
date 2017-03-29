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
    //获取链接点位置
    virtual QPointF  getPortPos(int pos)
    {
        UNUSED(pos);
        assert(false);
    }
    //删除链接
    virtual bool delLink(int selPos,Graphic* graphic);
    virtual bool delJoin(int selPos);

    //设置颜色
    virtual void setColor(const QColor& color);
    //确保可见
    virtual void ensureVisible()
    {
        QGraphicsItem::ensureVisible();
    }
    //恢复
    virtual void restoreGraphic(QDataStream& dataStream);
    virtual void loadXML(rapidxml::xml_node<char> *node);
    //保存
    virtual void saveGraphic(QDataStream& dataStream) const;
    virtual void saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic);
    //获取大小
    virtual const QSize& getSize() const;
    //设置母线位置
    virtual void setPosition(const QPointF& pos);
    //获取母线位置
    QPointF getPosition() const
    {
        return this->pos();
    }
    //是否链接
    virtual bool isJointed(int selPos)
    {
        UNUSED(selPos);
        return false;
    }
    //查询拐点
    int queryKneeNode(const QPointF& point);
    //设置拐点位置
    void setKneePos(int kneeIndex,const QPointF& point);
    //画图
    virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    //更新
    virtual void updateShape()
    {
        this->update();
    }
    //获取父图
    virtual Graphic* parentGraphic()
    {
        return dynamic_cast<Graphic*>(this->parentItem());
    }
    //获取设备名称
    virtual const QString& getDevName() const
    {
        return _devName;
    }
    //元件链接到母线
    void setJoinGraphic(Graphic* joinGraphic,int pos);
    //设置标签
    virtual void setCaption(const QString& caption);
    //初始化链接
    GroupDeal initLink(map<ulong64,Graphic*>& allElement);
    //获取链接点
    virtual QVector<GraphicPort>& getPorts()
    {
        return _port;
    }
private:
    //QMap<Graphic*,int> _joinGraphic;
    QVector<GraphicPort> _port;//用于保存链接点

    CaptionGraphic* _captionGraphic;//标签
    static const QString _devName;//设备名称
    int _busWidth;//母线宽度
    QSize _size;//用于保存大小
};

#endif // BUSGRAPHIC_H
