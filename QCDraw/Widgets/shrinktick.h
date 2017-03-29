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


    //恢复
    virtual void restoreGraphic(QDataStream& dataStream);
    virtual void loadXML(rapidxml::xml_node<char> *node);
    //保存
    virtual void saveGraphic(QDataStream& dataStream) const;
    virtual void saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic);

    //确认可见
    virtual void ensureVisible()
    {
    }

//    virtual void restoreGraphic(QDataStream& dataStream) = 0;
//    virtual void saveGraphic(QDataStream& dataStream) const=0;
    //获取链接点
    virtual QVector<GraphicPort>& getPorts()
    {
        return _vecPort;
    }
    //获取连接点位置
    virtual QPointF  getPortPos(int pos)
    {
        UNUSED(pos);
        return QPointF(0,0);
    }
    //删除链接
    virtual bool  delLink(int selPos,Graphic* graphic)
    {
        UNUSED(selPos);
        UNUSED(graphic);
        return false;
    }
    //删除链接
    virtual bool delJoin(int selPos)
    {
        UNUSED(selPos);
        return false;
    }

    //获取大小
    virtual const QSize& getSize() const
    {
        assert(false);
        return _minSize;
    }
    //设置位置
    virtual void setPosition(const QPointF& pos)
    {
        this->setPos(pos.toPoint());
    }
    //获取位置
    virtual QPointF getPosition() const
    {
        return QPointF(this->pos());
    }
    //更新
    virtual void updateShape()
    {
        this->update();
    }
    //判断给的点是否在窗体上
    virtual bool isPointOver(const QPointF& point) const;
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

protected:
    virtual void	mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event );
signals:
public slots:

private:
    ShrinkWidget* _tabWid;

    QSize _minSize;//用于保存最小大小
     QVector<GraphicPort> _vecPort;//用于保存链接点
     static const QString _devName;//设备名称

     bool _bTiny;
};

#endif // SHRINKTICK_H
