#include "graphicport.h"
#include "graphic.h"
GraphicPort::GraphicPort()
{
    _graphic = NULL;
    _id = 0;
}

void GraphicPort::setGraphic(Graphic* graphic)
{
    _graphic = graphic;
    if(_graphic)
    {
        _id = _graphic->getID();
    }
}

QString GraphicPort::getPosText(int pos,bool isTrans) const
{
    UNUSED(pos);
    if(isTrans)
    {
        switch(_selPos)
        {
        case Graphic::JOIN_HIGH:
            return "¸ß¶Ë";
        case Graphic::JOIN_MID:
            return "ÖÐ¶Ë";
        case Graphic::JOIN_LOW:
            return "µÍ¶Ë";
        }
    }
    else
    {
        switch(_selPos)
        {
        case Graphic::JOIN_BEGIN:
            return "Ê¼¶Ë";
        case Graphic::JOIN_END:
            return "Ä©¶Ë";
        }
    }
    return "Î´Öª";
}

QString GraphicPort::getSelText() const
{
    return getPosText(_selPos,_graphic->isTrans());
}
QString GraphicPort::getLinkText() const
{
    return getPosText(_linkPos,_graphic->isTrans());
}


QDataStream&	operator<< (QDataStream& dataStream,const GraphicPort& vector )
{
    dataStream << vector._selPos;
    dataStream << vector._linkPos;
    if(vector.getGraphic())
    {
        dataStream << vector.getGraphic()->getID();
    }
    else
    {
        dataStream << vector._id;
    }
    return dataStream;
}

QDataStream&	operator>> (QDataStream& dataStream,GraphicPort& vector )
{
    dataStream >> vector._selPos;
    dataStream >> vector._linkPos;
    dataStream >> vector._id;
    return dataStream;
}

//void GraphicPort::restoreJoin(QDataStream& dataStream)
//{
//    dataStream >> _selPos;
//    dataStream >> _linkPos;
//    dataStream >> _id;
//}

//void GraphicPort::saveJoin(QDataStream& dataStream) const
//{
//    dataStream << _selPos;
//    dataStream << _linkPos;
//    dataStream << _id;
//}
