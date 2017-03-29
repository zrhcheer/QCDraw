#include "shrinktick.h"
#include <QHBoxLayout>
#include "pixwidget.h"

const QString ShrinkTick::_devName = CodeConvertor::fromLocal("�嶯");

ShrinkTick::ShrinkTick(QGraphicsItem *parent) :
    QGraphicsProxyWidget(parent)
{
    this->setType(Graphic::GRAPHIC_CONTROL_SHRINK);
    _tabWid = new ShrinkWidget;
    this->setWidget(_tabWid);
    _bTiny = true;
    this->setZValue(2.0);

}
ShrinkTick::~ShrinkTick()
{
}

void	ShrinkTick::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event )
{
    if(_bTiny)
    {
        this->resize(700,600);
        //this->setAttribute(Qt::WA_TranslucentBackground);
    }
    else
    {
        this->resize(70,60);
        //this->setAttribute(Qt::WA_TranslucentBackground,false);
    }
    _bTiny = !_bTiny;
    _tabWid->setTiny(_bTiny);
}

void ShrinkTick::loadXML(rapidxml::xml_node<char> *node)
{
    string rect_x,rect_y,rect_w,rect_h;
    for(rapidxml::xml_attribute<char>* attr = node->first_attribute();attr;attr = attr->next_attribute())
    {
        if("name" == (string)attr->name())
        {
            _name = attr->value();
        }
        else if("id" == (string)attr->name())
        {
            _id = atoll(attr->value());
        }
        else if("rect_x" == (string)attr->name())
        {
            rect_x = attr->value();
        }
        else if("rect_y" == (string)attr->name())
        {
            rect_y = attr->value();
        }
        else if("rect_h" == (string)attr->name())
        {
            rect_h = attr->value();
        }
        else if("rect_w" == (string)attr->name())
        {
            rect_w = attr->value();
        }
    }
    QRect rect;
    rect.setRect(atoi(rect_x.c_str()),atoi(rect_y.c_str()),atoi(rect_w.c_str()),atoi(rect_h.c_str()));
    this->setGeometry(rect);
}

void ShrinkTick::restoreGraphic(QDataStream& dataStream)
{
    dataStream >> _name;
    dataStream >> _id;
    QRect rect;
    dataStream >> rect;
    this->setGeometry(rect);
}

void ShrinkTick::saveXML(rapidxml::xml_node<char> *node, rapidxml::xml_document<> &doc,Graphic* graphic)
{
    char* type = doc.allocate_string(QString::number(_type).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("type",type));
    char* name = doc.allocate_string(_name.toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("name",name));
    char* id = doc.allocate_string(QString::number(_id).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("id",id));
    char* rect_x = doc.allocate_string(QString::number(this->geometry().x()).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("rect_x",rect_x));
    char* rect_y = doc.allocate_string(QString::number(this->geometry().y()).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("rect_y",rect_y));
    char* rect_w = doc.allocate_string(QString::number(this->geometry().width()).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("rect_w",rect_w));
    char* rect_h = doc.allocate_string(QString::number(this->geometry().height()).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("rect_h",rect_h));
}

void ShrinkTick::saveGraphic(QDataStream& dataStream) const
{
    dataStream << _type;
    dataStream << _name;
    dataStream << _id;
    dataStream << this->geometry();
}

bool ShrinkTick::isPointOver(const QPointF& point) const
{
    return false;
}

void ShrinkTick::addShrink(const QString& name,const CdData& shrinkData)
{
    _tabWid->addShrink(name,shrinkData);
}