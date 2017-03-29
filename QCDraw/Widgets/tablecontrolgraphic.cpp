#include "tablecontrolgraphic.h"
#include <QPainter>
#include <QHBoxLayout>

const QString TableControlGraphic::_devName = CodeConvertor::fromLocal("����");

TableControlGraphic::TableControlGraphic(QWidget* parent) :
    WidgetGraphicBase(parent)
{
    this->setType(Graphic::GRAPHIC_CONTROL_TABLE);
    _table = new QTableWidget(3,3,this);
    this->setCurWidget(_table);
    //this->resize(_table->width() + 12,_table->height() + 12);
}

void TableControlGraphic::loadXML(rapidxml::xml_node<char> *node)
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

void TableControlGraphic::restoreGraphic(QDataStream& dataStream)
{
    dataStream >> _name;
    dataStream >> _id;
    QRect rect;
    dataStream >> rect;
    this->setGeometry(rect);
}

void TableControlGraphic::saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic)
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

void TableControlGraphic::saveGraphic(QDataStream& dataStream) const
{
    dataStream << _type;
    dataStream << _name;
    dataStream << _id;
    dataStream << this->geometry();
}

