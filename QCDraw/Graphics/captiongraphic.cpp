#include "captiongraphic.h"
#include <QFontMetrics>
#include <QPainter>
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "rapidxml/rapidxml_utils.hpp"

const QString CaptionGraphic::_devName = CodeConvertor::fromLocal("标签");
CaptionGraphic::CaptionGraphic() :
    _font("宋体",10)
{
    //_font.setPointSize(8);
    this->setDirect(Graphic::POS_RIGHT);
    _portPoints.clear();
    setType(Graphic::GRAPHIC_TEXT);
}
CaptionGraphic::CaptionGraphic(QGraphicsItem* parent) :
    QGraphicsItem(parent), _font("宋体",10)
{
    this->setDirect(Graphic::POS_RIGHT);
    setType(Graphic::GRAPHIC_TEXT);
}
CaptionGraphic::CaptionGraphic(const QString& strText,QGraphicsItem* parent) :
    QGraphicsItem(parent), _font("宋体",10)
{
    this->setDirect(Graphic::POS_RIGHT);
    setType(Graphic::GRAPHIC_TEXT);
    this->setText(strText);
}
int CaptionGraphic::fontWidth()
{
    QFontMetrics fontMetrics(_font);
    return fontMetrics.width(_text);
}

int CaptionGraphic::fonrHeight()
{
    QFontMetrics fontMetrics(_font);
    return  fontMetrics.height();
}

void  CaptionGraphic::setText(const QString& strText)
{
    _text = strText;
    QFontMetrics fontMetrics(_font);
    int height = fontMetrics.height();
    int width = fontMetrics.width(_text);
    _size.setWidth(width + 2);
    _size.setHeight(height + 2);
}

void CaptionGraphic::loadXML(rapidxml::xml_node<char> *node)
{
    string pos_x,pos_y;
    string caption;
    for(rapidxml::xml_attribute<char>* attr = node->first_attribute();attr;attr = attr->next_attribute())
    {
        if(0 == strcmp("caption",attr->name()))
        {
            caption = attr->value();
            for(int i = 0;i < caption.size();++i)
            {
                size_t pos = caption.find(",",i);
                _text = QString::fromStdString(caption.substr(i,pos));
                size_t pos1 = caption.find(",",pos + 1);
                _direct = atoi(caption.substr(pos + 1,pos1 - pos - 1).c_str());
                size_t pos2 = caption.find(",",pos1 + 1);
                pos_x = caption.substr(pos1 + 1,pos2 - pos1 - 1);
                size_t pos3 = caption.find(";",pos2 + 1);
                pos_y = caption.substr(pos2 + 1,pos3 - pos2 - 1);
                i = pos3 + 1;
                QFontMetrics fontMetrics(_font);
                int height = fontMetrics.height();
                int width = fontMetrics.width(_text);
                _size.setWidth(width + 2);
                _size.setHeight(height + 2);
                QPointF posPoint;
                posPoint.setX(atof(pos_x.c_str()));
                posPoint.setY(atof(pos_y.c_str()));
                this->setPos(posPoint);
            }
        }
    }
}

void CaptionGraphic::restoreGraphic(QDataStream& dataStream)
{
    dataStream >> _text;
    QFontMetrics fontMetrics(_font);
    int height = fontMetrics.height();
    int width = fontMetrics.width(_text);
    _size.setWidth(width + 2);
    _size.setHeight(height + 2);
    dataStream >> _direct;
    QPointF posPoint;
    dataStream >> posPoint;
    this->setPos(posPoint);
}

void CaptionGraphic::saveXML(rapidxml::xml_node<char> *node, rapidxml::xml_document<> &doc,Graphic* graphic)
{
    string strCaption;
    strCaption += _text.toStdString() + "," + QString::number(_direct).toStdString() + ","
            + QString::number(this->pos().x()).toStdString() + ","
            + QString::number(this->pos().y()).toStdString() + ";";
    node->append_attribute(doc.allocate_attribute("caption",doc.allocate_string(strCaption.c_str())));
}

void CaptionGraphic::saveGraphic(QDataStream& dataStream) const
{
    dataStream << _text;
    dataStream << _direct;
    dataStream << this->pos();
}

void CaptionGraphic::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    UNUSED(option);
    UNUSED(widget);
    //    painter->setPen(Qt::red);
    //    painter->drawRect(this->boundingRect());

    painter->save();
    prepareGraphic(painter);
    drawGraphic(painter);
    if(getSelect())
    {
        painter->save();
        painter->setBrush(QBrush(Qt::green));
        painter->setPen(QPen(QBrush(Qt::black),1));
        painter->drawRect(-3,-3,6,6);
        painter->restore();
    }
    painter->restore();
}
void CaptionGraphic::drawGraphic(QPainter *painter)
{
    painter->setFont(_font);
    painter->drawText(- _size.width() / 2,- _size.height() / 2,
                      _size.width(),_size.height(),Qt::AlignCenter,_text);
    //painter->drawRect(- _size.width() / 2,- _size.height() / 2, _size.width(),_size.height());
}

void CaptionGraphic::prepareGraphic(QPainter *painter)
{
    switch(_direct)
    {
    case POS_UP:
    case POS_DOWN:
        painter->rotate(90);
        break;
    case POS_RIGHT:
    case POS_LEFT:
        break;
    }
    painter->setPen(this->getColor());
}
QRectF CaptionGraphic::boundingRect() const
{
    switch(_direct)
    {
    case POS_UP:
    case POS_DOWN:
        return QRectF(- _size.height() / 2,- _size.width() / 2,_size.height(),_size.width());
        break;
    case POS_RIGHT:
    case POS_LEFT:
        return  QRectF(- _size.width() / 2,- _size.height() / 2,_size.width(),_size.height());
        break;
    }
    return QRectF(- _size.width() / 2,- _size.height() / 2,_size.width(),_size.height());
}
