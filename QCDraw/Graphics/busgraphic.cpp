#include "busgraphic.h"
#include <QPainter>
#include "linegraphic.h"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "rapidxml/rapidxml_utils.hpp"

#include "groupgraphicbase.h"
#include "Widgets/shrinktick.h"

const QString BusGraphic::_devName = CodeConvertor::fromLocal("母线");

BusGraphic::BusGraphic()
{
    _captionGraphic = NULL;
    setType(Graphic::GRAPHIC_BUS);
    setDirect(Graphic::POS_RIGHT);
    _busWidth = 4;
    this->setZValue(0.6);
    this->setPen(QPen(QBrush(QColor(0,127,0)),_busWidth));
    _color.setRgb(0,127,0);
    _portPoints.resize(1);
    _portPoints[0].setJoinType(GraphicPortPoint::JOIN_ALL);
    //_busPos = GraphicBase::POS_DOWN;
}
BusGraphic::BusGraphic(const QPointF& begin,const QPointF& end) :
    QGraphicsLineItem(begin.x(),begin.y(),end.x(),end.y())
{
    _captionGraphic = NULL;
    setType(Graphic::GRAPHIC_BUS);
    setDirect(Graphic::POS_RIGHT);
    _busWidth = 4;
    this->setPen(QPen(QBrush(QColor(0,127,0)),_busWidth));
     _color.setRgb(0,127,0);
    if(fabs(begin.x() - end.x()) < 1)
    {
        setDirect(Graphic::POS_UP);
    }
    else
    {
        setDirect(Graphic::POS_RIGHT);
    }
//    _ptBegin = begin;
//    _ptEnd = end;
}

void BusGraphic::setColor(const QColor& color)
{
    _color = color;
    this->setPen(QPen(QBrush(_color),_busWidth));
    this->update();
}

bool BusGraphic::delLink(int selPos,Graphic* graphic)
{
    for(QVector<GraphicPort>::Iterator iterPort = _port.begin();
        iterPort != _port.end(); )
    {
        GraphicPort& port = *iterPort;
        if(selPos == port.getSelPos() && graphic == port.getGraphic())
        {
            iterPort = _port.erase(iterPort);
        }
        else
        {
            iterPort++;
        }
    }
    return true;
}

bool BusGraphic::delJoin(int selPos)
{
    UNUSED(selPos);
    for(QVector<GraphicPort>::Iterator iterPort = _port.begin();
        iterPort != _port.end(); )
    {
        GraphicPort& port = *iterPort;

        Graphic* graphic = port.getGraphic();
        graphic->delLink(port.getLinkPos(),this);
    }
    _port.clear();
    return true;
}

void BusGraphic::loadXML(rapidxml::xml_node<char> *node)
{
    string color,lineBus,ports;
    for(rapidxml::xml_attribute<char>* attr = node->first_attribute();attr; attr = attr->next_attribute())
    {
        if(0 == strcmp("id",attr->name()))
        {
            _id = atoll(attr->value());
        }
        else  if(0 == strcmp("name",attr->name()))
        {
            _name = attr->value();
        }
        else  if(0 == strcmp("direct",attr->name()))
        {
            _direct = atoi(attr->value());
        }
        else  if(0 == strcmp("volLevelId",attr->name()))
        {
            _volLevelId = atoll(attr->value());
        }
        else  if(0 == strcmp("color",attr->name()))
        {
            color = attr->value();
            size_t pos = color.find(",",0);
            string color_r = color.substr(0,pos);
            size_t pos1 = color.find(",",pos + 1);
            string color_g = color.substr(pos + 1,pos1 - pos - 1);
            size_t pos2 = color.find(";",pos1 + 1);
            string color_b = color.substr(pos1 + 1,pos2 - pos1 - 1);
            _color.setRgb(atoi(color_r.c_str()),atoi(color_g.c_str()),atoi(color_b.c_str()));
            this->setColor(_color);
        }
        else  if(0 == strcmp("lineBus",attr->name()))
        {
            lineBus = attr->value();
            size_t pos = lineBus.find(",",0);
            string lineBus_x1 = lineBus.substr(0,pos);
            size_t pos1 = lineBus.find(",",pos + 1);
            string lineBus_y1 = lineBus.substr(pos + 1,pos1 - pos - 1);
            size_t pos2 = lineBus.find(",",pos1 + 1);
            string lineBus_x2 = lineBus.substr(pos1 + 1,pos2 - pos1 - 1);
            size_t pos3 = lineBus.find(";",pos2 + 1);
            string lineBus_y2 = lineBus.substr(pos2 + 1,pos3 - pos2 - 1);
            QLineF lineBus;
            lineBus.setLine(atof(lineBus_x1.c_str()),atof(lineBus_y1.c_str()),atof(lineBus_x2.c_str()),atof(lineBus_y2.c_str()));
            this->setLine(lineBus);
        }
        else  if(0 == strcmp("width",attr->name()))
        {
            _busWidth = atoi(attr->value());
        }
        else  if(0 == strcmp("num",attr->name()))
        {
            int num = atoi(attr->value());
            if(num > 0)
            {
                if(!_captionGraphic)
                {
                    _captionGraphic = new CaptionGraphic(this);
                }
                _captionGraphic->loadXML(node);
            }
        }
        else if(0 == strcmp("ports",attr->name()))
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
        _port.push_back(graphicPort);
        i = pos2;
    }
}

void BusGraphic::saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic)
{
    int color_r,color_g,color_b;
    _color.getRgb(&color_r,&color_g,&color_b);

    char* type = doc.allocate_string(QString::number(_type).toStdString().c_str());  //配置属性
    node->append_attribute(doc.allocate_attribute("type",type));

    char* id = doc.allocate_string(QString::number(_id).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("id",id));

    char* name = doc.allocate_string(_name.toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("name",name));

    char* direct = doc.allocate_string(QString::number(_direct).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("direct",direct));

    char* volLevelId = doc.allocate_string(QString::number(_volLevelId).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("volLevelId",volLevelId));

    string colorStr;
    colorStr += QString::number(color_r).toStdString() + ","
            + QString::number(color_g).toStdString() + ","
            + QString::number(color_b).toStdString() + ";";
    node->append_attribute(doc.allocate_attribute("color",doc.allocate_string(colorStr.c_str())));

    string lineBus;
    lineBus += QString::number(this->line().x1()).toStdString() + ","
            + QString::number(this->line().y1()).toStdString() + ","
            + QString::number(this->line().x2()).toStdString() + ","
            + QString::number(this->line().y2()).toStdString() + ";";
    node->append_attribute(doc.allocate_attribute("lineBus",doc.allocate_string(lineBus.c_str())));

    char* busWidth= doc.allocate_string(QString::number(_busWidth).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("width",busWidth));

    if(_captionGraphic)
    {
        node->append_attribute(doc.allocate_attribute("num","1"));
        _captionGraphic->saveXML(node,doc,graphic);
    }
    else
    {
        node->append_attribute(doc.allocate_attribute("num","0"));
    }

    QString graPort;
    QVector<GraphicPort> port = graphic->getPorts();
    for(int i = 0;i < port.size();++i)
    {
        GraphicPort graphicPort = port[i];
        graPort += QString::number(graphicPort.getSelPos()) + "," +
                                  QString::number(graphicPort.getLinkPos()) + "," +
                                             QString::number(graphicPort.getID()) + ";";
    }
    node->append_attribute(doc.allocate_attribute("ports",doc.allocate_string(graPort.toStdString().c_str())));
}

void BusGraphic::restoreGraphic(QDataStream& dataStream)
{
    dataStream >> _id;
    dataStream >> _name;
    dataStream >> _direct;
    dataStream >>_volLevelId;
    dataStream >> _color;
    this->setColor(_color);
    QLineF lineBus;
    dataStream >> lineBus;
    this->setLine(lineBus);
    dataStream >> _busWidth;

    //标签
    int num;
    dataStream >> num;//现誰为只有一个标签
    if(num > 0)
    {
        if(!_captionGraphic)
        {
            _captionGraphic = new CaptionGraphic(this);
        }
        _captionGraphic->restoreGraphic(dataStream);
    }
    //接点
    dataStream >> _port;
}

void BusGraphic::saveGraphic(QDataStream& dataStream) const
{
    dataStream << _type;
    dataStream << _id;
    dataStream << _name;
    dataStream << _direct;
    dataStream << _volLevelId;
    dataStream << _color;
    dataStream << this->line();
    dataStream << _busWidth;

    //标签
    if(_captionGraphic)
    {
        dataStream << (int)1;//现誰为只有一个标签
        _captionGraphic->saveGraphic(dataStream);
    }
    else
    {
        dataStream << (int)0;//现誰为只有一个标签
    }
    //接点
    dataStream << _port;
}

const QSize& BusGraphic::getSize() const
{
    return _size;
}

void BusGraphic::setPosition(const QPointF& pos)
{
    QPointF movePoint = pos - this->pos();
    QLineF lineBus = this->line();
    lineBus.setP1(lineBus.p1() + movePoint);
    lineBus.setP2(lineBus.p2() + movePoint);
    if(_captionGraphic)
    {
        _captionGraphic->setPos(_captionGraphic->pos() + movePoint);
    }
    if(_shrink)
    {
        _shrink->setPos(_shrink->pos() + movePoint);
    }
    this->setLine(lineBus);
    //this->setPos(pos);
    //对线进行移动
    for(QVector<GraphicPort>::Iterator iterGraphic = _port.begin();
        iterGraphic != _port.end(); ++iterGraphic)
    {
        GraphicPort& port = *iterGraphic;
        Graphic* tmpGraphic = port.getGraphic();
        int direct = port.getLinkPos();
        if(tmpGraphic->isLine())
        {
            LineGraphic* lineGraphic = (LineGraphic*)tmpGraphic;
            lineGraphic->moveJointPoint(direct,movePoint);
        }
    }
}

int BusGraphic::queryKneeNode(const QPointF& point)
{
    QLineF line = this->line();
    QPointF tmpPoint = line.p1();
    QRectF tmpRect;
    tmpRect.setLeft(tmpPoint.x() - PORTSIZE);
    tmpRect.setTop(tmpPoint.y() - PORTSIZE);
    tmpRect.setWidth(PORTSIZE * 2);
    tmpRect.setHeight(PORTSIZE * 2);
    if(tmpRect.contains(point))
    {
        return 0;
    }
    tmpPoint = line.p2();
    tmpRect.setLeft(tmpPoint.x() - PORTSIZE);
    tmpRect.setTop(tmpPoint.y() - PORTSIZE);
    tmpRect.setWidth(PORTSIZE * 2);
    tmpRect.setHeight(PORTSIZE * 2);
    if(tmpRect.contains(point))
    {
        return 1;
    }
    return -1;
}

void BusGraphic::setKneePos(int kneeIndex,const QPointF& point)
{
    switch(kneeIndex)
    {
    case 0:
    {
        QLineF line = this->line();

        switch(this->getDirect())
        {
        case Graphic::POS_UP:
        {
            QPointF begin = line.p1();
            begin.setY(point.y());
            line.setP1(begin);
            this->setLine(line);
        }
            break;
        case Graphic::POS_RIGHT:
        {
            QPointF begin = line.p1();
            begin.setX(point.x());
            line.setP1(begin);
            this->setLine(line);
        }
            break;
        }
    }
        break;
    case 1:
    {
        QLineF line = this->line();

        switch(this->getDirect())
        {
        case Graphic::POS_UP:
        {
            QPointF begin = line.p2();
            begin.setY(point.y());
            line.setP2(begin);
            this->setLine(line);
        }
            break;
        case Graphic::POS_RIGHT:
        {
            QPointF begin = line.p2();
            begin.setX(point.x());
            line.setP2(begin);
            this->setLine(line);
        }
            break;
        }
    }
        break;
    }
    this->update();
}

void BusGraphic::setCaption(const QString& caption)
{
    if(caption.isEmpty())//如果标题为空则删去
    {
        if(!_captionGraphic)
        {
            delete _captionGraphic;
            _captionGraphic = NULL;
        }
        return;
    }
    if(!_captionGraphic)
    {
        _captionGraphic = new CaptionGraphic(caption,this);
        _captionGraphic->setDirect(this->getDirect());
        float lenFont = _captionGraphic->fontWidth();
        QLineF line = this->line();
        switch (this->getDirect())
        {
        case POS_UP:
        case POS_DOWN:
            _captionGraphic->setPos(line.p1().x() , line.p1().y() - lenFont / 2 - 1);
            break;
        case POS_LEFT:
        case POS_RIGHT:
            _captionGraphic->setPos(line.p1().x() - lenFont / 2 - 1, line.p1().y());
            break;
        }
    }
    else
    {
        _captionGraphic->setText(caption);
    }
}

GroupDeal BusGraphic::initLink(map<ulong64,Graphic*>& allElement)
{
    GroupDeal groupDeal;
    GroupGraphicBase* groupGraphic = NULL;
    for(QVector<GraphicPort>::Iterator iterPort = _port.begin();
        iterPort != _port.end(); ++iterPort)
    {
        GraphicPort& tmpPort = *iterPort;
        map<ulong64,Graphic*>::iterator iterGraphic = allElement.find(tmpPort.getID());
        if(iterGraphic != allElement.end())
        {
            Graphic* tmpGraphic = iterGraphic->second;
            tmpPort.setGraphic(tmpGraphic);
            if(!tmpGraphic->isLine())
            {
                QGraphicsItem* graphicItem = dynamic_cast<QGraphicsItem*>(tmpGraphic);
                QGraphicsItem* tmpParent = graphicItem->parentItem();
                if(!tmpParent)
                {
                    if(!groupGraphic)
                    {
                        groupGraphic = new GroupGraphicBase();
                        groupDeal.addDeal(GroupDeal::GROUPD_ADD,groupGraphic);
                    }
                    groupGraphic->addToGroup(graphicItem);
                }
                else
                {
                    GroupGraphicBase* parent = dynamic_cast<GroupGraphicBase*>(tmpParent);
                    if(!groupGraphic)
                    {
                        groupGraphic = parent;
                    }
                    else
                    {
                        if(parent != groupGraphic)
                        {
                            //这个組的元件放入现在組中
                            QList<QGraphicsItem *> curGroup = parent->childItems();
                            for(QList<QGraphicsItem *>::Iterator iterCurGroup = curGroup.begin();
                                iterCurGroup != curGroup.end(); ++iterCurGroup)
                            {
                                QGraphicsItem* curItem = *iterCurGroup;
                                parent->removeFromGroup(curItem);
                                groupGraphic->addToGroup(curItem);
                            }
                            //parent->removeFromGroup(graphicItem);
                            groupDeal.addDeal(GroupDeal::GROUPD_DEL,parent);
                           // groupGraphic->addToGroup(graphicItem);
                        }
                    }
                }
            }
        }
    }
    if(groupGraphic)
    {
        groupGraphic->addToGroup(this);
    }
    return groupDeal;
}

void BusGraphic::setJoinGraphic(Graphic* joinGraphic,int pos)
{
    bool bFind = false;
    for(QVector<GraphicPort>::iterator iterPort = _port.begin();
        iterPort != _port.end(); ++iterPort)
    {
        GraphicPort& tmpPort = *iterPort;
        if(tmpPort.getGraphic() == joinGraphic)
        {
            tmpPort.setLinkPos(pos);
            tmpPort.setSelPos(0);
            bFind = true;
            break;
        }
    }
    if(!bFind)
    {
        GraphicPort tmpPort;
        tmpPort.setSelPos(0);
        tmpPort.setLinkPos(pos);
        tmpPort.setGraphic(joinGraphic);
        _port.push_back(tmpPort);
    }
}

void BusGraphic::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    QGraphicsLineItem::paint(painter,option,widget);
    if(getSelect())
    {
        painter->save();
        painter->setBrush(QBrush(Qt::green));
        painter->setPen(QPen(QBrush(Qt::black),1));

        QLineF lineBus = this->line();
        QPointF center = lineBus.pointAt(0.5);
        painter->drawRect(center.x()-PORTSIZE,center.y()-PORTSIZE,PORTSIZE * 2,PORTSIZE * 2);
        double length = lineBus.length();
        double pos = PORTSIZE / length;
        QPointF begin = lineBus.pointAt(pos);
        QPointF end = lineBus.pointAt(1 - pos);
        painter->drawRect(begin.x() - PORTSIZE,begin.y()-PORTSIZE,PORTSIZE * 2,PORTSIZE * 2);
        painter->drawRect(end.x() - PORTSIZE,end.y()-PORTSIZE,PORTSIZE * 2,PORTSIZE * 2);
        painter->restore();
    }
}
