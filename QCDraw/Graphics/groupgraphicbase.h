#ifndef GROUPGRAPHICBASE_H
#define GROUPGRAPHICBASE_H

#include <QGraphicsItemGroup>
#include "graphicshape.h"

class GroupGraphicBase : public GraphicShape,public QGraphicsItemGroup
{
    Q_OBJECT
public:
    GroupGraphicBase();
    //获取链接点位置
    virtual QPointF  getPortPos(int pos)
    {
        UNUSED(pos);
        assert(false);
    }
    //删除链接
    virtual bool delLink(int selPos,Graphic* graphic)
    {
        UNUSED(selPos);
        UNUSED(graphic);
        return true;
    }
    //删除链接
    virtual bool delJoin(int selPos)
    {
        UNUSED(selPos);
        return  true;
    }
    //确保可见
    virtual void ensureVisible();
    //恢复
    virtual void restoreGraphic(QDataStream& dataStream)
    {
        UNUSED(dataStream);
        assert(false);
    }
    virtual void loadXML(rapidxml::xml_node<char> *node)
    {
        UNUSED(node);
    }
    //保存
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
    //设置位置
    virtual void setPosition(const QPointF& pos)
    {
        UNUSED(pos);
        //assert(false);
    }
    //获取位置
    virtual QPointF getPosition()const
    {
        assert(false);
    }
    //设置大小
    virtual const QSize& getSize() const
    {
        assert(false);
    }
    //更新
    virtual void updateShape()
    {
        this->update();
    }
    //获取父图
    virtual Graphic* parentGraphic()
    {
        return NULL;
    }
    //获取设备名称
    virtual const QString& getDevName() const
    {
        return _devName;
    }
    //获取链接点
    virtual QVector<GraphicPort>& getPorts()
    {
        return _port;
    }
    //移动图标
    void moveGraphic(const QPointF& point);
private:
    static const QString _devName;//设备名称
    QVector<GraphicPort> _port;//用于保存链接点
};

#endif // GROUPGRAPHICBASE_H
