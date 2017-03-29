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
    //画图
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    //获取矩形大小
    virtual QRectF boundingRect() const;
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
        return true;
    }
    //确保可见
    virtual void ensureVisible()
    {
        QGraphicsItem::ensureVisible();
    }

    int fontWidth();//字体宽度
    int fonrHeight();//字体高度
    //获取链接点位置
    virtual QPointF  getPortPos(int pos)
    {
        UNUSED(pos);
        assert(false);
    }
    //恢复
    virtual void restoreGraphic(QDataStream& dataStream);
    virtual void loadXML(rapidxml::xml_node<char> *node);
    //保存
    virtual void saveGraphic(QDataStream& dataStream) const;
    virtual void saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic);
    //更新
    virtual void updateShape()
    {
        this->update();
    }
    //获取链接点
    virtual QVector<GraphicPort>& getPorts()
    {
        return _port;
    }
    //获取标签大小
    virtual const QSize& getSize() const
    {
        return _size;
    }
    //设置标签位置
    virtual void setPosition(const QPointF& pos)
    {
        this->setPos(pos);
    }
    //获取标签位置
    QPointF getPosition() const
    {
        return this->pos();
    }
    //获取父图
    virtual Graphic* parentGraphic()
    {
        return dynamic_cast<Graphic*>(this->parentItem());
    }
    //设置标签文本
    void setText(const QString& strText);
    //获取标签文本
    const QString& getText() const
    {
        return _text;
    }
    //获取设备名称
    virtual const QString& getDevName() const
    {
        return _devName;
    }
protected:
    //画图
    virtual void prepareGraphic(QPainter *painter);
    virtual void drawGraphic(QPainter *painter);
private:
    //QString _caption;
    QSize _size;//标签大小
    QFont _font;//标签字体
    QString _text;//标签文本
    static const QString _devName;//设备名称
    QVector<GraphicPort> _port;//用于保存链接点
};

#endif // CAPTIONGRAPHIC_H
