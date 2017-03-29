#include "graphicbase.h"
#include <math.h>
#include "qcdrawscene.h"
#include "groupgraphicbase.h"
#include "linegraphic.h"
#include <QTextStream>
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "Widgets/shrinktick.h"

GraphicBase::GraphicBase(QGraphicsItem * parent) :
    QGraphicsItem(parent)
{
    this->setDirect(Graphic::POS_RIGHT);
    _captionGraphic = NULL;
    _tickGraphic = NULL;
    this->setZValue(1.0);
}

void GraphicBase::setCaption(const QString& caption)
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
        _captionGraphic = new CaptionGraphic(this);
        _captionGraphic->setDirect(this->getDirect());
        switch (this->getDirect())
        {
        case POS_UP:
        case POS_DOWN:
            _captionGraphic->setPos(-_size.width() / 2 - 10 , 0);
            break;
        case POS_LEFT:
        case POS_RIGHT:
            _captionGraphic->setPos(0 , -_size.width() / 2 - 10);
            break;
        }
    }
    _captionGraphic->setText(caption);
}

void GraphicBase::setCaption(const QString& caption,const QPointF& pos)
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
        _captionGraphic = new CaptionGraphic(this);
    }
    _captionGraphic->setText(caption);
    _captionGraphic->setPos(pos);
}

void GraphicBase::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    UNUSED(option);
    UNUSED(widget);
    painter->save();
    prepareGraphic(painter);
    drawGraphic(painter);
    if(getSelect())
    {
        drawSelect(painter);
    }
    painter->restore();
}
//void GraphicBase::drawPort(QPainter *painter)
//{
//    painter->save();
//    painter->setBrush(QBrush(Qt::red));
//    for(QVector<GraphicPortPoint>::Iterator iterJoinPoints =  _portPoints.begin();
//        iterJoinPoints != _portPoints.end(); ++iterJoinPoints)
//    {
//        GraphicPortPoint& tmpPortPoint = *iterJoinPoints;
//        if(tmpPortPoint.getIsNeedJoin())
//        {
//            const QPointF& tmpPoint = tmpPortPoint.getJoinPoint();
//            painter->drawRect(tmpPoint.x() - PORTSIZE,tmpPoint.y() - PORTSIZE,PORTSIZE * 2, PORTSIZE * 2);
//            painter->drawLine(tmpPoint.x(),tmpPoint.y() - PORTSIZE / 2,tmpPoint.x(),tmpPoint.y() + PORTSIZE / 2);
//            painter->drawLine(tmpPoint.x() - PORTSIZE / 2,tmpPoint.y(),tmpPoint.x() + PORTSIZE / 2,tmpPoint.y());
//        }
//    }
//    painter->restore();
//}

void GraphicBase::drawLock(QPainter *painter)
{
    painter->save();
    painter->setBrush(Qt::white);
    painter->setPen(QPen(QBrush(Qt::black),1));
    //painterPath.a
    painter->drawRect(-4,0,8,4);
    painter->drawChord(-4,-4,8,8,0,180 * 16);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(QBrush(Qt::blue),1,Qt::DashDotLine));
    painter->drawRect(-_size.width() / 2,-_size.height() / 2,_size.width(),_size.height());
    painter->restore();
}

void GraphicBase::drawSelect(QPainter *painter)
{
    painter->save();
    painter->setBrush(QBrush(Qt::green));
    painter->setPen(QPen(QBrush(Qt::black),1));
    painter->drawRect(-3,-3,6,6);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(QBrush(Qt::blue),1,Qt::DashDotLine));
    painter->drawRect(-_size.width() / 2,-_size.height() / 2,_size.width(),_size.height());
    painter->restore();
}

void GraphicBase::hidePortAnchor(int selPos)
{
    if(selPos < _portPoints.size())
    {
        _portPoints[selPos].hideAnchor();
    }
    else
    {
        assert(false);
    }
}

void GraphicBase::hidePortAnchor()
{
    for(int i = 0; i < _portPoints.size(); ++i)
    {
        _portPoints[i].hideAnchor();
    }
}

void GraphicBase::showPortAnchor(int selPos)
{
    if(selPos < _portPoints.size())
    {
        _portPoints[selPos].showAnchor(this,selPos);
    }
    else
    {
        assert(false);
    }
}

bool GraphicBase::delLink(int selPos,Graphic* graphic)
{
    for(QVector<GraphicPort>::Iterator iterPort = _port.begin();
        iterPort != _port.end(); )
    {
        GraphicPort& port = *iterPort;
        if(selPos == port.getSelPos() && graphic == port.getGraphic())
        {
            _port.erase(iterPort);
            return true;
        }
        else
        {
            iterPort ++;
        }
    }
    return false;
}
//删除厂站连接
void GraphicBase::unlinkGraphic()
{
    QVector<GraphicPort>& ports = this->getPorts();
    for(QVector<GraphicPort>::Iterator iterPort = ports.begin();
        iterPort != ports.end(); ++iterPort)
    {
        GraphicPort& tmpPort = *iterPort;
        Graphic* tmpGraphic = tmpPort.getGraphic();
        if(tmpGraphic)
        {
            tmpGraphic->delLink(tmpPort.getLinkPos(),tmpGraphic);
        }
    }
    ports.clear();
}

bool GraphicBase::delJoin(int selPos)
{
    for(QVector<GraphicPort>::Iterator iterPort = _port.begin();
        iterPort != _port.end(); )
    {
        GraphicPort& port = *iterPort;
        if(selPos == port.getSelPos())
        {
            Graphic* graphic = port.getGraphic();
            graphic->delLink(port.getLinkPos(),this);
            iterPort = _port.erase(iterPort);
        }
        else
        {
            ++iterPort;
        }
    }
    return true;
}

bool GraphicBase::isJointed(int selPos)
{
    for(QVector<GraphicPort>::Iterator iterPort = _port.begin();
        iterPort != _port.end(); ++iterPort)
    {
        GraphicPort& tmpPort = *iterPort;
        if(tmpPort.getSelPos() == selPos)
        {
            return true;
        }
    }
    return false;
}

void GraphicBase::prepareGraphic(QPainter *painter)
{
    //painter->translate(this->pos());
    //painter->rotate(_angle);
    painter->setBrush(QBrush(_color));
    painter->setPen(_color);
}
QRectF GraphicBase::boundingRect() const
{
    float halfWidth = _size.width() / 2.0;
    float halfHeight = _size.height() / 2.0;
    switch(this->getDirect())
    {
    case POS_UP:
        return QRectF(- halfWidth,- halfHeight,_size.width(),_size.height());
        break;
    case POS_RIGHT:
        return QRectF(- halfHeight,- halfWidth,_size.height(),_size.width());
        break;
    case POS_DOWN:
        return QRectF(- halfWidth,- halfHeight,_size.width(),_size.height());
        break;
    case POS_LEFT:
        return QRectF(- halfHeight,- halfWidth,_size.height(),_size.width());
        break;
    }
    return QRectF(- halfHeight,- halfHeight,_size.height(),_size.height());
}

void GraphicBase::restoreGraphic(QDataStream& dataStream)
{
    dataStream >> _id;
    dataStream >> _name;
    dataStream >> _direct;
    dataStream >> _volLevelId;
    dataStream >> _color;
    dataStream >> _bMirror;
    QPointF posPoint;
    dataStream >> posPoint;
    this->setPos(posPoint);
    dataStream >> _size;

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
    this->loadPortPos();
}

void GraphicBase::loadXML(rapidxml::xml_node<char> *node)
{
    string color,size,posPoint,ports;
    for(rapidxml::xml_attribute<char>* attr = node->first_attribute();attr;attr = attr->next_attribute())
    {
        if(0 == strcmp("id",attr->name()))
        {
            _id = atoll(attr->value());
        }
        else if(0 == strcmp("name",attr->name()))
        {
            _name = attr->value();
        }
        else if(0 == strcmp("direct",attr->name()))
        {
            _direct = atoi(attr->value());
        }
        else if(0 == strcmp("volLevelId",attr->name()))
        {
            _volLevelId = atoll(attr->value());
        }
        else if(0 == strcmp("color",attr->name()))
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
        else if(0 == strcmp("bMirror",attr->name()))
        {
            _bMirror = atoi(attr->value());
        }
        else if(0 == strcmp("size",attr->name()))
        {
            size = attr->value();
            size_t pos = size.find(",",0);
            string size_width = size.substr(0,pos);
            size_t pos1 = size.find(";",pos + 1);
            string size_height = size.substr(pos + 1,pos1 - pos - 1);
            _size.setHeight(atoi(size_height.c_str()));
            _size.setWidth(atoi(size_width.c_str()));
        }
        else if(0 == strcmp("pos",attr->name()))
        {
            posPoint = attr->value();
            size_t pos = posPoint.find(",",0);
            string posPoint_x = posPoint.substr(0,pos);
            size_t pos1 = posPoint.find(";",pos + 1);
            string posPoint_y = posPoint.substr(pos + 1,pos1 - pos - 1);
            QPointF posPoint;
            posPoint.setX(atoi(posPoint_x.c_str()));
            posPoint.setY(atoi(posPoint_y.c_str()));
            this->setPos(posPoint);
        }
        else if(0 == strcmp("num",attr->name()))
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
    this->loadPortPos();
}

void GraphicBase::saveXML(rapidxml::xml_node<char> *node, rapidxml::xml_document<> &doc,Graphic* graphic)
{
    int color_r,color_g,color_b;
    _color.getRgb(&color_r,&color_g,&color_b);
    int mirror;
    if(_bMirror)
    {
        mirror = 1;
    }
    else
    {
        mirror = 0;
    }
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
    char* color = doc.allocate_string(colorStr.c_str());
    node->append_attribute(doc.allocate_attribute("color",color));

    char* bMirror = doc.allocate_string(QString::number(mirror).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("bMirror",bMirror));

    string size;
    size += QString::number(_size.width()).toStdString() + ","
            + QString::number(_size.height()).toStdString() + ";";
    node->append_attribute(doc.allocate_attribute("size",doc.allocate_string(size.c_str())));

    string posPoint;
    posPoint += QString::number(this->pos().x()).toStdString() + ","
            + QString::number(this->pos().y()).toStdString() + ";";
    node->append_attribute(doc.allocate_attribute("pos",doc.allocate_string(posPoint.c_str())));

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
    char* ports = doc.allocate_string(graPort.toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("ports",ports));

}

void GraphicBase::saveGraphic(QDataStream& dataStream) const
{
    dataStream << _type;
    dataStream << _id;
    dataStream << _name;
    dataStream << _direct;
    dataStream << _volLevelId;
    dataStream << _color;
    dataStream << _bMirror;
    dataStream << this->pos();
    dataStream << _size;

    //标签
    if(_captionGraphic)
    {
        dataStream << int(1);//标签数量
        _captionGraphic->saveGraphic(dataStream);
    }
    else
    {
        dataStream << int(0);
    }
    //接点
    dataStream << _port;
}
void GraphicBase::setPosition(const QPointF& pos)
{
    QPointF movePoint = pos - this->pos();
    this->setPos(pos);
    if(_shrink)
    {
        _shrink->setPos(_shrink->pos() + movePoint);
    }
    //对线进行移动
    for(QVector<GraphicPort>::Iterator iterPort = _port.begin();
        iterPort != _port.end(); ++iterPort)
    {
        GraphicPort& tmpPort = *iterPort;
        Graphic* tmpGraphic = tmpPort.getGraphic();
        if(tmpGraphic)
        {
            if(tmpGraphic->isLine())
            {
                LineGraphic* lineGraphic = (LineGraphic*)tmpGraphic;
                lineGraphic->moveJointPoint(tmpPort.getLinkPos(),movePoint);
            }
        }
    }
}

int GraphicBase::getSizeChangeFlag(const QPointF& point)
{
    QSize size = this->getSize();
    QPointF curPoint = point - this->getPosition();
    curPoint.setX(curPoint.x() - size.width() /2);
    curPoint.setY(curPoint.y() - size.height() /2);
    if(curPoint.x() < 0 || curPoint.x() > size.width() || curPoint.y() < 0 || curPoint.y() > size.height())
    {
        return 0;
    }
    if(curPoint.x() < 6)//
    {
        if(curPoint.y() < 6)
        {
            return SIZECH_LEFT | SIZECH_TOP;
        }
        else if(curPoint.y() > size.height() - 6)
        {
            return SIZECH_LEFT | SIZECH_BOM;
        }
    }
    else if(curPoint.x() > size.width() - 6)
    {
        if(curPoint.y() < 6)
        {
            return SIZECH_RIGHT | SIZECH_TOP;
        }
        else if(curPoint.y() > size.height() - 6)
        {
            return SIZECH_RIGHT | SIZECH_BOM;
        }
    }
    return 0;
}
bool GraphicBase::isPointOver(const QPointF& point) const
{
    QPointF pointLeave = point - this->getPosition();
    pointLeave.setX(pointLeave.x() + _size.width() / 2);
    pointLeave.setY(pointLeave.y() + _size.height() / 2);
    if(pointLeave.x() < 0 || pointLeave.x() > _size.width())
    {
        return false;
    }
    if(pointLeave.y() < 0 || pointLeave.y() > _size.height())
    {
        return false;
    }
    return true;
}

set<int> GraphicBase::queryUnMountPos()
{
    set<int> tmpJoin;
    QVector<GraphicPortPoint>& portPoints =   getJoinPortPoint();
    for(int i = 0; i < portPoints.size(); i++)
    {
        tmpJoin.insert(i);
    }
    for(QVector<GraphicPort>::Iterator iterPort =  _port.begin();
        iterPort != _port.end(); ++iterPort)
    {
        GraphicPort& tmpPort = *iterPort;
        tmpJoin.erase(tmpPort.getSelPos());
    }
    return tmpJoin;
}

//一端为母线，别的端为线路或不连可绕母线移动
bool GraphicBase::moveAroundBus(const QPointF& point)
{
    BusGraphic* tmpBus = NULL;
    int linkPos;
    for(QVector<GraphicPort>::Iterator iterPort = _port.begin();
        iterPort != _port.end(); ++iterPort)
    {
        GraphicPort& tmpPort = *iterPort;
        Graphic* graphic = tmpPort.getGraphic();
        if(!graphic)
        {
            continue;
        }
        switch(graphic->getType())
        {
        case Graphic::GRAPHIC_BUS :
            if(tmpBus)
            {
                return false;
            }
            else
            {
                tmpBus = dynamic_cast<BusGraphic*>(graphic);
                linkPos = tmpPort.getSelPos();
            }
            break;
        case Graphic::GRAPHIC_LINE:
            break;
        default:
            return false;
            break;
        }
    }
    if(tmpBus)//进行绕母线移动
    {
        QLineF line = tmpBus->line();
        QPointF firPoint = line.p1();
        QPointF secPoint = line.p2();
        QPointF joinPoint;
        //决定元件方向
        switch(tmpBus->getDirect())
        {
        case Graphic::POS_DOWN:
        case Graphic::POS_UP:
            joinPoint.setX(firPoint.x());
            joinPoint.setY(point.y());
            if(point.x() < firPoint.x())//在左
            {
                switch(linkPos)
                {
                case Graphic::JOIN_BEGIN:
                    this->setDirect(Graphic::POS_RIGHT);
                    break;
                case Graphic::JOIN_END:
                    this->setDirect(Graphic::POS_LEFT);
                    break;
                case Graphic::JOIN_MID:
                    this->setDirect(Graphic::POS_UP);
                    break;
                }
            }
            else//在右
            {
                switch(linkPos)
                {
                case Graphic::JOIN_BEGIN:
                    this->setDirect(Graphic::POS_LEFT);
                    break;
                case Graphic::JOIN_END:
                    this->setDirect(Graphic::POS_RIGHT);
                    break;
                case Graphic::JOIN_MID:
                    this->setDirect(Graphic::POS_DOWN);
                    break;
                }
            }
            this->loadPortPos();
            break;
        case Graphic::POS_LEFT:
        case Graphic::POS_RIGHT:
            joinPoint.setX(point.x());
            joinPoint.setY(firPoint.y());
            if(point.y() > firPoint.y())
            {
                switch(linkPos)
                {
                case Graphic::JOIN_BEGIN:
                    this->setDirect(Graphic::POS_UP);
                    break;
                case Graphic::JOIN_END:
                    this->setDirect(Graphic::POS_DOWN);
                    break;
                case Graphic::JOIN_MID:
                    this->setDirect(Graphic::POS_LEFT);
                    break;
                }
            }
            else
            {
                switch(linkPos)
                {
                case Graphic::JOIN_BEGIN:
                    this->setDirect(Graphic::POS_DOWN);
                    break;
                case Graphic::JOIN_END:
                    this->setDirect(Graphic::POS_UP);
                    break;
                case Graphic::JOIN_MID:
                    this->setDirect(Graphic::POS_RIGHT);
                    break;
                }
            }
            this->loadPortPos();
            break;
        }
        //决定元件位置和连线位
        //QPointF tmpPos = this->pos();
        QPointF tmpJoinPos = this->getPortPos(linkPos);
        QPointF realPos = joinPoint  - tmpJoinPos;
        this->setPos(realPos);
        this->update();
        //移动连线
        LineGraphic* lineGraphic = NULL;
        for(QVector<GraphicPort>::Iterator iterPort = _port.begin();
            iterPort != _port.end(); ++iterPort)
        {
            GraphicPort& tmpPort = *iterPort;
            Graphic* graphic = tmpPort.getGraphic();
            if(!graphic)
            {
                continue;
            }
            switch(graphic->getType())
            {
            case Graphic::GRAPHIC_BUS :
                break;
            case Graphic::GRAPHIC_LINE:
                tmpJoinPos = this->getPortPos(tmpPort.getSelPos());
                lineGraphic = dynamic_cast<LineGraphic*>(graphic);
                lineGraphic->setJointPoint(tmpPort.getLinkPos(),realPos + tmpJoinPos);
                break;
            default:
                assert(false);
                break;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

void GraphicBase::setJointGraphic(int direct,GraphicBase* basicGraphic,int directOther)
{
    if(basicGraphic)
    {
        this->setPortGraphic(direct,basicGraphic,directOther);
//        _port[direct].setGraphic(basicGraphic);
//        _port[direct].setLinkPos(directOther);
//        _port[direct].setSelPos(direct);
    }
}
GroupDeal GraphicBase::initLink(map<ulong64,Graphic*>& allElement)
{
    GroupGraphicBase* groupGraphic = NULL;
    GroupDeal groupDeal;
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
                if(tmpParent)
                {
                    GroupGraphicBase* parent = dynamic_cast<GroupGraphicBase*>(tmpParent);
                    if(!groupGraphic)
                    {
                        groupGraphic = parent;
                    }
                    else
                    {
                        if(groupGraphic != parent)
                        {
                            QList<QGraphicsItem *> curGroup = parent->childItems();
                            for(QList<QGraphicsItem *>::Iterator iterCurGroup = curGroup.begin();
                                iterCurGroup != curGroup.end(); ++iterCurGroup)
                            {
                                QGraphicsItem* curItem = *iterCurGroup;
                                parent->removeFromGroup(curItem);
                                groupGraphic->addToGroup(curItem);
                            }
                            //parent->removeFromGroup(tmpParent);
                            //groupGraphic->addToGroup(tmpParent);
                            groupDeal.addDeal(GroupDeal::GROUPD_DEL,parent);
                            //groupDeal.addDeal(GroupDeal::GROUPD_DEL,parent);
                        }
                    }
                }
                else
                {
                    if(!groupGraphic)
                    {
                        groupGraphic = new GroupGraphicBase();
                        groupDeal.addDeal(GroupDeal::GROUPD_ADD,groupGraphic);
                    }
                    groupGraphic->addToGroup(graphicItem);
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
//元件和元件相联
GroupDeal GraphicBase::setPortBasic(int direct,GraphicBase* basicGraphic,int directOther)
{
    if(basicGraphic)
    {
        this->setPortGraphic(direct,basicGraphic,directOther);
//        _port[direct].setGraphic(basicGraphic);
//        _port[direct].setLinkPos(directOther);
//        _port[direct].setSelPos(direct);
        basicGraphic->setJointGraphic(directOther,this,direct);
        if(!this->isLine() ||
                !basicGraphic->isLine())
        {
            return groupGraphicItem(basicGraphic);
        }
    }
    return  GroupDeal(GroupDeal::GROUPD_UNKNOW,NULL);
}

GroupDeal GraphicBase::setPortBus(int direct,BusGraphic* busGraphic,const double& busPos)
{
    if(busGraphic)
    {
        this->setPortGraphic(direct,busGraphic,busPos);
//        _port[direct].setGraphic(busGraphic);
//        _port[direct].setLinkPos(busPos);
//        _port[direct].setSelPos(direct);

        //_port[direct].setDirect(direct);
        QPointF lineBus = busGraphic->line().pointAt(busPos);
        QPointF posSide = this->getPortPos(direct);
        this->setPos(lineBus - posSide);
        busGraphic->setJoinGraphic(this,direct);
        if(!this->isLine())
        {
            return groupGraphicItem(busGraphic);
        }
    }
    return  GroupDeal(GroupDeal::GROUPD_UNKNOW,NULL);
}
GroupDeal  GraphicBase::setPortBus(int direct,BusGraphic* busGraphic)
{
    if(busGraphic)
    {
        this->setPortGraphic(direct,busGraphic,0);
//        _port[direct].setGraphic(busGraphic);
//        _port[direct].setLinkPos(0);
//        _port[direct].setSelPos(direct);
        //_port[direct].setDirect(direct);
        //計算控件位置
        QPointF pointJoint = this->getPortPos(direct) + this->pos();
        QLineF busLine = busGraphic->line();
        if(fabs(busLine.x1() - busLine.x2()) < 0.1)
        {
            pointJoint.setX(busLine.x1());
        }
        else
        {
            pointJoint.setY(busLine.y1());
        }
        pointJoint -= this->getPortPos(direct);
        this->setPosition(pointJoint);

        //QPointF joinPoint = this->getPortPos(direct);
        //QLineF busLine = busGraphic->line();
        //得到母线上对应的点
        //QPointF lineBus = busGraphic->line().pointAt(busPos);
        //QPointF posSide = this->getPortPos(direct);
        //this->setPos(lineBus - posSide);
        busGraphic->setJoinGraphic(this,direct);
        //元件連到母线上則放到一个組中
        return groupGraphicItem(busGraphic);
    }
    return  GroupDeal(GroupDeal::GROUPD_UNKNOW,NULL);
}
void GraphicBase::setPortGraphic(int pos,Graphic* joint,int posLink)
{
    bool bFind = false;
    for(QVector<GraphicPort>::Iterator iterPort = _port.begin();
        iterPort != _port.end(); ++iterPort)
    {
        GraphicPort& tmpPort = *iterPort;
        if(tmpPort.getGraphic() && tmpPort.getGraphic() == joint)
        {
            bFind = true;
            break;
        }
    }
    if(!bFind)
    {
        GraphicPort tmpPort;
        tmpPort.setSelPos(pos);
        tmpPort.setGraphic(joint);
        tmpPort.setLinkPos(posLink);
        _port.push_back(tmpPort);
    }
}
GroupDeal GraphicBase::groupGraphicItem(BusGraphic* firstItem)
{
    GroupGraphicBase* firstParent = (GroupGraphicBase*)firstItem->parentItem();
    GroupGraphicBase* secParent = (GroupGraphicBase*)this->parentItem();
    if(firstParent  && secParent)
    {
        QList<QGraphicsItem *> secChild = secParent->childItems();
        for(QList<QGraphicsItem *>::Iterator iterChild = secChild.begin();
            iterChild != secChild.end(); ++iterChild)
        {
            QGraphicsItem* tmpChile = *iterChild;
            secParent->removeFromGroup(tmpChile);
            firstParent->addToGroup(tmpChile);
        }
        return  GroupDeal(GroupDeal::GROUPD_DEL,secParent);
    }
    else if(firstParent)
    {
        firstParent->addToGroup(this);
        //secItem->setParentItem(firstParent);
    }
    else if(secParent)
    {
        secParent->addToGroup(firstItem);
        //firstItem->setParentItem(secParent);
    }
    else
    {
        GroupGraphicBase* parent = new 	GroupGraphicBase();
        parent->addToGroup(firstItem);
        parent->addToGroup(this);
        return GroupDeal(GroupDeal::GROUPD_ADD,parent);
    }
    return  GroupDeal(GroupDeal::GROUPD_UNKNOW,NULL);
}
GroupDeal GraphicBase::groupGraphicItem(GraphicBase* firstItem)
{
    GroupGraphicBase* firstParent = (GroupGraphicBase*)firstItem->parentItem();
    GroupGraphicBase* secParent = (GroupGraphicBase*)this->parentItem();
    if(firstParent  && secParent)
    {
        QList<QGraphicsItem *> secChild = secParent->childItems();
        for(QList<QGraphicsItem *>::Iterator iterChild = secChild.begin();
            iterChild != secChild.end(); ++iterChild)
        {
            QGraphicsItem* tmpChile = *iterChild;
            secParent->removeFromGroup(tmpChile);
            firstParent->addToGroup(tmpChile);
        }
        return  GroupDeal(GroupDeal::GROUPD_DEL,secParent);
    }
    else if(firstParent)
    {
        firstParent->addToGroup(this);
        //secItem->setParentItem(firstParent);
    }
    else if(secParent)
    {
        secParent->addToGroup(firstItem);
        //firstItem->setParentItem(secParent);
    }
    else
    {
        GroupGraphicBase* parent = new 	GroupGraphicBase();
        parent->addToGroup(firstItem);
        parent->addToGroup(this);
        return GroupDeal(GroupDeal::GROUPD_ADD,parent);
    }
    return  GroupDeal(GroupDeal::GROUPD_UNKNOW,NULL);
}

 void GraphicBase::setTickColor(const QColor& clr)
 {
     if(_tickGraphic)
     {
         _tickGraphic->setColor(clr);
     }
 }

void GraphicBase::setTick(bool bTick,int flag)
{
    if(bTick)
    {
        if(!_tickGraphic)
        {
            _tickGraphic = new TickGraphic(this,flag);
            _tickGraphic->setPos(0,0);
        }
    }
    else
    {
        if(_tickGraphic)
        {
            delete _tickGraphic;
            _tickGraphic = NULL;
        }
    }
}
