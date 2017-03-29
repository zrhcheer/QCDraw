#include "nodelink.h"
#include "linegraphic.h"
#include <QDebug>
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "rapidxml/rapidxml_utils.hpp"

bool NodeLink::addLink(Graphic* graphic,int posLink)
{
    bool bFind = false;
    for(QList<GraphicPort>::iterator iterPort =   _port->_link.begin();
        iterPort != _port->_link.end(); ++iterPort)
    {
        GraphicPort& port = *iterPort;
        if(port.getGraphic() == graphic)
        {
            port.setLinkPos(posLink);
            bFind = true;
            break;
        }
    }
    if(!bFind)
    {
        GraphicPort  tmpPort;
        tmpPort.setSelPos(0);
        tmpPort.setLinkPos(posLink);
        tmpPort.setGraphic(graphic);
        _port->_link.push_back(tmpPort);
    }
    return true;
}

bool NodeLink::setLineLinkSel(Graphic* graphic,int posLink)
{
    if(!_port.get())
    {
        _port = boost::shared_ptr<NodeLineLink>(new NodeLineLink());
        GraphicPort  tmpPort;
        tmpPort.setSelPos(0);
        tmpPort.setLinkPos(posLink);
        tmpPort.setGraphic(graphic);
        _port->_link.push_back(tmpPort);
    }
    return true;
}

bool NodeLink::setLineLink(Graphic* graphic,int posLink)
{
    if(!_port.get())
    {
        _port = boost::shared_ptr<NodeLineLink>(new NodeLineLink());
    }
    if(Graphic::GRAPHIC_LINE == graphic->getType())
    {
        LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>(graphic);
        QPointF posPoint = lineGraphic->getPortPos(posLink);
        //合并连接点
        NodeLink& link = lineGraphic->getNodeLink(posLink);
        if(link._port.get())
        {
            for(QList<GraphicPort>::Iterator iterPort =   link._port->_link.begin();
                iterPort != link._port->_link.end(); ++iterPort)
            {
                GraphicPort& port = *iterPort;
                this->addLink(port.getGraphic(),port.getLinkPos());
            }
        }
        else
        {
            this->addLink(graphic,posLink);
        }
        link._port = this->_port;
        //合到一点
        for(QList<GraphicPort>::Iterator iterPort =   this->_port->_link.begin();
            iterPort != this->_port->_link.end(); ++iterPort)
        {
            GraphicPort& port = *iterPort;
            Graphic* graphic = port.getGraphic();
            if(graphic && Graphic::GRAPHIC_LINE)
            {
                LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>(graphic);
                lineGraphic->setJointPoint(port.getLinkPos(),posPoint);
            }
        }
    }
    else
    {
        addLink(graphic,posLink);
    }
    return true;
}

void NodeLink::loadXML(rapidxml::xml_node<char> *node)
{
    if(!_port.get())
    {
        _port = boost::shared_ptr<NodeLineLink>(new NodeLineLink());
    }
    _port->_link.clear();
    string ports;
    for(rapidxml::xml_attribute<char>* attr = node->first_attribute();attr;
        attr = attr->next_attribute())
    {
        if(0 == strcmp("ports",attr->name()))
        {
            ports = attr->value();
        }
    }
    GraphicPort graphicPort;
    for(int i = 0;i < ports.size();++i)
    {
        size_t pos = ports.find(",",i);
        string selPos = ports.substr(i,pos - i);
        size_t pos1 = ports.find(",",pos + 1);
        string linkPos = ports.substr(pos + 1,pos1 - pos - 1);
        size_t pos2 = ports.find(";",pos1 + 1);
        string id = ports.substr(pos1 + 1,pos2 - pos1 - 1);
        graphicPort.setID(atoll(id.c_str()));
        graphicPort.setSelPos(atoi(selPos.c_str()));
        graphicPort.setLinkPos(atoi(linkPos.c_str()));
        _port->_link.push_back(graphicPort);
        i = pos2;
    }
}

void NodeLink::restoreGraphic(QDataStream& dataStream)
{
    if(!_port.get())
    {
        _port = boost::shared_ptr<NodeLineLink>(new NodeLineLink());
    }
    _port->_link.clear();
    dataStream >> _port->_link;
}

void NodeLink::saveXML(rapidxml::xml_node<char> *node, rapidxml::xml_document<> &doc,Graphic* graphic)
{
    if(_port.get())
    {
        QString graPort;
        QVector<GraphicPort> port = graphic->getPorts();
        for(int i = 0;i < port.size();++i)
        {
            GraphicPort graphicPort = port[i];
            graPort += QString::number(graphicPort.getSelPos()) + "," +
                    QString::number(graphicPort.getLinkPos()) + "," +
                    QString::number(graphicPort.getID()) + ";";
        }
        char* ports = doc.allocate_string(graPort.toStdString().c_str());
        node->append_attribute(doc.allocate_attribute("ports",ports));
    }
    else
    {
        QList<GraphicPort> port;
        QString graPort;
        for(int i = 0;i < port.size();++i)
        {
            GraphicPort graphicPort = port[i];
            graPort += QString::number(graphicPort.getSelPos()) + "," +
                    QString::number(graphicPort.getLinkPos()) + "," +
                    QString::number(graphicPort.getID()) + ";";
        }
        char* ports = doc.allocate_string(graPort.toStdString().c_str());
        node->append_attribute(doc.allocate_attribute("ports",ports));
    }
}

void NodeLink::saveGraphic(QDataStream& dataStream) const
{
    if(_port.get())
    {
        dataStream << _port->_link;
    }
    else
    {
        QList<GraphicPort> _link;
        dataStream << _link;
    }
}
Graphic* NodeLink::getLinkCenter()
{
    if(_port.get())
    {
        for(QList<GraphicPort>::Iterator iterPort =   _port->_link.begin();
            iterPort != _port->_link.end(); ++iterPort)
        {
            GraphicPort& port = *iterPort;
            Graphic* graphic = port.getGraphic();
            if(graphic && Graphic::GRAPHIC_STATION == graphic->getType())
            {
                return port.getGraphic();
            }
        }
    }
    return NULL;
}

bool NodeLink::isMagicPos()
{
    if(!_port.get())
    {
        return true;
    }
    for(QList<GraphicPort>::Iterator iterPort =   _port->_link.begin();
        iterPort != _port->_link.end(); ++iterPort)
    {
        GraphicPort& port = *iterPort;
        Graphic* graphic = port.getGraphic();
        if(graphic)
        {
            if(Graphic::GRAPHIC_LINE== graphic->getType())
            {
                LineGraphic* line = dynamic_cast<LineGraphic*>(graphic);
                if(!line->isMagic())
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

/*bool NodeLink::combineLink(LineGraphic* lineGraphic,int pos)
{
    NodeLink& outLink = lineGraphic->getNodeLink(pos);
    outLink.setLineLink(lineGraphic,pos);
    QPointF joinPoint = lineGraphic->getPortPos(pos);
    map<LineGraphic*,int>::iterator iterLink = _lineLink->_link.begin();
    for(;iterLink != _lineLink->_link.end(); ++iterLink)
    {
        LineGraphic* tmpLine = iterLink->first;
        if(!tmpLine->getMagic())
        {
            joinPoint = tmpLine->getPortPos(iterLink->second);
            break;
        }

    }

    //判断是否能连接
    if(_lineLink.get())
    {
        map<LineGraphic*,int>::iterator iterLink = _lineLink->_link.find(lineGraphic);
        if(iterLink != _lineLink->_link.end())
        {
            if(iterLink->second != pos)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
    //设置连接位置
    iterLink = _lineLink->_link.begin();
    for(;iterLink != _lineLink->_link.end(); ++iterLink)
    {
        LineGraphic* tmpLine = iterLink->first;
        int pos = iterLink->second;
        tmpLine->setJointPoint(pos,joinPoint);
    }

    if(_lineLink.get() != outLink._lineLink.get())
    {
        _lineLink->_link.insert(outLink._lineLink->_link.begin(),
                                outLink._lineLink->_link.end());
        outLink._lineLink = _lineLink;
    }
    //outLink._lineLink->_link.insert(make_pair(lineGraphic,pos));
    return true;
}*/
