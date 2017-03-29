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

    //������·���������ĳ�վ
    bool querySideStation(SideStation& sideStation);
    //QRectF boundingRect() const;
    //����
    virtual void updateShape();
    //ȷ���ɼ�
    virtual void ensureVisible();
    //����ѡ��״̬
    virtual void setSelect(const bool& select);
    //��ѯ�յ�
    GraphicKnee queryKneeNode(const QPointF& point);
    //�ƶ��յ�
    bool moveKnee(GraphicKnee& knee,const QPointF& point);
    //ɾ���յ�
    bool delKnee(GraphicKnee& knee);
    //�ƶ�
    bool movePostion(const QPointF& pointMove,set<LineMove>& lineMove);
    //ɾ������
    virtual bool delJoin(int selPos);
    virtual bool  delLink(int selPos,Graphic* graphic);
    //�ָ�
    virtual void restoreGraphic(QDataStream& dataStream);
    virtual void loadXML(rapidxml::xml_node<char> *node);
    //����
    virtual void saveGraphic(QDataStream& dataStream) const;
    virtual void saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic);
    //��ʼ������
    void initLink(map<ulong64,Graphic*>& allElement);
    //��ȡ���ӵ㼰������
    virtual QVector<GraphicPortPoint>&  getJoinPortPoint();

    //��ʾê
    virtual void showPortAnchor(int selPos);
    //����ê
    virtual void hidePortAnchor(int selPos);
    virtual void hidePortAnchor();

    virtual set<int> queryUnMountPos();
    //�Ƿ�����
    virtual bool isJointed(int selPos);
    //��ȡ��С
    virtual const QSize& getSize() const;
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
    //���ñ�ǩ
    virtual void setCaption(const QString& caption);
    //��ȡ���ӵ�λ��
    virtual QPointF  getPortPos(int pos);

    bool setStationGraphic(GraphicBase* beginStation,GraphicBase* endStation);
    //��linkPos������graphic
    bool linkGraphic(int selPos,Graphic* graphic,int linkPos);
    //��graphic��ʼ���������
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

    //����������ͨԪ��
    //��beginStation��ʼ����
    bool setBeginGraphic(GraphicBase* beginStation,int pos);
    //��endJoin��������
    bool setEndGraphic(GraphicBase* endJoin,int pos);

    //ɾ������·����
    void unlinkGraphic();

    //��������ĸ��,��Ϊ�˵���ĸ����
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
    //�Ƿ��ĸ�߿�ʼ����
    bool setBeginBusGraphic(BusGraphic* graphic);
    //�Ƿ���ĸ�߽�������
    bool setEndBusGraphic(BusGraphic* graphic);

    //����������·
    //�����Ѽ������Ӽ���
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
    //��������Ԫ��
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

    //��ȡ���ӵ�
    bool getLinePoint(QVector<QPointF>& vecPoint)const;
    //�������ӵ�
    bool setLinePoint(const QVector<QPointF>& vecPoint);
    //��ȡ���ӿ�ʼ��
    QPointF getBeginPoint();
    //�������ӿ�ʼ��
    bool setBeginPoint(const QPointF& beginPoint);
    //��ȡ���ӽ�����
    QPointF getEndPoint();
    //�������ӽ�����
    bool setEndPoint(const QPointF& endPoint);

    QPointF getCenterPoint() const;

    bool setJointPointDis(int pos,const QPointF& joinMove,float dis,bool casc = true);
    //�������ӵ�
    bool setJointPoint(int pos,const QPointF& joinPoint);
    //�ƶ���ʼ��
    bool moveBeginPoint(const QPointF& beginPoint);
    //�ƶ�������
    bool moveEndPoint(const QPointF& endPoint);
    //�ƶ����ӵ�
    bool moveJointPoint(int pos,const QPointF& joinMove);
    //��ȡ_beginLink/_endLink
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
    //������ɫ
    virtual void setColor(const QColor& clr);
    //void setMagic(bool bMagic);
    //��pos���Ƿ�Ϊ��������
    bool isMagicPos(int pos);
    //�Ƿ�Ϊ����
    bool isMagic() const
    {
        return _lineType == Graphic::LINE_VIR;
    }
    //��·����/������ɫ��ģʽ
    void setPattern(const QColor& clr);
    //��·���Ӷ�·��
    void setLineBreak(int pos,bool bBreaker = true);
    //���ñ����ɫ
    void setLineBreakColor(int pos,const QColor& clrCross);
    //����·�м�������
    void setLineMarkMid(bool bMark = true);
    //��ȡ��·����
    const int& getLineType() const
    {
        return _lineType;
    }
    //������·����
    void setLineType(int lineType);
    //���ó������ͺͳ��߳�վID
    void setOut(int outType,const ulong64& idOutStation)
    {
        _outType = outType;
        _idOutStation = idOutStation;
    }
    //���ó�������
    void setOutType(int outType);
    //��ȡ��������
    int getOutType()
    {
        return _outType;
    }
    //�����Ƿ���ʾ����
    void setIsShowOut(bool bShowOut);
    //��ȡ���߳�վID
    const ulong64& getOutStationId() const
    {
        return _idOutStation;
    }
    //��ȡ���ӵ�
    virtual QVector<GraphicPort>& getPorts();

    //�ƶ����
    void flushMove();
    LineFlow* addMove(const int& beginPer,const int& endPer,float step,const QColor& clr);
    bool delMove(LineFlow* flow);

signals:
    
public slots:
private:

    void flushTick();
    //�����м���λ��
    void setMidTickPos(TickGraphic* tickMid);
    //�迪ʼ���λ��
    void setBeginTick();
    //���ý������λ��
    void setEndTick();
    CaptionGraphic* _captionGraphic;//��ǩ
    TickGraphic* _tickBegin;//��ʼ���
    TickGraphic* _tickEnd;//�������
    TickGraphic* _tickMid;//�м���
    QList<WidthGraphicLineItem*> _listLine;

    //һ������
    NodeLink _beginLink;//���ӿ�ʼ
    NodeLink _endLink;//���ӽ���

   //��·���ƶ�
    QSet<LineFlow*> _flowList;
//    bool _bBeginPosMove;
//    bool _isMove;//�Ƿ��ƶ�
//    int _movePercent;//�ܳ��Ȱٷֱ�
//    float _moveLen;//����λ��
//    float _moveMax;//�ƶ��ܳ���
//    float _stepMove;//����
//    QColor _moveClr;//�ɫ
//    WidthGraphicLineItem* _moveLine;

    //����
    ulong64 _idOutStation;//���߳�վID
    int _outType;//��������
    int _lineType;//��·����
    bool _bShowOut;//�Ƿ���ʾ����

    //bool _bMagic;//�����߻���ʵ��
    //int _consumer;// ͷ�Ƿ��ȓͷ,��û�У���ʼ�ˣ�2ĩ��
    static const QString _devName;//�豸����
    QVector<GraphicPort> _port;//���ڱ������ӵ�
    QSize _size;//��С
};

#endif // LINEGRAPITEM_H
