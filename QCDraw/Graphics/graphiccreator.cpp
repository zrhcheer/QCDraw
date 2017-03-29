#include "graphiccreator.h"
#include "../qcdrawscene.h"
#include "graphic.h"
#include "utilfunc.h"
#include "linegraphic.h"
#include "graphicfactory.h"
#include "graphiccursor.h"

GraphicCreator::GraphicCreator(QCDrawScene* drawScene) :
    _drawScene(drawScene),
    _dealGraphic(NULL)
{
}
bool GraphicCreator::beginCreateItem(const QPointF& mousePt)
{
    if(OPER_READY != _createStep)
    {
        return false;
    }
    switch(_type)
    {
    case CREATE_BUS:
        return beginCreateBus(mousePt);
        break;
    case CREAT_LINE:
        return beginCreateLine(mousePt);
        break;
    }
    return false;
}
bool GraphicCreator::beginCreateLine(const QPointF& mousePt)
{
    Graphic* graphic = _drawScene->selectSingleItem(mousePt);
    if(!graphic)
    {
        return false;
    }
    LineGraphic* lineGraphic = NULL;
    switch(graphic->getType())
    {
        case Graphic::GRAPHIC_BUS:
        case Graphic::GRAPHIC_STATION:
            lineGraphic = GraphicFactory::createLine(_flag & 0xff);
            lineGraphic->setID(_drawScene->createId());
            lineGraphic->setBeginPoint(mousePt);
            lineGraphic->linkGraphic(Graphic::JOIN_BEGIN,graphic,Graphic::JOIN_BEGIN);
            _dealGraphic = dynamic_cast<Graphic*>(lineGraphic);
            _drawScene->addGraphic(lineGraphic);
            _createStep = OPER_BEGIN;
            return true;
            break;
        default:
            if(graphic->getType() < Graphic::GRAPHIC_MAX)
            {
                QVector<GraphicPortPoint>&  vecPort = graphic->getJoinPortPoint();
                int i = 0;
                for(QVector<GraphicPortPoint>::Iterator iterPort = vecPort.begin();
                    iterPort != vecPort.end(); ++iterPort,i++)
                {
                    GraphicPortPoint& tmpPortPoint = *iterPort;
                    if(UtilFunc::manhattanLength(graphic->getPosition() + tmpPortPoint.getJoinPoint() - mousePt) < PORTSIZE)
                    {
                        lineGraphic = GraphicFactory::createLine(_flag & 0xff);
                        lineGraphic->setID(_drawScene->createId());
                        lineGraphic->linkGraphic(Graphic::JOIN_BEGIN,graphic,i);
                        _dealGraphic = dynamic_cast<Graphic*>(lineGraphic);
                        _drawScene->addGraphic(lineGraphic);
                        _createStep = OPER_BEGIN;
                        return true;
                    }
                }

            }
    }
    return false;
}

bool GraphicCreator::beginCreateBus(const QPointF& mousePt)
{
    QRectF sceneRect = _drawScene->sceneRect().adjusted(10,10,-10,-10);
    if(sceneRect.contains(mousePt))
    {
        BusGraphic* busItem = NULL;
        int direct = _flag & 0xFF;
        switch(direct)
        {
        case Graphic::POS_DOWN:
        case Graphic::POS_UP:
            busItem = new BusGraphic(QPointF(mousePt.x(),mousePt.y() - 10),mousePt);
            break;
        case Graphic::POS_LEFT:
        case Graphic::POS_RIGHT:
            busItem = new BusGraphic(QPointF(mousePt.x() - 10,mousePt.y()),mousePt);
            break;
        default:
            assert(false);
            break;
        }
        if(busItem)
        {
            busItem->setDirect(direct);
            busItem->setID(_drawScene->createId());
            _drawScene->addGraphic(busItem);
            _dealGraphic = busItem;
            _createStep = OPER_BEGIN;
        }
    }
    return true;
}

bool GraphicCreator::moveCreateLineBef(const QPointF& mousePt)
{
    Graphic* graphic = _drawScene->selectSingleItem(mousePt);
    if(!graphic)
    {
        return false;
    }
    switch(graphic->getType())
    {
        case Graphic::GRAPHIC_BUS:
            return true;
            break;
        case Graphic::GRAPHIC_STATION:
            return true;
            break;
        default:
            if(graphic->getType() < Graphic::GRAPHIC_MAX)
            {
                QVector<GraphicPortPoint>&  vecPort = graphic->getJoinPortPoint();
                for(QVector<GraphicPortPoint>::Iterator iterPort = vecPort.begin();
                    iterPort != vecPort.end(); ++iterPort)
                {
                    GraphicPortPoint& tmpPortPoint = *iterPort;
                    if(UtilFunc::manhattanLength(graphic->getPosition() + tmpPortPoint.getJoinPoint() - mousePt) < PORTSIZE)
                    {
                        return true;
                    }
                }

            }
    }
    return false;
}

bool GraphicCreator::moveCreateItem(const QPointF& mousePt)
{
    bool bRet = false;
    switch(_createStep)
    {
    case OPER_READY:
        switch(_type)
        {
        case CREATE_BUS:
            break;
        case CREAT_LINE:
            bRet =  moveCreateLineBef(mousePt);
            if(bRet)
            {
                GraphicCursor::getInstance()->setOverrideCursor(GraphicCursor::CURSOR_ANCHOR);
            }
            else
            {
                GraphicCursor::getInstance()->setOverrideCursor(GraphicCursor::CURSOR_ARROW);
            }
            break;
        }
        break;
    case OPER_BEGIN:
        switch(_type)
        {
        case CREATE_BUS:
            bRet =  moveCreateBus(mousePt);
            break;
        case CREAT_LINE:
            bRet =  moveCreateLine(mousePt);
            if(bRet)
            {
                GraphicCursor::getInstance()->setOverrideCursor(GraphicCursor::CURSOR_ANCHOR);
            }
            else
            {
                GraphicCursor::getInstance()->setOverrideCursor(GraphicCursor::CURSOR_ARROW);
            }
            break;
        }
        break;
    case OPER_END:
        break;
    }
    return bRet;
}
bool GraphicCreator::moveCreateLine(const QPointF& mousePt)
{
    if(_dealGraphic)
    {
        LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>(_dealGraphic);
        //QLineF tmpLine = lineGraphic->line();
        //tmpLine.setP2(mousePt);
        lineGraphic->setEndPoint(mousePt);
        QList<GraphicPort> joinPort = _drawScene->selectMultiJoinItem(mousePt);
        for(QList<GraphicPort>::Iterator iterPort = joinPort.begin();
            iterPort != joinPort.end(); ++iterPort)
        {
            GraphicPort& tmpPort = *iterPort;
            if(tmpPort.getGraphic() != _dealGraphic)
            {
                switch(tmpPort.getGraphic()->getType())
                {
                case Graphic::GRAPHIC_BUS:
                case Graphic::GRAPHIC_STATION:
                    return true;
                    break;
                default:
                    if(tmpPort.getGraphic()->getType() < Graphic::GRAPHIC_MAX)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool GraphicCreator::moveCreateBus(const QPointF& mousePt)
{
    if(_dealGraphic)
    {
        BusGraphic* busGraphic = dynamic_cast<BusGraphic*>(_dealGraphic);
        QLineF busLine = busGraphic->line();
        int direct = _flag & 0xFF;
        switch(direct)
        {
        case Graphic::POS_DOWN:
        case Graphic::POS_UP:
            busLine.setP2(QPointF(busLine.p2().x(),mousePt.y()));
            break;
        case Graphic::POS_LEFT:
        case Graphic::POS_RIGHT:
            busLine.setP2(QPointF(mousePt.x(),busLine.p2().y()));
            break;
        default:
            assert(false);
            break;
        }
        busGraphic->setLine(busLine);
        return true;
    }
    return false;
}

bool GraphicCreator::endCreateItem(const QPointF& mousePt)
{
    if(OPER_BEGIN != _createStep)
    {
        return true;
    }
    bool bRet = false;
    switch(_type)
    {
    case CREATE_BUS:
        bRet =  endCreateBus(mousePt);
        break;
    case CREAT_LINE:
        bRet =  endCreateLine(mousePt);
        break;
    }
    GraphicCursor::getInstance()->setOverrideCursor(GraphicCursor::CURSOR_ARROW);
    return false;
}

bool GraphicCreator::endCreateLine(const QPointF& mousePt)
{
    if(_dealGraphic)
    {
        LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>(_dealGraphic);
        //QLineF tmpLine = lineGraphic->line();
        //tmpLine.setP2(mousePt);

        bool bFind = false;
        QList<GraphicPort> joinPort = _drawScene->selectMultiJoinItem(mousePt);
        for(QList<GraphicPort>::Iterator iterPort = joinPort.begin();
            iterPort != joinPort.end(); ++iterPort)
        {
            GraphicPort& tmpPort = *iterPort;
            if(tmpPort.getGraphic() != _dealGraphic)
            {
                switch(tmpPort.getGraphic()->getType())
                {
                case Graphic::GRAPHIC_BUS:
                case Graphic::GRAPHIC_STATION:
                    bFind = true;
                    lineGraphic->linkGraphic(Graphic::JOIN_END,tmpPort.getGraphic(),tmpPort.getSelPos());
                    break;
                default:
                    if(tmpPort.getGraphic()->getType() < Graphic::GRAPHIC_MAX)
                    {
                        if(!tmpPort.getGraphic()->isJointed(tmpPort.getSelPos()))
                        {
                            bFind = true;
                            lineGraphic->linkGraphic(Graphic::JOIN_END,tmpPort.getGraphic(),tmpPort.getSelPos());
                        }
                    }
                }
            }
            if(bFind)
            {
                break;
            }
        }
        if(!bFind)
        {
            lineGraphic->setEndPoint(mousePt);
        }
        _createStep = OPER_END;
        return true;
    }
    _createStep = OPER_END;
    return false;
}

bool GraphicCreator::endCreateBus(const QPointF& mousePt)
{
    if(_dealGraphic)
    {
        BusGraphic* busGraphic = dynamic_cast<BusGraphic*>(_dealGraphic);
        QLineF busLine = busGraphic->line();
        int direct = _flag & 0xFF;
        switch(direct)
        {
        case Graphic::POS_DOWN:
        case Graphic::POS_UP:
            busLine.setP2(QPointF(busLine.p2().x(),mousePt.y()));
            break;
        case Graphic::POS_LEFT:
        case Graphic::POS_RIGHT:
            busLine.setP2(QPointF(mousePt.x(),busLine.p2().y()));
            break;
        default:
            assert(false);
            break;
        }
        busGraphic->setLine(busLine);
        _createStep = OPER_END;
        return true;
    }
    return false;
}
