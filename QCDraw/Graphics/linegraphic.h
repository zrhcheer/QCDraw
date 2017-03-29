#ifndef LINEGRAPITEM_H
#define LINEGRAPITEM_H

#include <QList>
#include <QPoint>
#include "graphicshape.h"
#include "graphicbase.h"
#include "stationgraphic.h"
#include "widthgraphiclineitem.h"
#include "nodelink.h"
#include "graphicknee.h"
#include "tickgraphic.h"
#include "lineflow.h"
#include <map>

using namespace std;

#define MIN_LEN 10
class StationGraphic;
struct SideStation
{
    StationGraphic* beginStation;
    StationGraphic* endStation;
};


struct LineMove
{
    LineMove(Graphic* graphic,const int& pos)
    {
        _graphic = graphic;
        _pos = pos;
    }

    bool operator<(const LineMove& lineMove) const
    {
        if(_graphic < lineMove._graphic)
        {
            return true;
        }
        else if(_graphic == lineMove._graphic)
        {
            if(_pos < lineMove._pos)
            {
                return true;
            }
        }

        return false;
    }

    Graphic* _graphic;
    int _pos;
};

class LineGraphic : public GraphicShape , public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit LineGraphic();

    //查找线路两边所连的厂站
    bool querySideStation(SideStation& sideStation);
    //QRectF boundingRect() const;
    //更新
    virtual void updateShape();
    //确保可见
    virtual void ensureVisible();
    //设置选择状态
    virtual void setSelect(const bool& select);
    //查询拐点
    GraphicKnee queryKneeNode(const QPointF& point);
    //移动拐点
    bool moveKnee(GraphicKnee& knee,const QPointF& point);
    //删除拐点
    bool delKnee(GraphicKnee& knee);
    //移动
    bool movePostion(const QPointF& pointMove,set<LineMove>& lineMove);
    //删除链接
    virtual bool delJoin(int selPos);
    virtual bool  delLink(int selPos,Graphic* graphic);
    //恢复
    virtual void restoreGraphic(QDataStream& dataStream);
    virtual void loadXML(rapidxml::xml_node<char> *node);
    //保存
    virtual void saveGraphic(QDataStream& dataStream) const;
    virtual void saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic);
    //初始化链接
    void initLink(map<ulong64,Graphic*>& allElement);
    //获取链接点及其类型
    virtual QVector<GraphicPortPoint>&  getJoinPortPoint();

    //显示锚
    virtual void showPortAnchor(int selPos);
    //隐藏锚
    virtual void hidePortAnchor(int selPos);
    virtual void hidePortAnchor();

    virtual set<int> queryUnMountPos();
    //是否链接
    virtual bool isJointed(int selPos);
    //获取大小
    virtual const QSize& getSize() const;
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
    //设置标签
    virtual void setCaption(const QString& caption);
    //获取链接点位置
    virtual QPointF  getPortPos(int pos);

    bool setStationGraphic(GraphicBase* beginStation,GraphicBase* endStation);
    //在linkPos处链接graphic
    bool linkGraphic(int selPos,Graphic* graphic,int linkPos);
    //以graphic开始或结束链接
    bool setGraphicLink(int posLink,GraphicBase* graphic,int pos)
    {
        switch(posLink)
        {
        case Graphic::JOIN_BEGIN:
            setBeginGraphic(graphic,pos);
            break;
        case Graphic::JOIN_END:
            setEndGraphic(graphic,pos);
            break;
        }
        return true;
    }

    //用于连接普通元件
    //以beginStation开始链接
    bool setBeginGraphic(GraphicBase* beginStation,int pos);
    //以endJoin结束链接
    bool setEndGraphic(GraphicBase* endJoin,int pos);

    //删除此线路连接
    void unlinkGraphic();

    //用于连接母线,认为此点在母线上
    bool setBusGraphicLink(int posLink,BusGraphic* graphic)
    {
        switch(posLink)
        {
        case Graphic::JOIN_BEGIN:
            setBeginBusGraphic(graphic);
            break;
        case Graphic::JOIN_END:
            setEndBusGraphic(graphic);
            break;
        }
        return true;
    }
    //是否从母线开始链接
    bool setBeginBusGraphic(BusGraphic* graphic);
    //是否以母线结束链接
    bool setEndBusGraphic(BusGraphic* graphic);

    //用于连接线路
    //把自已加入连接集和
    bool setLineGraphicLink(int posLink)
    {
        switch(posLink)
        {
        case Graphic::JOIN_BEGIN:
            _beginLink.setLineLinkSel(this,posLink);
            break;
        case Graphic::JOIN_END:
            _endLink.setLineLinkSel(this,posLink);
            break;
        }
        return true;
    }
    //连接其他元件
    bool setLineGraphicLink(int posLink,LineGraphic* graphic,int pos)
    {
        switch(posLink)
        {
        case Graphic::JOIN_BEGIN:
            setBeginLineGraphic(graphic,pos);
            break;
        case Graphic::JOIN_END:
            setEndLineGraphic(graphic,pos);
            break;
        }
        return true;
    }
    bool setBeginLineGraphic(LineGraphic* ,int pos);
    bool setEndLineGraphic(LineGraphic* ,int pos);

    //获取链接点
    bool getLinePoint(QVector<QPointF>& vecPoint)const;
    //设置链接点
    bool setLinePoint(const QVector<QPointF>& vecPoint);
    //获取链接开始点
    QPointF getBeginPoint();
    //设置链接开始点
    bool setBeginPoint(const QPointF& beginPoint);
    //获取链接结束点
    QPointF getEndPoint();
    //设置链接结束点
    bool setEndPoint(const QPointF& endPoint);

    QPointF getCenterPoint() const;

    bool setJointPointDis(int pos,const QPointF& joinMove,float dis,bool casc = true);
    //设置链接点
    bool setJointPoint(int pos,const QPointF& joinPoint);
    //移动开始点
    bool moveBeginPoint(const QPointF& beginPoint);
    //移动结束点
    bool moveEndPoint(const QPointF& endPoint);
    //移动链接点
    bool moveJointPoint(int pos,const QPointF& joinMove);
    //获取_beginLink/_endLink
    NodeLink& getNodeLink(int pos)
    {
        switch(pos)
        {
        case Graphic::JOIN_BEGIN:
            return _beginLink;
            break;
        case Graphic::JOIN_END:
            return _endLink;
            break;
        }
        throw exception();
    }
    //设置颜色
    virtual void setColor(const QColor& clr);
    //void setMagic(bool bMagic);
    //在pos出是否为虚线链接
    bool isMagicPos(int pos);
    //是否为虚线
    bool isMagic() const
    {
        return _lineType == Graphic::LINE_VIR;
    }
    //线路类型/画笔颜色和模式
    void setPattern(const QColor& clr);
    //线路链接断路器
    void setLineBreak(int pos,bool bBreaker = true);
    //设置标记颜色
    void setLineBreakColor(int pos,const QColor& clrCross);
    //设线路中间标记闪电
    void setLineMarkMid(bool bMark = true);
    //获取线路类型
    const int& getLineType() const
    {
        return _lineType;
    }
    //设置线路类型
    void setLineType(int lineType);
    //设置出线类型和出线厂站ID
    void setOut(int outType,const ulong64& idOutStation)
    {
        _outType = outType;
        _idOutStation = idOutStation;
    }
    //设置出线类型
    void setOutType(int outType);
    //获取出线类型
    int getOutType()
    {
        return _outType;
    }
    //设置是否显示出线
    void setIsShowOut(bool bShowOut);
    //获取出线厂站ID
    const ulong64& getOutStationId() const
    {
        return _idOutStation;
    }
    //获取链接点
    virtual QVector<GraphicPort>& getPorts();

    //移动相关
    void flushMove();
    LineFlow* addMove(const int& beginPer,const int& endPer,float step,const QColor& clr);
    bool delMove(LineFlow* flow);

signals:
    
public slots:
private:

    void flushTick();
    //设置中间标记位置
    void setMidTickPos(TickGraphic* tickMid);
    //设开始标记位置
    void setBeginTick();
    //设置结束标记位置
    void setEndTick();
    CaptionGraphic* _captionGraphic;//标签
    TickGraphic* _tickBegin;//开始标记
    TickGraphic* _tickEnd;//结束标记
    TickGraphic* _tickMid;//中间标记
    QList<WidthGraphicLineItem*> _listLine;

    //一般连接
    NodeLink _beginLink;//链接开始
    NodeLink _endLink;//链接结束

   //线路的移动
    QSet<LineFlow*> _flowList;
//    bool _bBeginPosMove;
//    bool _isMove;//是否移动
//    int _movePercent;//总长度百分比
//    float _moveLen;//现在位置
//    float _moveMax;//移动总长度
//    float _stepMove;//步长
//    QColor _moveClr;//顔色
//    WidthGraphicLineItem* _moveLine;

    //出线
    ulong64 _idOutStation;//出线厂站ID
    int _outType;//出线类型
    int _lineType;//线路类型
    bool _bShowOut;//是否显示出线

    //bool _bMagic;//是虚线还是实线
    //int _consumer;// 头是否加葥头,０没有，１始端，2末端
    static const QString _devName;//设备名称
    QVector<GraphicPort> _port;//用于保存链接点
    QSize _size;//大小
};

#endif // LINEGRAPITEM_H
