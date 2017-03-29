#ifndef NODELINK_H
#define NODELINK_H

#include "graphicport.h"
#include "graphicbase.h"
#include <boost/shared_ptr.hpp>
class LineGraphic;
class NodeLineLink
{
public:
    //连接的线路和连接的端
    QList<GraphicPort> _link;
};

class NodeLink
{
public:
    enum
    {
        LINK_NORMAL,
        LINK_LINE,
        LINK_BUS,
        LINK_UN
    };
    NodeLink()
    {
        _bOutLine = false;
    }
    //恢复
    void restoreGraphic(QDataStream& dataStream);
    void loadXML(rapidxml::xml_node<char>* node);
    //保存
    void saveGraphic(QDataStream& dataStream) const;
    void saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic);

    //用于与线相连
    //int _flagConnect;
    //boost::shared_ptr<NodeLineLink> _lineLink;
    //bool combineLink(LineGraphic* lineGraphic,int pos);
    //是否为虚线
    bool isMagicPos();
    //设置链接点连接的线路和连接的端
    bool setLineLinkSel(Graphic* graphic,int posLink);
    //设置线路链接
    bool setLineLink(Graphic* lineGraphic,int posLink);
    //获取厂站
    Graphic* getLinkCenter();
    //获取链接点
    NodeLineLink* getNodeLink()
    {
        return _port.get();
    }
    //获取节点
    boost::shared_ptr<NodeLineLink>& getPort()
    {
        return _port;
    }
    //设置节点
    void setPort(boost::shared_ptr<NodeLineLink>& port)
    {
        _port = port;
    }
    //清空链接
    void clearLink()
    {
        _port.reset();
    }
private:
    //增加链接
    bool addLink(Graphic* graphic,int posLink);
    boost::shared_ptr<NodeLineLink> _port;//线路链接节点

    bool _bOutLine;//是否出线
    //用于与正常元件相连
    //GraphicBase* _joinGraphic;
    //int posBegin;
    //用于与母线相连
    //BusGraphic* _joinBus;
};

#endif // NODELINK_H
