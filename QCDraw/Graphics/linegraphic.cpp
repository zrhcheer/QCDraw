#include "linegraphic.h"
#include "graphicfactory.h"
#include "graphicexception.h"
#include "utilfunc.h"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "rapidxml/rapidxml_utils.hpp"

const QString LineGraphic::_devName = CodeConvertor::fromLocal("线路");

LineGraphic::LineGraphic()
{
    setType(Graphic::GRAPHIC_LINE);
    _bShowOut = true;
    _outType = Graphic::OUT_NONE;
    _lineType = Graphic::LINE_VIR;
    _idOutStation = 0;
    _tickBegin = NULL;
    _tickEnd = NULL;
    _tickMid = NULL;

    _captionGraphic = NULL;
    _portPoints.resize(2);
    _portPoints[0].setJoinType(GraphicPortPoint::JOIN_MUTI);
    this->setZValue(0.6);
    //setLineBreak(Graphic::JOIN_END);
//    _beginJoin = NULL;
//    _endJoin = NULL;
}

void LineGraphic::setColor(const QColor& clr)
{
    if(_color != clr)
    {
        Graphic::setColor(clr);
        for(QList<WidthGraphicLineItem*>::Iterator iterItem = _listLine.begin();
            iterItem != _listLine.end(); ++iterItem)
        {
            WidthGraphicLineItem* wideItem = *iterItem;
            if(wideItem)
            {
                wideItem->setColor(clr);
                wideItem->update();
            }
        }
    }
}

bool LineGraphic::querySideStation(SideStation& sideStation)
{
    sideStation.beginStation = dynamic_cast<StationGraphic*>(_beginLink.getLinkCenter());
    sideStation.endStation = dynamic_cast<StationGraphic*>(_endLink.getLinkCenter());
    return true;
}

void LineGraphic::setLineType(int lineType)
{
    _lineType = lineType;
    for(QList<WidthGraphicLineItem*>::Iterator iterItem = _listLine.begin();
        iterItem != _listLine.end(); ++iterItem)
    {
        WidthGraphicLineItem* wideItem = *iterItem;
        if(wideItem)
        {
            wideItem->setLineType(lineType);
        }
    }
}
void LineGraphic::setIsShowOut(bool bShowOut)
{
    WidthGraphicLineItem* tmpLine = NULL;
    _bShowOut = bShowOut;
    if(!_listLine.empty())
    {
        tmpLine = _listLine.front();
        tmpLine->setIsShowOut(bShowOut);
        tmpLine = _listLine.back();
        tmpLine->setIsShowOut(bShowOut);
    }
}

QVector<GraphicPort>& LineGraphic::getPorts()
{
    _port.clear();
    NodeLineLink* tmpNodeLink = _beginLink.getNodeLink();
    if(tmpNodeLink)
    {
        for(QList<GraphicPort> ::Iterator iterPort = tmpNodeLink->_link.begin();
            iterPort != tmpNodeLink->_link.end(); ++iterPort)
        {
            GraphicPort&  tmpPort = *iterPort;
            if(Graphic::GRAPHIC_LINE == tmpPort.getGraphic()->getType())
            {
                LineGraphic* tmpLine = dynamic_cast<LineGraphic*>(tmpPort.getGraphic());
                if(this == tmpLine)
                {
                    continue;
                }
            }
            GraphicPort curPort;
            curPort.setLinkPos(tmpPort.getLinkPos());
            curPort.setSelPos(Graphic::JOIN_BEGIN);
            curPort.setGraphic(tmpPort.getGraphic());
            _port.push_back(curPort);
        }
    }
    tmpNodeLink = _endLink.getNodeLink();
    if(tmpNodeLink)
    {
        for(QList<GraphicPort> ::Iterator iterPort = tmpNodeLink->_link.begin();
            iterPort != tmpNodeLink->_link.end(); ++iterPort)
        {
            GraphicPort&  tmpPort = *iterPort;
            if(Graphic::GRAPHIC_LINE == tmpPort.getGraphic()->getType())
            {
                LineGraphic* tmpLine = dynamic_cast<LineGraphic*>(tmpPort.getGraphic());
                if(this == tmpLine)
                {
                    continue;
                }
            }
            GraphicPort curPort;
            curPort.setLinkPos(tmpPort.getLinkPos());
            curPort.setSelPos(Graphic::JOIN_END);
            curPort.setGraphic(tmpPort.getGraphic());
            _port.push_back(curPort);
        }
    }
    return _port;
}

LineFlow* LineGraphic::addMove(const int& beginPer,const int& endPer,float step,const QColor& clr)
{
    LineFlow* flow = new LineFlow(_listLine);
    flow->initMove(beginPer,endPer,step,clr);
    _flowList.insert(flow);
    return flow;
}

bool LineGraphic::delMove(LineFlow* flow)
{
    QSet<LineFlow*>::Iterator iterFlow = _flowList.find(flow);
    if(iterFlow != _flowList.end())
    {
        LineFlow* tmpFlow = *iterFlow;
        tmpFlow->stopMove();
        delete tmpFlow;
        _flowList.erase(iterFlow);
    }
}

void LineGraphic::flushMove()
{
    for(QSet<LineFlow*>::Iterator iterFlow = _flowList.begin();
        iterFlow != _flowList.end(); ++iterFlow)
    {
        LineFlow* tmpFlow = *iterFlow;
        tmpFlow->flushMove();
    }
}

void LineGraphic::setOutType(int outType)
{
    WidthGraphicLineItem* tmpLine = NULL;
    _outType = outType;
    if(!_listLine.empty())
    {
        switch(outType)
        {
        case  OUT_BEGIN:
            tmpLine = _listLine.front();
            tmpLine->setOutType(outType);
            tmpLine = _listLine.back();
            tmpLine->setOutType(OUT_NONE);

            break;
        case  OUT_END:
            tmpLine = _listLine.front();
            tmpLine->setOutType(OUT_NONE);
            tmpLine = _listLine.back();
            tmpLine->setOutType(outType);
            break;
        case  OUT_NONE:
            tmpLine = _listLine.front();
            tmpLine->setOutType(outType);
            tmpLine = _listLine.back();
            tmpLine->setOutType(outType);
            _idOutStation = 0;
            break;
        }
    }
}

bool LineGraphic::isMagicPos(int pos)
{
    if(!this->isMagic())
    {
        return false;
    }
    switch (pos) {
    case Graphic::JOIN_BEGIN:
        return _beginLink.isMagicPos();
        break;
    case Graphic::JOIN_END:
         return _endLink.isMagicPos();
        break;
    }
    return true;
}

void LineGraphic::setPattern(const QColor& clr)
{
    Graphic::setColor(clr);
    //_bMagic = bMagic;
    for(QList<WidthGraphicLineItem*>::Iterator iterItem = _listLine.begin();
        iterItem != _listLine.end(); ++iterItem)
    {
        WidthGraphicLineItem* wideItem = *iterItem;
        if(wideItem)
        {
            wideItem->setPattern(_lineType,clr,_bShowOut);
        }
    }
}

void LineGraphic::flushTick()
{
    if(!_listLine.empty())
    {
        if(_tickBegin)
        {
            WidthGraphicLineItem* beginLine = _listLine.front();
            _tickBegin->setTickPos(beginLine->line(),true);
        }
        if(_tickEnd)
        {
            WidthGraphicLineItem* endLine = _listLine.back();
            _tickEnd->setTickPos(endLine->line(),false);
        }
    }
    if(_tickMid)
    {
        setMidTickPos(_tickMid);
    }
}

void LineGraphic::setMidTickPos(TickGraphic* tickMid)
{
    int lineSize =  _listLine.size();
    lineSize = lineSize / 2 + 1;
    QList<WidthGraphicLineItem*>::Iterator iterLine = _listLine.begin();
    WidthGraphicLineItem* curLine = NULL;
    for(int i = 0; i < lineSize && iterLine != _listLine.end();++iterLine,++i)
    {
        curLine = *iterLine;
    }
    if(curLine)
    {

        tickMid->setPosition(curLine->line().pointAt(0.5));
    }
}

void LineGraphic::setLineMarkMid(bool bMark)
{
    if(!bMark)
    {
        if(_tickMid)
        {
            this->removeFromGroup(_tickMid);
            delete _tickMid;
            _tickMid = NULL;
        }
    }
    else
    {
        if(!_tickMid)
        {
            _tickMid = new TickGraphic(this,TickGraphic::TICK_LIGHT);
        }
        setMidTickPos(_tickMid);
    }
}

void LineGraphic::setLineBreakColor(int pos,const QColor& clrCross)
{
    switch(pos)
    {
    case Graphic::JOIN_BEGIN:
        if(_tickBegin)
        {
            _tickBegin->setColor(clrCross);
        }
        break;
    case Graphic::JOIN_END:
        if(_tickEnd)
        {
            _tickEnd->setColor(clrCross);
        }
        break;
    }
}

void LineGraphic::setLineBreak(int pos,bool bBreaker)
{
    switch(pos)
    {
    case Graphic::JOIN_BEGIN:
        if(bBreaker)
        {
            if(!_tickBegin)
            {
                _tickBegin = new TickGraphic(this);
                this->addToGroup(_tickBegin);
            }
            if(!_listLine.empty())
            {
                WidthGraphicLineItem* front = _listLine.front();
                _tickBegin->setTickPos(front->line(),true);
            }
        }
        else
        {
            if(_tickBegin)
            {
                this->removeFromGroup(_tickBegin);
                delete _tickBegin;
                _tickBegin = NULL;
            }
        }

        //_beginLink.setIsBreak(bBreaker);
        break;
    case Graphic::JOIN_END:
        if(bBreaker)
        {
            if(!_tickEnd)
            {
                _tickEnd = new TickGraphic(this);
                this->addToGroup(_tickEnd);
            }
            if(!_listLine.empty())
            {
                WidthGraphicLineItem* back = _listLine.back();
                _tickEnd->setTickPos(back->line(),false);
            }
        }
        else
        {
            if(_tickEnd)
            {
                this->removeFromGroup(_tickEnd);
                delete _tickEnd;
                _tickEnd = NULL;
            }
        }
        //_endLink.setIsBreak(bBreaker);
        break;
    }
}

void LineGraphic::setCaption(const QString& caption)
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

    QGraphicsLineItem* begin = _listLine.front();
    QGraphicsLineItem* end = _listLine.back();
    if(!_captionGraphic)
    {
        _captionGraphic = new CaptionGraphic(this);
        //_captionGraphic->setPos(0, 0);
    }
    if(begin && end)
    {
        QLineF beginLine = begin->line();
        QLineF endLine = end->line();
        QLineF minLine(beginLine.p1(),endLine.p2());
        QPointF capPos = minLine.pointAt(0.5);
        if(fabs(minLine.p1().x() - minLine.p2().x()) > fabs(minLine.p1().y() - minLine.p2().y()))
        {
            _captionGraphic->setDirect(Graphic::POS_RIGHT);
            _captionGraphic->setPos(capPos.x(),capPos.y() - 14);
        }
        else
        {
            _captionGraphic->setDirect(Graphic::POS_UP);
            _captionGraphic->setPos(capPos.x() - 14,capPos.y());
        }

        _captionGraphic->setText(caption);
    }
}
GraphicKnee LineGraphic::queryKneeNode(const QPointF& point)
{
    GraphicKnee knee;
    QList<WidthGraphicLineItem*>::Iterator iterLine = _listLine.begin();
    int index = 0;
    if(iterLine != _listLine.end())
    {
        WidthGraphicLineItem* preLineGraphic = *iterLine;
        QLineF lineItem = preLineGraphic->line();
        QPointF tmpPoint = lineItem.p1();
//        QRectF rect(tmpPoint.x() - PORTSIZE,tmpPoint.y() - PORTSIZE,
//                    PORTSIZE * 2,PORTSIZE * 2);
        if(UtilFunc::manhattanLength(tmpPoint - point) < PORTSIZE)
        {
            //起点判定是不是都是线
            NodeLineLink* tmpNodeLink =  _beginLink.getNodeLink();
            if(tmpNodeLink)
            {
                QList<GraphicPort>& ports = tmpNodeLink->_link;
                for(QList<GraphicPort>::Iterator iterPort = ports.begin();
                    iterPort != ports.end(); ++iterPort)
                {
                    GraphicPort&  tmpPort = *iterPort;
                    Graphic* graphic = tmpPort.getGraphic();
                    if(graphic && Graphic::GRAPHIC_LINE != graphic->getType())
                    {
                        return knee;
                    }
                }
            }
            knee.setKneeType(GraphicKnee::KNEE_JOIN);
            knee.setKneeIndex(0);
            knee.setBeginLine(NULL);
            knee.setEndLine(preLineGraphic);
            return knee;
        }

        if(lineItem.length() > MIN_LINE_LEN)
        {
            tmpPoint = (tmpPoint + lineItem.p2()) / 2;
    //        rect.setLeft(tmpPoint.x() - PORTSIZE);
    //        rect.setTop(tmpPoint.y() - PORTSIZE);
            if(UtilFunc::manhattanLength(tmpPoint - point)< PORTSIZE)
            {
                knee.setKneeType(GraphicKnee::KNEE_MID);
                knee.setKneeIndex(0);
                knee.setBeginLine(preLineGraphic);
                knee.setEndLine(NULL);
                return knee;
            }
        }
        iterLine++;
        index ++;
        for(;iterLine != _listLine.end(); ++iterLine,++index)
        {
            WidthGraphicLineItem* lineGraphic = *iterLine;
            lineItem = lineGraphic->line();
            QPointF firPoint = lineItem.p1();
//            rect.setLeft(firPoint.x() - PORTSIZE);
//            rect.setTop(firPoint.y() - PORTSIZE);
            if(UtilFunc::manhattanLength(firPoint - point) < PORTSIZE)
            {
                knee.setKneeType(GraphicKnee::KNEE_JOIN);
                knee.setKneeIndex(index);
                knee.setBeginLine(preLineGraphic);
                knee.setEndLine(lineGraphic);
                return knee;
            }

            //QLineF lineItem = lineGraphic->line();
            QPointF firstLine = lineItem.p1();
            QPointF secLine = lineItem.p2();
            if(lineItem.length() > MIN_LINE_LEN)
            {
                tmpPoint = (firstLine + secLine) / 2;
    //            rect.setLeft(tmpPoint.x() - PORTSIZE);
    //            rect.setTop(tmpPoint.y() - PORTSIZE);
                if(UtilFunc::manhattanLength(tmpPoint - point) < PORTSIZE)
                {
                    knee.setKneeType(GraphicKnee::KNEE_MID);
                    knee.setKneeIndex(index);
                    knee.setBeginLine(lineGraphic);
                    knee.setEndLine(NULL);
                    return knee;
                }
            }
            preLineGraphic = lineGraphic;
        }
        //判定末点
        lineItem = preLineGraphic->line();
        QPointF secPoint = lineItem.p2();
//        rect.setLeft(secPoint.x() - PORTSIZE);
//        rect.setTop(secPoint.y() - PORTSIZE);
//        rect.setWidth(PORTSIZE * 2);
//        rect.setHeight(PORTSIZE * 2);
        if(UtilFunc::manhattanLength(secPoint - point) < PORTSIZE)
        {
            NodeLineLink* tmpNodeLink = _endLink.getNodeLink();
            if(tmpNodeLink)
            {
                QList<GraphicPort>& ports = tmpNodeLink->_link;
                for(QList<GraphicPort>::Iterator iterPort = ports.begin();
                    iterPort != ports.end(); ++iterPort)
                {
                    GraphicPort&  tmpPort = *iterPort;
                    Graphic* graphic = tmpPort.getGraphic();
                    if(graphic && Graphic::GRAPHIC_LINE != graphic->getType())
                    {
                        return knee;
                    }
                }
            }
            knee.setKneeType(GraphicKnee::KNEE_JOIN);
            knee.setKneeIndex(index);
            knee.setBeginLine(preLineGraphic);
            knee.setEndLine(NULL);
            return knee;
        }
    }
    return knee;
}

bool LineGraphic::delKnee(GraphicKnee& knee)
{
    if(GraphicKnee::KNEE_JOIN == knee.getKneeType())
    {
        if(knee.getBeginLine() && knee.getEndLine())
        {
            for(QList<WidthGraphicLineItem*>::Iterator iterLine = _listLine.begin();
                iterLine != _listLine.end(); ++iterLine)
            {
                WidthGraphicLineItem* tmpLine = *iterLine;
                if(tmpLine == knee.getBeginLine())
                {
                    iterLine++;
                    WidthGraphicLineItem* tmpSecLine = *iterLine;
                    if(tmpSecLine != knee.getEndLine())
                    {
                        return false;
                    }
                    iterLine = _listLine.erase(iterLine);
                    QLineF afterLine = tmpSecLine->line();
                    QLineF preLine = tmpLine->line();
                    preLine.setP2(afterLine.p2());
                    tmpLine->setLine(preLine);
                    this->removeFromGroup(tmpSecLine);
                    delete tmpSecLine;
                    flushMove();
//                    if(iterLine == _listLine.end())
//                    {
//                        tmpLine->set
//                    }
                    return true;
                }
            }
        }
    }
    return false;
}

bool LineGraphic::delLink(int selPos,Graphic* graphic)
{
    NodeLineLink* tmpLink = NULL;
    bool bDeal = false;
    switch(selPos)
    {
    case Graphic::JOIN_BEGIN:
        tmpLink = _beginLink.getNodeLink();
        if(tmpLink)
        {
            if(Graphic::GRAPHIC_LINE == graphic->getType())
            {
                _beginLink.clearLink();
                bDeal = true;
            }
            else
            {
                for(QList<GraphicPort> ::Iterator iterLink = tmpLink->_link.begin();
                    iterLink != tmpLink->_link.end();)
                {
                    GraphicPort& port = *iterLink;
                    if( graphic == port.getGraphic())
                    {
                        iterLink = tmpLink->_link.erase(iterLink);
                    }
                    else
                    {
                         ++iterLink;
                    }
                }
                if( tmpLink->_link.size() <= 1)
                {
                    _beginLink.clearLink();
                }
            }
        }
        break;
    case Graphic::JOIN_END:
        tmpLink = _endLink.getNodeLink();
        if(tmpLink)
        {
            if(Graphic::GRAPHIC_LINE == graphic->getType())
            {
                _endLink.clearLink();
                bDeal = true;
            }
            else
            {
                for(QList<GraphicPort> ::Iterator iterLink = tmpLink->_link.begin();
                    iterLink != tmpLink->_link.end();)
                {
                    GraphicPort& port = *iterLink;
                    if(graphic == port.getGraphic())
                    {
                        iterLink = tmpLink->_link.erase(iterLink);
                    }
                    else
                    {
                         ++iterLink;
                    }
                }
                if( tmpLink->_link.size() <= 1)
                {
                    _endLink.clearLink();
                }
            }
        }
        break;
    }
    return true;
}

bool LineGraphic::delJoin(int selPos)
{
    NodeLineLink* tmpLink = NULL;
    switch(selPos)
    {
    case Graphic::JOIN_BEGIN:
        tmpLink = _beginLink.getNodeLink();
        if(tmpLink)
        {
            for(QList<GraphicPort>::Iterator iterPort = tmpLink->_link.begin();
                iterPort != tmpLink->_link.end(); ++iterPort)
            {
                GraphicPort& tmpGraphic = *iterPort;
                Graphic* graphic = tmpGraphic.getGraphic();
                if(Graphic::GRAPHIC_LINE == graphic->getType())
                {
                    LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>(graphic);
                    if(this != lineGraphic)
                    {
                        lineGraphic->delLink(tmpGraphic.getLinkPos(),this);
                    }
                }
                else
                {
                    graphic->delLink(tmpGraphic.getLinkPos(),this);
                }
            }
        }
        _beginLink.clearLink();
        break;
    case Graphic::JOIN_END:
        tmpLink = _endLink.getNodeLink();
        if(tmpLink)
        {
            for(QList<GraphicPort>::Iterator iterPort = tmpLink->_link.begin();
                iterPort != tmpLink->_link.end(); ++iterPort)
            {
                GraphicPort& tmpGraphic = *iterPort;
                Graphic* graphic = tmpGraphic.getGraphic();
                if(Graphic::GRAPHIC_LINE == graphic->getType())
                {
                    LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>(graphic);
                    if(this != lineGraphic)
                    {
                        lineGraphic->delLink(tmpGraphic.getLinkPos(),this);
                    }
                }
                else
                {
                    graphic->delLink(tmpGraphic.getLinkPos(),this);
                }
            }
        }
        _endLink.clearLink();
        break;
    }
    return true;
}
bool LineGraphic::movePostion(const QPointF& pointMove,set<LineMove>& lineMove)
{
    QList<WidthGraphicLineItem*>::Iterator iterLine = _listLine.begin();
    WidthGraphicLineItem* befGraphicLineItem = NULL;
    WidthGraphicLineItem* tmpGraphicLineItem = *iterLine++;
    NodeLineLink* nodeLinkBegin = _beginLink.getNodeLink();
//    bool bLink = false;
    bool bMove = true;
    Graphic* selGraphic = dynamic_cast<Graphic*>(this);
    if(nodeLinkBegin)
    {
        for(QList<GraphicPort>::Iterator iterPort = nodeLinkBegin->_link.begin();
            iterPort != nodeLinkBegin->_link.end(); ++iterPort)
        {
            GraphicPort& tmpPort = *iterPort;
            Graphic* graphic = tmpPort.getGraphic();
//            if(Graphic::GRAPHIC_LINE != graphic->getType())
//            {
//                bLink = true;
//            }
            if(selGraphic != graphic)
            {
                set<LineMove>::const_iterator iterMove = lineMove.find(LineMove(graphic,tmpPort.getLinkPos()));
                if(iterMove == lineMove.end())
                {
                    bMove = false;
                }
            }
        }
        if(bMove)
        {
            for(QList<GraphicPort>::Iterator iterPort = nodeLinkBegin->_link.begin();
                iterPort != nodeLinkBegin->_link.end(); ++iterPort)
            {
                GraphicPort& tmpPort = *iterPort;
                Graphic* graphic = tmpPort.getGraphic();
                if(Graphic::GRAPHIC_LINE == graphic->getType())
                {
                    LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>(graphic);
                    lineGraphic->moveJointPoint(tmpPort.getLinkPos(),pointMove);
                }
            }
        }
    }
    lineMove.insert(LineMove(selGraphic,Graphic::JOIN_BEGIN));
//    if(bMove)
//    {
//        QLineF line = tmpGraphicLineItem->line();
//        line.setP1(line.p1() + pointMove);
//        tmpGraphicLineItem->setLine(line);
//    }

    befGraphicLineItem = tmpGraphicLineItem;
    for(;iterLine != _listLine.end();++iterLine)
    {
        WidthGraphicLineItem* tmpGraphicLineItem = *iterLine;
        QLineF befLine = befGraphicLineItem->line();
        befLine.setP2(befLine.p2() + pointMove);
        befGraphicLineItem->setLine(befLine);
        befLine = tmpGraphicLineItem->line();
        befLine.setP1(befLine.p1() + pointMove);
        tmpGraphicLineItem->setLine(befLine);
        befGraphicLineItem = tmpGraphicLineItem;
    }
    NodeLineLink* nodeLinkEnd = _endLink.getNodeLink();
    bMove = true;
    if(nodeLinkEnd)
    {
        for(QList<GraphicPort>::Iterator iterPort = nodeLinkEnd->_link.begin();
            iterPort != nodeLinkEnd->_link.end(); ++iterPort)
        {
            GraphicPort& tmpPort = *iterPort;
            Graphic* graphic = tmpPort.getGraphic();
//            if(Graphic::GRAPHIC_LINE != graphic->getType())
//            {
//                bLink = true;
//            }

            if(selGraphic != graphic)
            {
                set<LineMove>::const_iterator iterMove = lineMove.find(LineMove(graphic,tmpPort.getLinkPos()));
                if(iterMove == lineMove.end())
                {
                    bMove = false;
                }
            }
        }
        if(bMove)
        {
            for(QList<GraphicPort>::Iterator iterPort = nodeLinkEnd->_link.begin();
                iterPort != nodeLinkEnd->_link.end(); ++iterPort)
            {
                GraphicPort& tmpPort = *iterPort;
                Graphic* graphic = tmpPort.getGraphic();
                if(Graphic::GRAPHIC_LINE == graphic->getType())
                {
                    LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>(graphic);
                    lineGraphic->moveJointPoint(tmpPort.getLinkPos(),pointMove);
                }
            }
        }
    }
    lineMove.insert(LineMove(selGraphic,Graphic::JOIN_END));
    flushMove();
    return true;
}

bool LineGraphic::moveKnee(GraphicKnee& knee,const QPointF& point)
{
    switch(knee.getKneeType())
    {
    case GraphicKnee::KNEE_JOIN:
    {
        WidthGraphicLineItem* firsLine = knee.getBeginLine();
        WidthGraphicLineItem* secLine = knee.getEndLine();
        if(!firsLine)
        {
            NodeLineLink* tmpNodeLink = _beginLink.getNodeLink();
            if(tmpNodeLink)
            {
                QList<GraphicPort>& ports = tmpNodeLink->_link;
                for(QList<GraphicPort>::Iterator iterPort = ports.begin();
                    iterPort != ports.end(); ++iterPort)
                {
                    GraphicPort& tmpPort = *iterPort;
                    Graphic* graphic = tmpPort.getGraphic();
                    if(graphic)
                    {
                        if(Graphic::GRAPHIC_LINE == graphic->getType())
                        {
                            LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>(graphic);
                            lineGraphic->setJointPoint(tmpPort.getLinkPos(),point);
                        }
                        else
                        {
                            assert(false);
                        }
                    }
                }
            }
            else
            {
                this->setJointPoint(Graphic::JOIN_BEGIN,point);
            }
            if(_tickBegin)
            {
                if(!_listLine.empty())
                {
                    WidthGraphicLineItem* beginLine = _listLine.front();
                    _tickBegin->setTickPos(beginLine->line(),true);
                }
            }
            if(_tickMid)
            {
                setMidTickPos(_tickMid);
            }
            flushMove();
            return true;
        }
        else if(!secLine)
        {
            NodeLineLink* tmpNodeLink = _endLink.getNodeLink();
            if(tmpNodeLink)
            {
                QList<GraphicPort>& ports = tmpNodeLink->_link;
                for(QList<GraphicPort>::Iterator iterPort = ports.begin();
                    iterPort != ports.end(); ++iterPort)
                {
                    GraphicPort& tmpPort = *iterPort;
                    Graphic* graphic = tmpPort.getGraphic();
                    if(graphic)
                    {
                        if(Graphic::GRAPHIC_LINE == graphic->getType())
                        {
                            LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>(graphic);
                            lineGraphic->setJointPoint(tmpPort.getLinkPos(),point);
                        }
                        else
                        {
                            assert(false);
                        }
                    }
                }
            }
            else
            {
                this->setJointPoint(Graphic::JOIN_END,point);
            }

            if(_tickEnd)
            {
                if(!_listLine.empty())
                {
                    WidthGraphicLineItem* endLine = _listLine.back();
                    _tickEnd->setTickPos(endLine->line(),false);
                }
            }
            if(_tickMid)
            {
                setMidTickPos(_tickMid);
            }
            flushMove();
            return true;
        }
        else
        {
            QLineF line = firsLine->line();
            line.setP2(point);
            firsLine->setLine(line);
            Graphic* stationGraphic = _beginLink.getLinkCenter();
            if(stationGraphic)
            {
                this->setJointPointDis(Graphic::JOIN_BEGIN,stationGraphic->getPosition(),
                                       stationGraphic->getSize().width() / 2,false);
            }
            line = secLine->line();
            line.setP1(point);
            secLine->setLine(line);
            stationGraphic = _endLink.getLinkCenter();
            if(stationGraphic)
            {
                this->setJointPointDis(Graphic::JOIN_END,stationGraphic->getPosition(),
                                       stationGraphic->getSize().width() / 2,false);
            }

            flushMove();
            flushTick();
//            if(!_listLine.empty())
//            {
//                if(_tickBegin)
//                {
//                    WidthGraphicLineItem* beginLine = _listLine.front();
//                    _tickBegin->setTickPos(beginLine,true);
//                }
//                if(_tickEnd)
//                {
//                    WidthGraphicLineItem* endLine = _listLine.back();
//                    _tickEnd->setTickPos(endLine,false);
//                }
//            }
//            if(_tickMid)
//            {
//                setMidTickPos(_tickMid);
//            }
        }
    }
        break;
    case GraphicKnee::KNEE_MID:
    {
        //是中点时新增一线
        WidthGraphicLineItem* firsLine = knee.getBeginLine();
        QLineF line = firsLine->line();
        QPointF secPoint = line.p2();
        line.setP2(point);
        firsLine->setOutType(Graphic::OUT_NONE);
        WidthGraphicLineItem* newLine = new WidthGraphicLineItem(point.x(),point.y(),
                                                                 secPoint.x(),secPoint.y(),this);
        newLine->setIsSelect(this->getSelect());
        newLine->setPattern(_lineType,this->getColor(),_bShowOut);
        knee.setEndLine(newLine);
        knee.setKneeType(GraphicKnee::KNEE_JOIN);
        //将新加的线加入列表
        for(QList<WidthGraphicLineItem*>::Iterator iterLine =  _listLine.begin();
            iterLine != _listLine.end(); ++iterLine)
        {
            WidthGraphicLineItem* tmpLine = *iterLine;
            if(tmpLine == firsLine)
            {
                iterLine++;
                _listLine.insert(iterLine,newLine);
                break;
            }
        }
        if(Graphic::OUT_END == _outType)
        {
            WidthGraphicLineItem* backLineItem = _listLine.back();
            backLineItem->setOutType(_outType);
        }
        else if(Graphic::OUT_BEGIN == _outType)
        {
            WidthGraphicLineItem* frontLineItem = _listLine.front();
            frontLineItem->setOutType(_outType);
        }
        flushMove();
        flushTick();
//        if(!_listLine.empty())
//        {
//            if(_tickBegin)
//            {
//                WidthGraphicLineItem* beginLine = _listLine.front();
//                _tickBegin->setTickPos(beginLine,true);
//            }
//            if(_tickEnd)
//            {
//                WidthGraphicLineItem* endLine = _listLine.back();
//                _tickEnd->setTickPos(endLine,false);
//            }
//        }
//        if(_tickMid)
//        {
//            setMidTickPos(_tickMid);
//        }
    }
        break;
    }
    return true;
}

void LineGraphic::hidePortAnchor(int selPos)
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

void LineGraphic::hidePortAnchor()
{
    for(int i = 0; i < _portPoints.size(); ++i)
    {
        _portPoints[i].hideAnchor();
    }
}

void LineGraphic::showPortAnchor(int selPos)
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

set<int> LineGraphic::queryUnMountPos()
{
    set<int> tmpJoin;
    if(_beginLink.getNodeLink())
    {
        NodeLineLink* tmpNodeLink = _beginLink.getNodeLink();
        if(tmpNodeLink->_link.size() <= 1)
        {
            tmpJoin.insert(0);
        }
    }
    else
    {
        tmpJoin.insert(0);
    }
    if(_endLink.getNodeLink())
    {
        NodeLineLink* tmpNodeLink = _beginLink.getNodeLink();
        if(tmpNodeLink->_link.size() <= 1)
        {
            tmpJoin.insert(1);
        }
    }
    else
    {
        tmpJoin.insert(1);
    }
    return tmpJoin;
}

bool LineGraphic::isJointed(int selPos)
{
    switch(selPos)
    {
    case Graphic::JOIN_BEGIN:
        if(_beginLink.getNodeLink() && _beginLink.getNodeLink()->_link.size() >= 2)
        {
            return true;
        }
        break;
    case Graphic::JOIN_END:
        if(_endLink.getNodeLink() && _endLink.getNodeLink()->_link.size() >= 2)
        {
            return true;
        }
        break;
    }
    return false;
}

QVector<GraphicPortPoint>&  LineGraphic::getJoinPortPoint()
{
    if(_listLine.empty())
    {
        assert(false);
    }
    else
    {
        WidthGraphicLineItem* front = _listLine.front();
        QLineF tmpLine = front->line();
        _portPoints[0].setJoinPoint(tmpLine.p1());

        WidthGraphicLineItem* back = _listLine.back();
        tmpLine = back->line();
        _portPoints[1].setJoinPoint(tmpLine.p2());
    }
    return _portPoints;
}
void LineGraphic::initLink(map<ulong64,Graphic*>& allElement)
{
    UNUSED(allElement);
    //    for(QVector<GraphicPort>::Iterator iterPort = _port.begin();
    //        iterPort != _port.end(); ++iterPort)
    //    {
    //        GraphicPort& tmpPort = *iterPort;
    //        map<ulong64,Graphic*>::iterator iterGraphic = allElement.find(tmpPort.getID());
    //        if(iterGraphic != allElement.end())
    //        {
    //            Graphic* tmpGraphic = iterGraphic->second;
    //            tmpPort.setGraphic(tmpGraphic);
    //        }
    //    }
}

void LineGraphic::loadXML(rapidxml::xml_node<char> *node)
{
    string color;
    string points;
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
        else  if(0 == strcmp("lineType",attr->name()))
        {
            _lineType = atoi(attr->value());
        }
        else  if(0 == strcmp("bShowOut",attr->name()))
        {
            _bShowOut = atoi(attr->value());
        }
        else  if(0 == strcmp("outType",attr->name()))
        {
            _outType = atoi(attr->value());
        }
        else  if(0 == strcmp("idOutStation",attr->name()))
        {
            _idOutStation = atoll(attr->value());
        }
        else  if(0 == strcmp("num",attr->name()))
        {
            int num = atoi(attr->value());
            if(num > 0)
            {
                _captionGraphic = new CaptionGraphic(this);
                _captionGraphic->loadXML(node);
            }
        }
        else if(0 == strcmp("points",attr->name()))
        {
            points = attr->value();
        }
    }

    QVector<QPointF> linePoint;
    QPointF pointF;
    for(int i = 0;i < points.size();++i)
    {
        size_t pos = points.find(",",i);
        string x = points.substr(i,pos - i);
        size_t pos1 = points.find(";",pos + 1);
        string y = points.substr(pos + 1,pos1 - pos - 1);
        pointF.setX(atof(x.c_str()));
        pointF.setY(atof(y.c_str()));
        linePoint.push_back(pointF);
        i = pos1;
    }
    if(linePoint.size() < 2)
    {
        string  strError = "线路:" + _name.toStdString() + "连线必需大于一";
        throw GraphicException(strError.c_str());
    }
    this->setLinePoint(linePoint);
}

void LineGraphic::restoreGraphic(QDataStream& dataStream)
{
    dataStream >> _id;
    dataStream >> _name;
    dataStream >> _volLevelId;
    dataStream >> _color;
    dataStream >> _lineType;
    dataStream >> _bShowOut;
    dataStream >> _outType;
    dataStream >> _idOutStation;

    QVector<QPointF> linePoint;
    dataStream >> linePoint;
    if(linePoint.size() < 2)
    {
        string  strError = "线路:" + _name.toStdString() + "连线必需大于一";
        throw GraphicException(strError.c_str());
    }
    this->setLinePoint(linePoint);
    int numText;
    dataStream >> numText;
    if(numText > 0)
    {
        _captionGraphic = new CaptionGraphic(this);
        _captionGraphic->restoreGraphic(dataStream);
    }
    //连接分开存
//    _beginLink.restoreGraphic(dataStream);
//    _endLink.restoreGraphic(dataStream);
}

void LineGraphic::saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic)
{
    int color_r,color_g,color_b;
    _color.getRgb(&color_r,&color_g,&color_b);
    int bShowOut;
    if(_bShowOut)
    {
        bShowOut = 1;
    }
    else
    {
        bShowOut = 0;
    }
    char* id = doc.allocate_string(QString::number(_id).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("id",id));

    char* name = doc.allocate_string(_name.toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("name",name));

    char* volLevelId = doc.allocate_string(QString::number(_volLevelId).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("volLevelId",volLevelId));

    string colorStr;
    colorStr += QString::number(color_r).toStdString() + ","
            + QString::number(color_g).toStdString() + ","
            + QString::number(color_b).toStdString() + ";";
    char* color = doc.allocate_string(colorStr.c_str());
    node->append_attribute(doc.allocate_attribute("color",color));

    char* type = doc.allocate_string(QString::number(_type).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("type",type));

    char* lineType = doc.allocate_string(QString::number(_lineType).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("lineType",lineType));

    char* outType = doc.allocate_string(QString::number(_outType).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("outType",outType));

    char* bShowOutchar = doc.allocate_string(QString::number(bShowOut).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("bShowOut",bShowOutchar));

    char* idOutStation = doc.allocate_string(QString::number(_idOutStation).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("idOutStation",idOutStation));

    if(_captionGraphic)
    {
        node->append_attribute(doc.allocate_attribute("num","1"));
        _captionGraphic->saveXML(node,doc,graphic);
    }
    else
    {
        node->append_attribute(doc.allocate_attribute("num","0"));
    }

    QVector<QPointF> vecPoint;
    this->getLinePoint(vecPoint);
    QString point;
    for(int i = 0;i < vecPoint.size();++i)
    {
        QPointF poinF = vecPoint[i];
        point += QString::number(poinF.x()) + "," +QString::number(poinF.y()) + ";";
    }
    char* points = doc.allocate_string(point.toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("points",points));

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

void LineGraphic::saveGraphic(QDataStream& dataStream) const
{
    dataStream << _type;
    dataStream << _id;
    dataStream << _name;
    dataStream << _volLevelId;
    dataStream << _color;
    dataStream << _lineType;
    dataStream << _bShowOut;
    dataStream << _outType;
    dataStream << _idOutStation;

    QVector<QPointF> vecPoint;
    this->getLinePoint(vecPoint);
    dataStream << vecPoint;
    if(_captionGraphic)
    {
        dataStream << int(1);
        _captionGraphic->saveGraphic(dataStream);
    }
    else
    {
        dataStream << int(0);
    }
    //连接分开存
//    _beginLink.saveGraphic(dataStream);
//    _endLink.saveGraphic(dataStream);
}
//QPainterPath LineGraphic::shape () const
//{
//    QPainterPath path;
//    QList<WidthGraphicLineItem*>::ConstIterator iterItem = _listLine.begin();
//    for(;iterItem != _listLine.end();++iterItem)
//    {
//        const WidthGraphicLineItem* beginItem = *iterItem;
//        path.addRect(beginItem->boundingRect());
//    }
//    return path;
//}

//QRectF LineGraphic::boundingRect() const
//{
//    QPainterPath path;
//    QList<WidthGraphicLineItem*>::ConstIterator iterItem = _listLine.begin();
//    for(;iterItem != _listLine.end();++iterItem)
//    {
//        const WidthGraphicLineItem* beginItem = *iterItem;
//        path.addRect(beginItem->boundingRect());
//    }
//    return path.boundingRect();
//}
void LineGraphic::updateShape()
{
    QList<WidthGraphicLineItem*>::Iterator iterItem = _listLine.begin();
    for(;iterItem != _listLine.end();++iterItem)
    {
        WidthGraphicLineItem* beginItem = *iterItem;
        beginItem->update();
    }
    this->update();
}

void LineGraphic::ensureVisible()
{
    QList<WidthGraphicLineItem*>::Iterator iterItem = _listLine.begin();
    for(;iterItem != _listLine.end();++iterItem)
    {
        WidthGraphicLineItem* beginItem = *iterItem;
        beginItem->ensureVisible();
    }
}

QPointF  LineGraphic::getPortPos(int pos)
{
    QGraphicsLineItem* front = _listLine.front();
    QLineF frontLine = front->line();
    QGraphicsLineItem* back = _listLine.back();
    QLineF backLine = back->line();
    switch(pos)
    {
    case Graphic::JOIN_BEGIN:
        return frontLine.p1();
        break;
    case Graphic::JOIN_END:
        return backLine.p2();
        break;
    }
    assert(false);
    return QPointF();
}

void LineGraphic::setSelect(const bool& select)
{
    if(_bSelected != select)
    {
        Graphic::setSelect(select);
        QList<WidthGraphicLineItem*>::Iterator iterItem = _listLine.begin();
        for(;iterItem != _listLine.end();++iterItem)
        {
            WidthGraphicLineItem* beginItem = *iterItem;
            beginItem->setIsSelect(select);
            beginItem->update();
        }
        this->update();
    }
}

bool LineGraphic::setStationGraphic(GraphicBase* beginStation,GraphicBase* endStation)
{
    if(beginStation && beginStation)
    {
        _beginLink.setLineLinkSel(this,Graphic::JOIN_BEGIN);
        _endLink.setLineLinkSel(this,Graphic::JOIN_END);
        _beginLink.setLineLink(beginStation,Graphic::JOIN_BEGIN);
        _endLink.setLineLink(endStation,Graphic::JOIN_BEGIN);


        QPointF begin = beginStation->pos();
        QPointF end = endStation->pos();
        float lenBegin = beginStation->getSize().width() / 2;
        float lenEnd = endStation->getSize().width() / 2;

        if(_listLine.size() > 0)
        {
            WidthGraphicLineItem* front = _listLine.front();
            QLineF frontLine = front->line();
            frontLine.setP1(begin);
            float beginPer = lenBegin / frontLine.length();
            QPointF beginPt = frontLine.pointAt(beginPer);
            frontLine.setP1(beginPt);
            front->setLine(frontLine);

            WidthGraphicLineItem* back = _listLine.back();
            frontLine = back->line();
            frontLine.setP2(end);
            float endPer = 1 - lenEnd / frontLine.length();
            QPointF endPt = frontLine.pointAt(endPer);
            frontLine.setP2(endPt);
            back->setLine(frontLine);

            beginStation->setLine(this,Graphic::JOIN_BEGIN);
            endStation->setLine(this,Graphic::JOIN_END);
        }
        else
        {

            QLineF line(begin,end);
            float beginPer = lenBegin / line.length();
            float endPer = 1 - lenEnd / line.length();
            QPointF beginPt = line.pointAt(beginPer);
            QPointF endPt = line.pointAt(endPer);
            WidthGraphicLineItem* curLine = new WidthGraphicLineItem(beginPt.x(),beginPt.y(),
                                                               endPt.x() , endPt.y(),this);
            curLine->setIsFirst(true);
            curLine->setPattern(_lineType,getColor(),_bShowOut);
            curLine->setOutType(_outType);
            beginStation->setLine(this,Graphic::JOIN_BEGIN);
            endStation->setLine(this,Graphic::JOIN_END);
            _listLine.push_back(curLine);
            //this->addToGroup(curLine);
        }
        return true;
    }
    return false;
}
bool LineGraphic::linkGraphic(int selPos,Graphic* graphic,int linkPos)
{
    switch(graphic->getType())
    {
    case Graphic::GRAPHIC_STATION:
    {
        StationGraphic* stationGraphic = dynamic_cast<StationGraphic*>(graphic);
        NodeLink& nodeLink = this->getNodeLink(selPos);
        nodeLink.setLineLinkSel(this,selPos);
        nodeLink.setLineLink(graphic,linkPos);
        QPointF ptStation = stationGraphic->pos();
        float lenBegin = stationGraphic->getSize().width() / 2;
        if(_listLine.size() > 0)
        {
            if(Graphic::JOIN_BEGIN == selPos)
            {
                WidthGraphicLineItem* front = _listLine.front();
                QLineF frontLine = front->line();
                frontLine.setP1(ptStation);
                float beginPer = lenBegin / frontLine.length();
                QPointF beginPt = frontLine.pointAt(beginPer);
                frontLine.setP1(beginPt);
                front->setLine(frontLine);
            }
            else if(Graphic::JOIN_END == selPos)
            {
                WidthGraphicLineItem* back = _listLine.back();
                QLineF backLine = back->line();
                backLine.setP1(ptStation);
                float endPer = 1 - lenBegin / backLine.length();
                QPointF endPt = backLine.pointAt(endPer);
                backLine.setP1(endPt);
                back->setLine(backLine);
            }
        }
        else
        {
            QLineF line(ptStation,QPointF(ptStation.x() + lenBegin + 20,ptStation.y() + lenBegin + 20));//默誰离开点
            float beginPer = lenBegin / line.length();
            float endPer = 1 - lenBegin / line.length();
            QPointF beginPt = line.pointAt(beginPer);
            QPointF endPt = line.pointAt(endPer);
            WidthGraphicLineItem* curLine = new WidthGraphicLineItem(beginPt.x(),beginPt.y(),
                                                               endPt.x() , endPt.y(),this);
            curLine->setIsFirst(true);
            curLine->setOutType(_outType);
            curLine->setPattern(_lineType,getColor(),_bShowOut);
            stationGraphic->setLine(this,selPos);
            _listLine.push_back(curLine);
        }
    }
        break;
    case Graphic::GRAPHIC_LINE:
    {
        LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>(graphic);
        setLineGraphicLink(selPos,lineGraphic,linkPos);
    }
        break;
    case Graphic::GRAPHIC_BUS:
    {
        BusGraphic* bus = dynamic_cast<BusGraphic*>(graphic);
        setBusGraphicLink(selPos,bus);
    }
        break;
    default:
        if(graphic->getType() < Graphic::GRAPHIC_MAX)
        {
            GraphicBase* eleGraphic = dynamic_cast<GraphicBase*>(graphic);
            this->setGraphicLink(selPos,eleGraphic,linkPos);
        }
    }
    return true;
}

bool LineGraphic::setBeginGraphic(GraphicBase* beginJoin,int pos)
{
    if(beginJoin)
    {
        QPointF pointPort = beginJoin->getPortPos(pos) + beginJoin->pos();
        _beginLink.setLineLinkSel(this,Graphic::JOIN_BEGIN);
        _beginLink.setLineLink(beginJoin,pos);
        beginJoin->setPortGraphic(pos,this,Graphic::JOIN_BEGIN);
        if(_listLine.size() > 0)
        {
            WidthGraphicLineItem* front = _listLine.front();
            QLineF frontLine = front->line();
            frontLine.setP1(pointPort);
            front->setLine(frontLine);
        }
        else
        {
            WidthGraphicLineItem* curLine = new WidthGraphicLineItem(pointPort.x(),pointPort.y(),
                                                               pointPort.x() + 40, pointPort.y() + 40,this);
            curLine->setIsFirst(true);
            curLine->setOutType(_outType);
            curLine->setPattern(_lineType,getColor(),_bShowOut);
            _listLine.push_back(curLine);
            //this->addToGroup(curLine);
        }
        return true;
    }
    return false;
}

bool LineGraphic::setEndGraphic(GraphicBase* endJoin,int pos)
{
    if(endJoin)
    {
        QPointF pointPort = endJoin->getPortPos(pos) + endJoin->pos();
        _endLink.setLineLinkSel(this,Graphic::JOIN_END);
        _endLink.setLineLink(endJoin,pos);
        endJoin->setPortGraphic(pos,this,Graphic::JOIN_END);
        if(_listLine.size() > 0)
        {
            QGraphicsLineItem* back = _listLine.back();
            QLineF backLine = back->line();
            backLine.setP2(pointPort);
            back->setLine(backLine);
        }
        else
        {
            WidthGraphicLineItem* curLine = new WidthGraphicLineItem(pointPort.x() - 40,pointPort.y() -40,
                                                               pointPort.x() , pointPort.y() ,this);
            curLine->setIsFirst(true);
            curLine->setOutType(_outType);
            curLine->setPattern(_lineType,getColor(),_bShowOut);
            _listLine.push_back(curLine);
        }
        return true;
    }
    return false;
}
void LineGraphic::unlinkGraphic()
{
    //删除首端连接
    NodeLineLink* beginLink = _beginLink.getNodeLink();
    if(beginLink)
    {
        for(QList<GraphicPort>::iterator iterLink = beginLink->_link.begin();
            iterLink != beginLink->_link.end();)
        {
            GraphicPort& tmpPort = *iterLink;
            Graphic* graphic = tmpPort.getGraphic();
            if(graphic == this)
            {
                iterLink = beginLink->_link.erase(iterLink);
                continue;
            }
            else if(Graphic::GRAPHIC_LINE != graphic->getType())
            {
                graphic->delLink(tmpPort.getLinkPos(),this);
            }
            iterLink++;
        }
    }
    //删除末端连接
    NodeLineLink* endLink = _endLink.getNodeLink();
    if(endLink)
    {
        for(QList<GraphicPort>::iterator iterLink = endLink->_link.begin();
            iterLink != endLink->_link.end();)
        {
            GraphicPort& tmpPort = *iterLink;
             Graphic* graphic = tmpPort.getGraphic();
            if(graphic == this)
            {
                iterLink = endLink->_link.erase(iterLink);
                continue;
            }
            else if(Graphic::GRAPHIC_LINE != graphic->getType())
            {
                graphic->delLink(tmpPort.getLinkPos(),this);
            }
            iterLink++;
        }
    }
}


bool LineGraphic::setBeginBusGraphic(BusGraphic* busGraphic)
{
    if(busGraphic)
    {
        busGraphic->setJoinGraphic(this,Graphic::JOIN_BEGIN);
        QPointF btPoint = this->getBeginPoint();
        QLineF lineBus = busGraphic->line();
        if(fabs(lineBus.x1() - lineBus.x2()) < 1)
        {
            btPoint.setX(lineBus.x1());
        }
        else
        {
            btPoint.setY(lineBus.y1());
        }
        this->setBeginPoint(btPoint);
        _beginLink.setLineLink(busGraphic,0);
        return true;
    }
    return false;
}

bool LineGraphic::setEndBusGraphic(BusGraphic* busGraphic)
{
    if(busGraphic)
    {
        busGraphic->setJoinGraphic(this,Graphic::JOIN_END);
        QPointF btPoint = this->getEndPoint();
        QLineF lineBus = busGraphic->line();
        if(fabs(lineBus.x1() - lineBus.x2()) < 1)
        {
            btPoint.setX(lineBus.x1());
        }
        else
        {
            btPoint.setY(lineBus.y1());
        }
        this->setEndPoint(btPoint);
        _endLink.setLineLink(busGraphic,0);
        return true;
    }
    return false;
}

bool LineGraphic::setBeginLineGraphic(LineGraphic* lineGraphic,int pos)
{
    if(lineGraphic)
    {
        //QPointF pointPort = lineGraphic->getPortPos(pos);
        //NodeLink& outLink = lineGraphic->getNodeLink(pos);
        _beginLink.setLineLinkSel(this,Graphic::JOIN_BEGIN);
        _beginLink.setLineLink(lineGraphic,pos);
        //bool bRes = outLink.combineLink(this,Graphic::JOIN_BEGIN);
        return true;
    }
    return false;
}

bool LineGraphic::setEndLineGraphic(LineGraphic* lineGraphic,int pos)
{
    if(lineGraphic)
    {
        //QPointF pointPort = lineGraphic->getPortPos(pos);
        _endLink.setLineLinkSel(this,Graphic::JOIN_END);
        _endLink.setLineLink(lineGraphic,pos);
        //NodeLink& outLink = lineGraphic->getNodeLink(pos);
        //outLink.setLineLink(lineGraphic,pos);
        //bool bRes = outLink.combineLink(this,Graphic::JOIN_END);
        return true;
    }
    return false;
}
QPointF LineGraphic::getBeginPoint()
{
    QGraphicsLineItem* front = _listLine.front();
    QLineF frontLine = front->line();
    return frontLine.p1();
}
QPointF LineGraphic::getEndPoint()
{
    QGraphicsLineItem* back = _listLine.back();
    QLineF backLine = back->line();
    return backLine.p2();
}

QPointF LineGraphic::getCenterPoint() const
{

    if(!_listLine.empty())
    {
        QList<WidthGraphicLineItem*>::const_iterator iterLine = _listLine.begin();
        const WidthGraphicLineItem*  tmpLine = *iterLine;
        QPointF plusPoint = tmpLine->line().p1();
        for(;iterLine != _listLine.end(); ++iterLine)
        {
            const WidthGraphicLineItem*  tmpLine = *iterLine;
            plusPoint += tmpLine->line().p2();
        }
        return plusPoint / (_listLine.size() + 1);
    }
    else
    {
        return QPointF(0,0);
    }
}

bool LineGraphic::setBeginPoint(const QPointF& beginPoint)
{
    if(_listLine.size() > 0)
    {
        WidthGraphicLineItem* front = _listLine.front();
        QLineF frontLine = front->line();
        QPointF centerPt = frontLine.pointAt(0.5);//取中线
        frontLine.setP1(beginPoint);
        front->setLine(frontLine);
        QPointF centerAfterPt = frontLine.pointAt(0.5);//取中线
        if(_captionGraphic)
        {
            _captionGraphic->setPos(_captionGraphic->pos() + centerAfterPt - centerPt);
        }
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(beginPoint);
       setBeginTick();
       if(_tickMid)
       {
           setMidTickPos(_tickMid);
       }
    }
    else
    {
        WidthGraphicLineItem* curLine = new WidthGraphicLineItem(beginPoint.x() ,beginPoint.y() ,
                                                           beginPoint.x() + MIN_LEN * 2, beginPoint.y() + MIN_LEN * 2,this);
        curLine->setIsFirst(true);
        curLine->setOutType(_outType);
        curLine->setPattern(_lineType,getColor(),_bShowOut);
        _listLine.push_back(curLine);
        _portPoints[Graphic::JOIN_BEGIN].setJoinPoint(beginPoint);

        if(_tickBegin)
        {
            _tickBegin->setTickPos(curLine->line(),true);
        }
        if(_tickEnd)
        {
            _tickEnd->setTickPos(curLine->line(),false);
        }
        if(_tickMid)
        {
            setMidTickPos(_tickMid);
        }
    }
    return true;
}

void LineGraphic::setBeginTick()
{
    WidthGraphicLineItem* front = _listLine.front();
    if(_tickBegin)
    {
        _tickBegin->setTickPos(front->line(),true);
    }
    if(1 == _listLine.size())
    {
        if(_tickEnd)
        {
            _tickEnd->setTickPos(front->line(),false);
        }
    }
}

void LineGraphic::setEndTick()
{
    WidthGraphicLineItem* back = _listLine.back();
    if(_tickEnd)
    {
        _tickEnd->setTickPos(back->line(),false);
    }
    if(1 == _listLine.size())
    {
        if(_tickBegin)
        {
            _tickBegin->setTickPos(back->line(),true);
        }
    }
}

const QSize& LineGraphic::getSize() const
{
    return _size;
}

bool LineGraphic::setEndPoint(const QPointF& endPoint)
{
    if(_listLine.size() > 0)
    {
        WidthGraphicLineItem* back = _listLine.back();
        QLineF backLine = back->line();
        QPointF centerPt = backLine.pointAt(0.5);
        backLine.setP2(endPoint);
        back->setLine(backLine);
        QPointF centerAfterPt = backLine.pointAt(0.5);
        if(_captionGraphic)
        {
            _captionGraphic->setPos(_captionGraphic->pos() + centerAfterPt - centerPt);
        }


        _portPoints[Graphic::JOIN_END].setJoinPoint(endPoint);

        setEndTick();
        if(_tickMid)
        {
            setMidTickPos(_tickMid);
        }
    }
    else
    {
        WidthGraphicLineItem* curLine = new WidthGraphicLineItem(endPoint.x() - MIN_LEN * 2 ,endPoint.y() -MIN_LEN * 2 ,
                                                           endPoint.x(), endPoint.y(),this);
        curLine->setIsFirst(true);
        curLine->setOutType(_outType);
        curLine->setPattern(_lineType,getColor(),_bShowOut);
        _listLine.push_back(curLine);
        _portPoints[Graphic::JOIN_END].setJoinPoint(endPoint);

        if(_tickEnd)
        {
            _tickEnd->setTickPos(curLine->line(),false);
        }
        if(_tickBegin)
        {
            _tickBegin->setTickPos(curLine->line(),true);
        }
        if(_tickMid)
        {
            setMidTickPos(_tickMid);
        }
    }
    return true;
}

bool LineGraphic::getLinePoint(QVector<QPointF>& vecPoint)const
{
    vecPoint.resize(_listLine.size() + 1);
    QList<WidthGraphicLineItem*>::const_iterator iterLine =  _listLine.begin();
    int i = 0;
    if(iterLine != _listLine.end())
    {
        const WidthGraphicLineItem* tmpLine = *iterLine;
        vecPoint[i++] = tmpLine->line().p1();
        for(;iterLine != _listLine.end();++iterLine)
        {
            const WidthGraphicLineItem* tmpLine = *iterLine;
            vecPoint[i++] = tmpLine->line().p2();
        }
    }
    return true;
}

bool LineGraphic::setLinePoint(const QVector<QPointF>& vecPoint)
{
    QList<WidthGraphicLineItem*>::Iterator iterLine =  _listLine.begin();
    int i = 1;
    for(; i < vecPoint.size() && iterLine != _listLine.end();++i,++iterLine)
    {
        WidthGraphicLineItem* tmpGraphic = *iterLine;
        QLineF  tmpLine;
        tmpLine.setP1(vecPoint[i - 1]);
        tmpLine.setP2(vecPoint[i]);
        tmpGraphic->setLine(tmpLine);
        tmpGraphic->setOutType(Graphic::OUT_NONE);
    }
    if(i >= vecPoint.size())
    {
        for(;iterLine != _listLine.end();)
        {
            WidthGraphicLineItem* tmpGraphic = *iterLine;
            this->removeFromGroup(tmpGraphic);
            delete tmpGraphic;
            iterLine = _listLine.erase(iterLine);
        }
    }
    else
    {
        for(;i < vecPoint.size(); ++i)
        {
            WidthGraphicLineItem* tmpGraphic = new WidthGraphicLineItem(vecPoint[i - 1].x(),vecPoint[i - 1].y(),
                    vecPoint[i ].x(),vecPoint[i].y(),this);
            tmpGraphic->setPattern(_lineType,getColor(),_bShowOut);
            tmpGraphic->setOutType(Graphic::OUT_NONE);
            _listLine.push_back(tmpGraphic);
        }
    }
    if(_listLine.size() > 0)
    {
        WidthGraphicLineItem* tmpGraphic = _listLine.front();
        tmpGraphic->setIsFirst(true);
        if(_tickBegin)
        {
            _tickBegin->setTickPos(tmpGraphic->line(),true);
        }
        if(_tickEnd)
        {
            WidthGraphicLineItem* tmpBack = _listLine.back();
            _tickEnd->setTickPos(tmpBack->line(),false);
        }
        switch(_outType)
        {
        case Graphic::OUT_BEGIN:
            tmpGraphic->setOutType(_outType);
            break;
        case Graphic::OUT_END:
            tmpGraphic = _listLine.back();
            tmpGraphic->setOutType(_outType);
            break;
        }
    }
    return true;
}

bool LineGraphic::setJointPoint(int pos,const QPointF& joinPoint)
{
    switch(pos)
    {
    case Graphic::JOIN_BEGIN:
        setBeginPoint(joinPoint);
        break;
    case Graphic::JOIN_END:
        setEndPoint(joinPoint);
        break;
    }
    return true;
}

bool LineGraphic::moveBeginPoint(const QPointF& movePoint)
{
    if(_listLine.size() > 0)
    {
        QGraphicsLineItem* front = _listLine.front();
        QLineF frontLine = front->line();
        frontLine.setP1(frontLine.p1() + movePoint);
        front->setLine(frontLine);
        if(_tickBegin)
        {
            _tickBegin->setTickPos(front->line(),true);
        }
        if(_listLine.size() < 2)
        {
            if(_tickEnd)
            {
                _tickEnd->setTickPos(front->line(),false);
            }
        }
        if(_tickMid)
        {
            setMidTickPos(_tickMid);
        }
        flushMove();
    }
    return true;
}

bool LineGraphic::moveEndPoint(const QPointF& mvPoint)
{
    if(_listLine.size() > 0)
    {
        QGraphicsLineItem* back = _listLine.back();
        QLineF backLine = back->line();
        backLine.setP2(backLine.p2() + mvPoint);
        back->setLine(backLine);

        if(_tickEnd)
        {
            _tickEnd->setTickPos(back->line(),false);
        }
        if(_listLine.size() < 2)
        {
            if(_tickBegin)
            {
                _tickBegin->setTickPos(back->line(),true);
            }
        }
        if(_tickMid)
        {
            setMidTickPos(_tickMid);
        }
        flushMove();
    }
    return true;
}

bool LineGraphic::setJointPointDis(int pos,const QPointF& joinMove,float dis,bool casc)
{
    switch(pos)
    {
    case Graphic::JOIN_BEGIN:
        if(_listLine.size() > 0)
        {
            QGraphicsLineItem* front = _listLine.front();
            QLineF frontLine = front->line();
            frontLine.setP1(joinMove);
            float perDis = dis / frontLine.length();
            QPointF resPoint = frontLine.pointAt(perDis);
            frontLine.setP1(resPoint);
            front->setLine(frontLine);

            Graphic* graphic = _endLink.getLinkCenter();
            if(casc && _listLine.size() < 2 && graphic)
            {
                this->setJointPointDis(Graphic::JOIN_END,graphic->getPosition(),
                                       graphic->getSize().width() / 2,false);
            }
            this->setBeginTick();
            if(_tickMid)
            {
                setMidTickPos(_tickMid);
            }
            flushMove();
        }
        break;
    case Graphic::JOIN_END:
        if(_listLine.size() > 0)
        {
            QGraphicsLineItem* back = _listLine.back();
            QLineF backLine = back->line();
            backLine.setP2(joinMove);
            float perDis = (backLine.length() - dis) / backLine.length();
            QPointF resPoint = backLine.pointAt(perDis);
            backLine.setP2(resPoint);
            back->setLine(backLine);

            Graphic* graphic = _beginLink.getLinkCenter();
            if(casc && _listLine.size() < 2 && graphic)
            {
                this->setJointPointDis(Graphic::JOIN_BEGIN,graphic->getPosition(),
                                       graphic->getSize().width() / 2,false);
            }
            this->setEndTick();
            if(_tickMid)
            {
                setMidTickPos(_tickMid);
            }
            flushMove();
        }
        break;
    }
    return true;
}

bool LineGraphic::moveJointPoint(int pos,const QPointF& joinMove)
{
    switch(pos)
    {
    case Graphic::JOIN_BEGIN:
        moveBeginPoint(joinMove);
        break;
    case Graphic::JOIN_END:
        moveEndPoint(joinMove);
        break;
    }
    return true;
}

