#include "widthgraphiclineitem.h"

#include <QPainter>
#include "graphic.h"

#define LINE_WIDTH 4

WidthGraphicLineItem::WidthGraphicLineItem(qreal x1, qreal y1, qreal x2, qreal y2,QGraphicsItem * parent) :
    QGraphicsLineItem(x1,y1,x2,y2,parent)
{
    QColor color = QColor(0,127,0);

//    _clrMove = QColor(200,0,0);
//    _moveFlag = MOVE_NO;
//    _bBegin = true;
//    _bOnMove = false;

    _outType = Graphic::OUT_NONE;
    _pen.setColor(color);
    _pen.setWidth(1);
    _pen.setStyle(Qt::SolidLine);
    this->setPen(QPen(QBrush(color),LINE_WIDTH));
    //_lineWidth = 1;
    //_penStyle = Qt::SolidLine;
    _bFirst = false;
    _bSelect = false;
    //_bConsumer = false;
    this->setZValue(0.6);
    _bShowOut = false;
}

void WidthGraphicLineItem::setColor(const QColor& color)
{
    _pen.setColor(color);
     update();
}
void WidthGraphicLineItem::setLineType(int type)
{
    _type = type;
    switch(type)
    {
    case Graphic::LINE_EQUI:
        _pen.setStyle(Qt::DashDotLine);
        break;
    case Graphic::LINE_NOR:
        _pen.setStyle(Qt::SolidLine);
        break;
    case Graphic::LINE_VIR:
        _pen.setStyle(Qt::DashLine);
        break;
    }
    update();
}
void WidthGraphicLineItem::setPattern(int type,const QColor& color,bool bShowOut)
{
    _type = type;
    _bShowOut = bShowOut;
    switch(type)
    {
    case Graphic::LINE_EQUI:
    {
        QVector<qreal> dashes;
         qreal space = 2;
         dashes << 9 << space << 2 << space;
         _pen.setDashPattern(dashes);
    }
        break;
    case Graphic::LINE_NOR:
        _pen.setStyle(Qt::SolidLine);
        break;
    case Graphic::LINE_VIR:
        _pen.setStyle(Qt::DashLine);
        break;
    }
    _pen.setColor(color);
     update();
}

void WidthGraphicLineItem::setOutType(int outType)
{
    _outType = outType;
    update();
}


//void WidthGraphicLineItem::initMove(const QColor& clr,float len,bool bBegin)
//{
//    _moveFlag = MOVE_HALF;
//    _clrMove = clr;
//    _bBegin = bBegin;
//    _lenMove = len;
//    _bOnMove = false;
//    _curPos = 0;
//}
//void WidthGraphicLineItem::initMove(const QColor& clr,bool bBegin)
//{
//    _moveFlag = MOVE_FULL;
//    _clrMove = clr;
//    _bBegin = bBegin;
//    _lenMove = this->line().length();
//    _bOnMove = false;
//    _curPos = 0;
//}

//void WidthGraphicLineItem::beginMove(float curPos)
//{
//    switch(_moveFlag)
//    {
//    case MOVE_FULL:
//    case MOVE_HALF:
//        _curPos = curPos;
//        _bOnMove = true;
//        update();
//        return ;
//    }
//}

void WidthGraphicLineItem::addMode(LineFlow* flow)
{
    _flow.insert(flow);
}

bool WidthGraphicLineItem::delMove(LineFlow* flow)
{
    QSet<LineFlow*>::Iterator iterFlow = _flow.find(flow);
    if(iterFlow != _flow.end())
    {
        _flow.erase(iterFlow);
        return true;
    }
    return false;
}

//bool WidthGraphicLineItem::moveStep(float step)
//{
//    switch(_moveFlag)
//    {
//    case MOVE_FULL:
//    case MOVE_HALF:
//        _curPos += step;
//        if(_curPos >= _lenMove)
//        {
//            _curPos = 0;
//            _bOnMove = false;
//            update();
//            return false;
//        }
//        update();
//        return true;
//    }
//}

void WidthGraphicLineItem::drawMove(QPainter *painter)
{
    QLineF curLine = this->line();
    float lineLen = curLine.length();

    painter->save();
    for(QSet<LineFlow*>::Iterator iterFlow = _flow.begin();
        iterFlow != _flow.end(); ++iterFlow)
    {
        LineFlow* tmpFlow = *iterFlow;
        painter->setPen(tmpFlow->getMoveClr());
        bool bBegin = tmpFlow->isOrder();
        float posBegin = 0;
        float posEnd = curLine.length();
        if(!bBegin)
        {
            posBegin = curLine.length();
            posEnd = 0;
        }

        if(tmpFlow->isBegin(this))
        {
            posBegin = tmpFlow->getBeginPos();
        }
        if(tmpFlow->isEnd(this))
        {
            posEnd = tmpFlow->getEndPos();
        }

        QPointF beginPt = curLine.pointAt(posBegin / lineLen);
        QPointF endPt = curLine.pointAt(posEnd / lineLen);
        painter->drawLine(beginPt,endPt);

        if(tmpFlow->isCur(this))
        {
            float beginPercent = 0;
            float endPercent = 0;
            float curPos = tmpFlow->getCurPos();
            if(bBegin)
            {
                beginPercent = curPos / curLine.length();
                endPercent =   (curPos + 3) / curLine.length();
            }
            else
            {
                beginPercent =  curPos/ curLine.length();
                endPercent =   (curPos - 3) / curLine.length();
            }
            QPointF tmpPoint = curLine.pointAt(beginPercent);
            QPointF point0 = curLine.pointAt(endPercent);

            QLineF norLine(tmpPoint,point0);
            norLine = norLine.normalVector();
            float percnetAngle = 3 / norLine.length();


            QPointF point1 = norLine.pointAt(percnetAngle);
            QPointF point2 = tmpPoint* 2 - point1;
            painter->drawLine(point0,point1);
            painter->drawLine(point1,point2);
            painter->drawLine(point2,point0);
        }
    }
    painter->restore();;
}

void WidthGraphicLineItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    UNUSED(option);
    UNUSED(widget);

    QLineF line = this->line();
    painter->save();
    painter->setPen(_pen);
    painter->drawLine(this->line());

    drawMove(painter);

    if(_bShowOut)
    {
        if(Graphic::OUT_BEGIN == _outType)
        {
//            QLineF line = this->line();
            float percent = 10 / line.length();
            QPointF tmpPoint = line.pointAt(percent);
            QLineF norLine(tmpPoint,line.p1());
            norLine = norLine.normalVector();
            float percnetAngle = 3 / norLine.length();
            QPointF point0 = line.p1();
            QPointF point1 = norLine.pointAt(percnetAngle);
            QPointF point2 = tmpPoint* 2 - point1;
            painter->drawLine(point0,point1);
            painter->drawLine(point1,point2);
            painter->drawLine(point2,point0);
        }
        else if(Graphic::OUT_END == _outType)
        {
//            QLineF line = this->line();
            float percent = (line.length() - 10) / line.length();
            QPointF tmpPoint = line.pointAt(percent);
            QLineF norLine(tmpPoint,line.p2());
            norLine = norLine.normalVector();
            float percnetAngle = 3 / norLine.length();
            QPointF point0 = line.p2();
            QPointF point1 = norLine.pointAt(percnetAngle);
            QPointF point2 = tmpPoint* 2 - point1;
            painter->drawLine(point0,point1);
            painter->drawLine(point1,point2);
            painter->drawLine(point2,point0);
        }
    }
    painter->restore();
    if(_bSelect)
    {
        painter->save();
        painter->setBrush(QBrush(Qt::green));
        painter->setPen(QPen(QBrush(Qt::black),1));

//        QLineF line = this->line();
        QPointF first = line.p1();
        QPointF sec = line.p2();
        QPointF center = (first + sec) / 2;
        if(_bFirst)
        {
            painter->drawRect(first.x()-PORTSIZE,first.y()-PORTSIZE,PORTSIZE * 2,PORTSIZE * 2);
        }
        if(line.length() > MIN_LINE_LEN)
        {
            painter->drawRect(center.x()-PORTSIZE,center.y()-PORTSIZE,PORTSIZE * 2,PORTSIZE * 2);
        }

        painter->drawRect(sec.x()-PORTSIZE,sec.y()-PORTSIZE,PORTSIZE * 2,PORTSIZE * 2);
        painter->restore();
    }
}

//QRectF WidthGraphicLineItem::boundingRect() const
//{
//    QLineF lineWide = this->line();
//    QRectF rect(QPointF(lineWide.x1(),lineWide.y1()),QPointF(lineWide.x2(),lineWide.y2()));
//    rect.normalized();
//    rect.adjust(-LINE_WIDTH / 2,-LINE_WIDTH/2,LINE_WIDTH/2,LINE_WIDTH/2);
//    return rect;
//}
