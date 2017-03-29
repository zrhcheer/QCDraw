#include "stationgraphic.h"
#include <QPainter>
#include <QPainterPath>
#include "linegraphic.h"
const QString StationGraphic::_devName = CodeConvertor::fromLocal("厂站");

StationGraphic::StationGraphic()
{
    setType(Graphic::GRAPHIC_STATION);
    this->setColor(QColor(22,149,19));
    _flagClr = QColor(255,0,0);
    _isTNode = false;
    _isFlag = false;
    _portPoints.resize(1);
    _portPoints[0].setJoinPoint(QPointF(0,0));
    _portPoints[0].setJoinType(GraphicPortPoint::JOIN_MUTI);
}

void StationGraphic::prepareGraphic(QPainter *painter)
{
    GraphicBase::prepareGraphic(painter);
}

void StationGraphic::setLine(LineGraphic* lineGraphic,int pos)
 {
    bool bFind = false;
    for(QVector<GraphicPort>::Iterator iterLine =  _port.begin();
        iterLine != _port.end(); ++iterLine)
    {
        GraphicPort& tmpPort = *iterLine;
        if(tmpPort.getGraphic() == lineGraphic)
        {
            tmpPort.setLinkPos(pos);
            bFind = true;
            break;
        }
    }
    if(!bFind)
    {
        GraphicPort  tmpPort;
        tmpPort.setGraphic(lineGraphic);
        tmpPort.setSelPos(0);
        tmpPort.setLinkPos(pos);
        _port.push_back(tmpPort);
    }
}

void StationGraphic::loadXML(rapidxml::xml_node<char> *node)
{
    string color,size,posPoint,ports;
    for(rapidxml::xml_attribute<char>* attr = node->first_attribute();attr;
        attr = attr->next_attribute())
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
        else if(0 == strcmp("isTNode",attr->name()))
        {
            _isTNode = atoi(attr->value());
        }
        else  if(0 == strcmp("volLevelId",attr->name()))
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
        this->loadPortPos();
}

void StationGraphic::restoreGraphic(QDataStream& dataStream)
{
    dataStream >> _id;
    dataStream >> _name;
    dataStream >> _direct;
    dataStream >> _isTNode;
    dataStream  >> _volLevelId;
    dataStream >> _color;
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
    //_port.clear();//zrh data error
    this->loadPortPos();
}

void StationGraphic::saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic)
{
    int color_r,color_g,color_b;
    _color.getRgb(&color_r,&color_g,&color_b);
    int isTNode;
    if(_isTNode)
    {
        isTNode = 1;
    }
    else
    {
        isTNode = 0;
    }
    char* type = doc.allocate_string(QString::number(_type).toStdString().c_str());  //配置属性
    node->append_attribute(doc.allocate_attribute("type",type));

    char* id = doc.allocate_string(QString::number(_id).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("id",id));

    char* name = doc.allocate_string(_name.toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("name",name));

    char* direct = doc.allocate_string(QString::number(_direct).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("direct",direct));

    char* istNode = doc.allocate_string(QString::number(isTNode).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("isTNode",istNode));

    char* volLevelId = doc.allocate_string(QString::number(_volLevelId).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("volLevelId",volLevelId));

    string colorStr;
    colorStr += QString::number(color_r).toStdString() + ","
            + QString::number(color_g).toStdString() + ","
            + QString::number(color_b).toStdString() + ";";
    char* color = doc.allocate_string(colorStr.c_str());
    node->append_attribute(doc.allocate_attribute("color",color));

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
void StationGraphic::saveGraphic(QDataStream& dataStream) const
{
    dataStream << _type;
    dataStream << _id;
    dataStream << _name;
    dataStream << _direct;
    dataStream << _isTNode;
    dataStream  << _volLevelId;
    dataStream << _color;
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

void StationGraphic::setPosition(const QPointF& pos)
{
    //QPointF movePoint = pos - this->pos();
    this->setPos(pos);
    //对线进行移动
    for(QVector<GraphicPort>::Iterator iterJoint = _port.begin();
        iterJoint != _port.end(); ++iterJoint)
    {
        GraphicPort& tmpPort = *iterJoint;
        LineGraphic* tmpGraphic = dynamic_cast<LineGraphic*>(tmpPort.getGraphic());
        if(tmpGraphic)
        {
            int direct = tmpPort.getLinkPos();
            tmpGraphic->setJointPointDis(direct,this->pos(),this->getSize().width() / 2);
        }
        //tmpGraphic->moveJointPoint(direct,movePoint);
    }
}

void StationGraphic::drawGraphic(QPainter *painter)
{
    if(_isTNode)
    {
        painter->drawEllipse(QPoint(0,0),_size.width() / 2 -4,_size.height() / 2 - 4);
    }
    else
    {
        if(!_isFlag)
        {
            QPainterPath painterPath;
            painterPath.addEllipse(QPoint(0,0),_size.width() / 2 -4,_size.height() / 2 - 4);
            painterPath.addEllipse(QPoint(0,0),_size.width() / 6 ,_size.height() / 6 );
            painterPath.setFillRule(Qt::OddEvenFill);
            painter->drawPath(painterPath);
        }
        else
        {
            QPainterPath painterPath;
            painterPath.addEllipse(QPoint(0,0),_size.width() / 2 -4,_size.height() / 2 - 4);
            painterPath.addEllipse(QPoint(0,0),_size.width() / 3 - 2 ,_size.height() / 3 - 2 );
            painterPath.setFillRule(Qt::OddEvenFill);
            painter->drawPath(painterPath);

            painter->save();
            QPainterPath painterInPath;
            painterInPath.addEllipse(QPoint(0,0),_size.width() / 3 - 2,_size.height() / 3 - 2);
            painterInPath.addEllipse(QPoint(0,0),_size.width() / 6 ,_size.height() / 6 );
            painterInPath.setFillRule(Qt::OddEvenFill);
            painter->setBrush(QBrush(_flagClr));
            painter->drawPath(painterInPath);
            painter->restore();
        }
    }
    //painter->drawEllipse(QPoint(0,0),_size.width() / 2 -4,_size.height() / 2 - 4);
}
