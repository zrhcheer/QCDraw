#ifndef TICKGRAPHIC_H
#define TICKGRAPHIC_H
#include "graphic.h"
class TickGraphic : public Graphic,public QGraphicsItem
{
public:
    enum
    {
        TICK_CROSS,//打叉
        TICK_EXCLA,//感叹号
        TICK_LIGHT//闪电
    };
    TickGraphic(QGraphicsItem* parent = 0,int flag = TICK_CROSS);
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    //获取矩形大小
    virtual QRectF boundingRect() const;
    //设置标记位置
    void setTickPos(const QLineF& line,bool bBegin);
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
    //获取大小
    virtual const QSize& getSize() const
    {
        return _size;
    }
    //设置位置
    virtual void setPosition(const QPointF& pos)
    {
        this->setPos(pos);
    }
    //获取位置
    QPointF getPosition() const
    {
        return this->pos();
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
    //设置符号类型
    void setFlag(const int& flag)
    {
        if(flag != _flag)
        {
            _flag = flag;
            update();
        }
    }

protected:
    //设置画笔
    virtual void prepareGraphic(QPainter *painter);
    //画图
    virtual void drawGraphic(QPainter *painter);
private:
    QSize _size;//大小
    static const QString _devName;//设备名称
    QVector<GraphicPort> _port;//用于保存链接点
    int _flag;//符号类型
};

#endif // TICKGRAPHIC_H
