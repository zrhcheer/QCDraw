#include "transgraphic.h"

#include "earthgraphic.h"

TransGraphic::TransGraphic()
{
    earthHGraphic = NULL;
    earthLGraphic = NULL;
    earthMGraphic = NULL;
    _connLType = TEARTH_Yn;
    _connMType = TEARTH_Yn;
    _connHType = TEARTH_Yn;
    _highColor.setRgb(2,149,19);
    _lowColor.setRgb(0,0,128);
    _midColor.setRgb(0,128,255);
    _leftColor.setRgb(0,128,255);
    _volLevelIdH = 0;
    _volLevelIdM = 0;
    _volLevelIdL = 0;
    //    _lowColor.setRgb(0,0,128);
    //    _midColor.setRgb(0,128,0);
}

void TransGraphic::loadXML(rapidxml::xml_node<char> *node)
{
    string highColor,lowColor,midColor,size,posPoint,ports;
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
        else  if(0 == strcmp("volLevelIdH",attr->name()))
        {
            _volLevelIdH = atoll(attr->value());
        }
        else  if(0 == strcmp("volLevelIdM",attr->name()))
        {
            _volLevelIdM = atoll(attr->value());
        }
        else  if(0 == strcmp("volLevelIdL",attr->name()))
        {
            _volLevelIdL = atoll(attr->value());
        }
        else if(0 == strcmp("highColor",attr->name()))
        {
            highColor = attr->value();
            size_t pos = highColor.find(",",0);
            string color_r = highColor.substr(0,pos);
            size_t pos1 = highColor.find(",",pos + 1);
            string color_g = highColor.substr(pos + 1,pos1 - pos - 1);
            size_t pos2 = highColor.find(";",pos1 + 1);
            string color_b = highColor.substr(pos1 + 1,pos2 - pos1 - 1);
            _highColor.setRgb(atoi(color_r.c_str()),atoi(color_g.c_str()),atoi(color_b.c_str()));
        }
        else if(0 == strcmp("midColor",attr->name()))
        {
            midColor = attr->value();
            size_t pos = midColor.find(",",0);
            string color_r = midColor.substr(0,pos);
            size_t pos1 = midColor.find(",",pos + 1);
            string color_g = midColor.substr(pos + 1,pos1 - pos - 1);
            size_t pos2 = midColor.find(";",pos1 + 1);
            string color_b = midColor.substr(pos1 + 1,pos2 - pos1 - 1);
            _midColor.setRgb(atoi(color_r.c_str()),atoi(color_g.c_str()),atoi(color_b.c_str()));
        }
        else if(0 == strcmp("lowColor",attr->name()))
        {
            lowColor = attr->value();
            size_t pos = lowColor.find(",",0);
            string color_r = lowColor.substr(0,pos);
            size_t pos1 = lowColor.find(",",pos + 1);
            string color_g = lowColor.substr(pos + 1,pos1 - pos - 1);
            size_t pos2 = lowColor.find(";",pos1 + 1);
            string color_b = lowColor.substr(pos1 + 1,pos2 - pos1 - 1);
            _lowColor.setRgb(atoi(color_r.c_str()),atoi(color_g.c_str()),atoi(color_b.c_str()));
        }
        else  if(0 == strcmp("connLType",attr->name()))
        {
            _connLType = atoi(attr->value());
        }
        else  if(0 == strcmp("connMType",attr->name()))
        {
            _connMType = atoi(attr->value());
        }
        else  if(0 == strcmp("connHType",attr->name()))
        {
            _connHType = atoi(attr->value());
        }
        else  if(0 == strcmp("bMirror",attr->name()))
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

void TransGraphic::restoreGraphic(QDataStream& dataStream)
{
    dataStream >> _id;
    dataStream >> _name;
    dataStream >> _direct;
    dataStream >> _volLevelIdH;
    dataStream >> _volLevelIdM;
    dataStream >> _volLevelIdL;
    dataStream >>  _highColor;
    dataStream >>  _lowColor;
    dataStream >>  _midColor;
    dataStream >> _connLType;
    dataStream >> _connMType;
    dataStream >> _connHType;
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

void TransGraphic::saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic)
{
    int highColor_r,highColor_g,highColor_b;
    _highColor.getRgb(&highColor_r,&highColor_g,&highColor_b);
    int lowColor_r,lowColor_g,lowColor_b;
    _lowColor.getRgb(&lowColor_r,&lowColor_g,&lowColor_b);
    int midColor_r,midColor_g,midColor_b;
    _midColor.getRgb(&midColor_r,&midColor_g,&midColor_b);
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

    char* volLevelIdH = doc.allocate_string(QString::number(_volLevelIdH).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("volLevelIdH",volLevelIdH));

    char* volLevelIdM = doc.allocate_string(QString::number(_volLevelIdM).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("volLevelIdM",volLevelIdM));

    char* volLevelIdL = doc.allocate_string(QString::number(_volLevelIdL).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("volLevelIdL",volLevelIdL));


    string high;
    high += QString::number(highColor_r).toStdString() + ","
            + QString::number(highColor_g).toStdString() + ","
            + QString::number(highColor_b).toStdString() + ";";
    char* highColor = doc.allocate_string(high.c_str());
    node->append_attribute(doc.allocate_attribute("highColor",highColor));

    string low;
    low += QString::number(lowColor_r).toStdString() + ","
            + QString::number(lowColor_g).toStdString() + ","
            + QString::number(lowColor_b).toStdString() + ";";
    char* lowColor = doc.allocate_string(low.c_str());
    node->append_attribute(doc.allocate_attribute("lowColor",lowColor));

    string mid;
    mid += QString::number(midColor_r).toStdString() + ","
            + QString::number(midColor_g).toStdString() + ","
            + QString::number(midColor_b).toStdString() + ";";
    char* midColor = doc.allocate_string(mid.c_str());
    node->append_attribute(doc.allocate_attribute("midColor",midColor));

    char* connLType = doc.allocate_string(QString::number(_connLType).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("connLType",connLType));

    char* connMType = doc.allocate_string(QString::number(_connMType).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("connMType",connMType));

    char* connHType = doc.allocate_string(QString::number(_connHType).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("connHType",connHType));

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

void TransGraphic::saveGraphic(QDataStream& dataStream) const
{
    dataStream << _type;
    dataStream << _id;
    dataStream << _name;
    dataStream << _direct;
    dataStream << _volLevelIdH;
    dataStream << _volLevelIdM;
    dataStream << _volLevelIdL;
    dataStream <<  _highColor;
    dataStream <<  _lowColor;
    dataStream <<  _midColor;
    dataStream << _connLType;
    dataStream << _connMType;
    dataStream << _connHType;
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

void TransGraphic::setEarchType(int pos,int earchType)
{
    switch(pos)
    {
    case Graphic::JOIN_BEGIN:
        if(_connHType != earchType)
        {
            _connHType = earchType;
            this->loadPortPos();
            this->update();
        }
        break;
    case Graphic::JOIN_MID:
        if(_connMType != earchType)
        {
            _connMType = earchType;
            this->loadPortPos();
            this->update();
        }
        break;
    case Graphic::JOIN_LOW:
        if(_connLType != earchType)
        {
            _connLType = earchType;
            this->loadPortPos();
            this->update();
        }
        break;
    }
}

void TransGraphic::posEarch(int pos,const QPointF& joinPt,double radius,int direct,bool bLong)
{
    switch(pos)
    {
    case Graphic::JOIN_HIGH:
        if(TEARTH_Yn == _connHType)
        {
            if(!earthHGraphic)
            {
                earthHGraphic = new EarthGraphic(this);
            }
            earthHGraphic->setColor(_highColor);
            earthHGraphic->setSize(radius);
            //earthHGraphic->setIsOpen(true);
            earthHGraphic->setIsLong(bLong);
            earthHGraphic->setSwitchLen(radius);
            earthHGraphic->setDirect(direct);
            earthHGraphic->setPos(joinPt);
            earthHGraphic->loadPortPos();
        }
        else
        {
            if(earthHGraphic)
            {
                delete earthHGraphic;
                earthHGraphic = NULL;
            }
        }
        break;
    case Graphic::JOIN_MID:
        if(TEARTH_Yn == _connMType)
        {
            if(!earthMGraphic)
            {
                earthMGraphic = new EarthGraphic(this);
            }
            earthMGraphic->setColor(_midColor);
            earthMGraphic->setSize(radius);
            //earthMGraphic->setIsOpen(true);
            earthMGraphic->setIsLong(bLong);
            earthMGraphic->setSwitchLen(radius);
            earthMGraphic->setDirect(direct);
            earthMGraphic->setPos(joinPt);
            earthMGraphic->loadPortPos();
        }
        else
        {
            if(earthMGraphic)
            {
                delete earthMGraphic;
                earthMGraphic = NULL;
            }
        }
        break;
    case Graphic::JOIN_LOW:
        if(TEARTH_Yn == _connLType)
        {
            if(!earthLGraphic)
            {
                earthLGraphic = new EarthGraphic(this);
            }
            earthLGraphic->setColor(_lowColor);
            earthLGraphic->setSize(radius);
            //earthLGraphic->setIsOpen(false);
            earthLGraphic->setIsLong(bLong);
            earthLGraphic->setSwitchLen(radius);
            earthLGraphic->setDirect(direct);
            earthLGraphic->setPos(joinPt);
            earthLGraphic->loadPortPos();
        }
        else
        {
            if(earthLGraphic)
            {
                delete earthLGraphic;
                earthLGraphic = NULL;
            }
        }
        break;
    }
}



void TransGraphic::setEarchState(int pos,bool hasResist,bool  isOpen)
{
    switch(pos)
    {
    case Graphic::JOIN_HIGH:
        if(earthHGraphic)
        {
            earthHGraphic->hide();
            earthHGraphic->setIsOpen(isOpen);
            earthHGraphic->setHasBreaker(hasResist);
            earthHGraphic->show();
        }
        break;
    case Graphic::JOIN_MID:
        if(earthMGraphic)
        {
            earthMGraphic->hide();
            earthMGraphic->setIsOpen(isOpen);
            earthMGraphic->setHasBreaker(hasResist);
            earthMGraphic->show();
        }
        break;
    case Graphic::JOIN_LOW:
        if(earthLGraphic)
        {
            earthLGraphic->hide();
            earthLGraphic->setIsOpen(isOpen);
            earthLGraphic->setHasBreaker(hasResist);
            earthLGraphic->show();
        }
        break;
    }
}

void TransGraphic::setEarchIsOpen(int pos,bool  isOpen)
{
    switch(pos)
    {
    case Graphic::JOIN_HIGH:
        if(earthHGraphic)
        {
            //earthHGraphic->hide();
            earthHGraphic->setIsOpen(isOpen);
        }
        break;
    case Graphic::JOIN_MID:
        if(earthMGraphic)
        {
            //earthHGraphic->hide();
            earthMGraphic->setIsOpen(isOpen);
        }
        break;
    case Graphic::JOIN_LOW:
        if(earthLGraphic)
        {
            earthLGraphic->setIsOpen(isOpen);
        }
        break;
    }
}

void TransGraphic::setEarchHasResist(int pos,bool  hasResist)
{
    switch(pos)
    {
    case Graphic::JOIN_HIGH:
        if(earthHGraphic)
        {
            earthHGraphic->hide();
            earthHGraphic->setHasBreaker(hasResist);
            earthHGraphic->show();
        }
        break;
    case Graphic::JOIN_MID:
        if(earthMGraphic)
        {
            earthMGraphic->hide();
            earthMGraphic->setHasBreaker(hasResist);
            earthMGraphic->show();
        }
        break;
    case Graphic::JOIN_LOW:
        if(earthLGraphic)
        {
            earthLGraphic->hide();
            earthLGraphic->setHasBreaker(hasResist);
            earthLGraphic->show();
        }
        break;
    }
}
void TransGraphic::setVolLevel(int pos,const ulong64& volLevelId)
{
    switch(pos)
    {
    case Graphic::JOIN_HIGH:
        _volLevelIdH = volLevelId;
        break;
    case Graphic::JOIN_MID:
        _volLevelIdM = volLevelId;
        break;
    case Graphic::JOIN_LOW:
        _volLevelIdL = volLevelId;
        break;
    }
}

void TransGraphic::setColor(int pos,const QColor& clr)
{
    switch(pos)
    {
    case Graphic::JOIN_HIGH:
        if(_highColor != clr)
        {
            _highColor = clr;
            update();
        }
        break;
    case Graphic::JOIN_MID:
        if(_midColor != clr)
        {
            _midColor = clr;
            update();
        }
        break;
    case Graphic::JOIN_LOW:
        if(_lowColor != clr)
        {
            _lowColor = clr;
            update();
        }
        break;
    }
}

void TransGraphic::drawTrans(QPainter *painter,const QPointF& centerPt,double radius,int connType)
{
    painter->drawEllipse(centerPt,radius,radius);
    if(TEARTH_D == connType)
    {
        QPointF lowUp(centerPt.x(),centerPt.y() - radius);
        double radis = 30 * M_RADIUS;
        QPointF lowRight(centerPt.x() + radius * cos(radis),
                         centerPt.y() + radius * sin(radis));
        radis = 150 * M_RADIUS;
        QPointF lowLeft(centerPt.x() + radius * cos(radis),
                        centerPt.y() + radius * sin(radis));
        painter->drawLine(lowUp,lowRight);
        painter->drawLine(lowRight,lowLeft);
        painter->drawLine(lowLeft,lowUp);
    }
    else
    {
        double  angle = -30 * M_RADIUS;
        for(int i = 0; i < 3; ++i)
        {
            painter->drawLine(centerPt,
                              QPoint(centerPt.x() + radius * cos(angle),centerPt.y() + radius * sin(angle)));
            angle += 120 * M_RADIUS;
        }
    }
}
