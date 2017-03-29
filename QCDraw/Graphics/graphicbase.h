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
    //画图
    virtual void drawGraphic(QPainter *painter) = 0;
    virtual void prepareGraphic(QPainter *painter);
    //画被选择的元件
    virtual void drawSelect(QPainter *painter);
    virtual void drawLock(QPainter *painter);
    //void drawPort(QPainter *painter);
    //确保可见
    virtual void ensureVisible()
    {
        QGraphicsItem::ensureVisible();
    }
    //设置颜色
    virtual void setColor(const QColor& color)
    {
        if(_color != color)
        {
            _color = color;
            this->update();
        }
    }
    //显示锚
    virtual void showPortAnchor(int selPos);
    //隐藏锚
    virtual void hidePortAnchor(int selPos);
    virtual void hidePortAnchor();
    //是否链接
    virtual bool isJointed(int selPos);
    //删除链接
    virtual bool delLink(int selPos,Graphic* graphic);
    virtual bool delJoin(int selPos);

    void unlinkGraphic(); //删除厂站连接
    //画图
    virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    //获取矩形大小
    virtual QRectF boundingRect() const;
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
    //恢复
    virtual void restoreGraphic(QDataStream& dataStream);
    virtual void loadXML(rapidxml::xml_node<char>*node);
    //保存
    virtual void saveGraphic(QDataStream& dataStream) const;
    virtual void saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic);

    //获取不是端点的链接点位置个数
    virtual set<int> queryUnMountPos();
    //一端为母线，别的端为线路或不连可绕母线移动
    bool moveAroundBus(const QPointF& point);
    //设置位置
    virtual void setPosition(const QPointF& pos);
    //获取位置
    QPointF getPosition() const
    {
        return this->pos();
    }
    //得到放大缩小的方向
    virtual int getSizeChangeFlag(const QPointF& point);
    //判断给的点是否在窗体上
    virtual bool isPointOver(const QPointF& point) const;
    //获取大小
    virtual const QSize& getSize() const
    {
        return _size;
    }
    //现设宽变是长变的四分之一
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
    //设置比例大小
    virtual void setScale(const float& scale)
    {
        setSize(BASIC_SQARE * 2 * scale);
    }

    //获取设备名称
    virtual const QString& getDevName()const = 0;
    //设置标签
    virtual  void setCaption(const QString& caption);
    void setCaption(const QString& caption,const QPointF& pos);
    //设置标签位置
    void setCaptionPos(const QPointF& pos)
    {
        if(_captionGraphic)
        {
            _captionGraphic->setPos(pos);
        }
    }
    //设置线路
    virtual void setLine(LineGraphic* lineGraphic,int pos)
    {
        UNUSED(lineGraphic);
        UNUSED(pos);
    }


    //这三个函数需处理反回值
    //元件和元件相联
    virtual GroupDeal setPortBasic(int direct,GraphicBase* basicGraphic,int directOther);
    //busPos 从母线开始到结束为0-1
    virtual GroupDeal setPortBus(int direct,BusGraphic* busGraphic,const double& busPos);
    virtual GroupDeal setPortBus(int direct,BusGraphic* busGraphic);
    virtual void setPortGraphic(int pos,Graphic* joint,int posLink);
//    virtual QPointF  getPortPos(int pos)
//    {
//        return this->pos();
//    }
    //加载链接点位置
    virtual void loadPortPos(){}
    //初始化链接
    GroupDeal initLink(map<ulong64,Graphic*>& allElement);
    //获取链接点
    virtual QVector<GraphicPort>& getPorts()
    {
        return _port;
    }
    //设置标记
    void setTick(bool bTick,int flag=TickGraphic::TICK_CROSS);
    //设置标记颜色
    void setTickColor(const QColor& clr);

protected:
    //元件链接到basicGraphic
    virtual void setJointGraphic(int direct,GraphicBase* basicGraphic,int directOther);
    //元件连到firstItem則放到一个組中
    GroupDeal groupGraphicItem(BusGraphic* firstItem);
    GroupDeal groupGraphicItem(GraphicBase* firstItem);
    QVector<GraphicPort> _port;//用于保存链接点
    CaptionGraphic* _captionGraphic;//标签
    QSize _size;//大小
    TickGraphic* _tickGraphic;//标记
    int _ref;
};

#endif // GRAPHICBASE_H
