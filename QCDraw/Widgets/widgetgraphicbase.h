#ifndef WIDGETGRAPHICBASE_H
#define WIDGETGRAPHICBASE_H

#include "Graphics/graphic.h"
#include <QWidget>
#include <QHBoxLayout>

class WidgetGraphicBase : public QWidget,public Graphic
{
public:
    WidgetGraphicBase(QWidget* parent = 0);
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
        this->move(pos.toPoint());
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
    virtual const QString& getDevName() const = 0;
    //得到放大缩小的方向
    virtual int getSizeChangeFlag(const QPointF& point);
//    //设置光标
//    virtual bool setCursorForSize(int sizeFlag);
//    //设置光标
//    virtual bool setCursorForID(int id);
    //从某一方向改变大小
    virtual void changeSizeFromSide(const QPointF& curPoint,const int& sizeFlag);

    //设置当前控件
    void setCurWidget(QWidget* curWidget);
protected:
    virtual void	paintEvent ( QPaintEvent * event );
    bool _bHorChange;
    bool _bVerChange;
    QSize _minSize;//用于保存最小大小
    QWidget* _curWidget;//用于保存当前控件
    QHBoxLayout* _topLayout;//用于设置水平布局

    QVector<GraphicPort> _vecPort;//用于保存链接点
};

#endif // WIDGETGRAPHICBASE_H
