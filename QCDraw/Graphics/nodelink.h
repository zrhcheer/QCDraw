#ifndef NODELINK_H
#define NODELINK_H

#include "graphicport.h"
#include "graphicbase.h"
#include <boost/shared_ptr.hpp>
class LineGraphic;
class NodeLineLink
{
public:
    //���ӵ���·�����ӵĶ�
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
    //�ָ�
    void restoreGraphic(QDataStream& dataStream);
    void loadXML(rapidxml::xml_node<char>* node);
    //����
    void saveGraphic(QDataStream& dataStream) const;
    void saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic);

    //������������
    //int _flagConnect;
    //boost::shared_ptr<NodeLineLink> _lineLink;
    //bool combineLink(LineGraphic* lineGraphic,int pos);
    //�Ƿ�Ϊ����
    bool isMagicPos();
    //�������ӵ����ӵ���·�����ӵĶ�
    bool setLineLinkSel(Graphic* graphic,int posLink);
    //������·����
    bool setLineLink(Graphic* lineGraphic,int posLink);
    //��ȡ��վ
    Graphic* getLinkCenter();
    //��ȡ���ӵ�
    NodeLineLink* getNodeLink()
    {
        return _port.get();
    }
    //��ȡ�ڵ�
    boost::shared_ptr<NodeLineLink>& getPort()
    {
        return _port;
    }
    //���ýڵ�
    void setPort(boost::shared_ptr<NodeLineLink>& port)
    {
        _port = port;
    }
    //�������
    void clearLink()
    {
        _port.reset();
    }
private:
    //��������
    bool addLink(Graphic* graphic,int posLink);
    boost::shared_ptr<NodeLineLink> _port;//��·���ӽڵ�

    bool _bOutLine;//�Ƿ����
    //����������Ԫ������
    //GraphicBase* _joinGraphic;
    //int posBegin;
    //������ĸ������
    //BusGraphic* _joinBus;
};

#endif // NODELINK_H
