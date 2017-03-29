#include "graphicselector.h"
#include "busgraphic.h"
#include "linegraphic.h"
#include "captiongraphic.h"
#include "../qcdrawscene.h"
#include "stationgraphic.h"
#include <QDebug>

GraphicSelector::GraphicSelector(QCDrawScene* drawScene) :
    _drawScene(drawScene)
{
    _sizeFlag = 0;
    clear();
}
bool GraphicSelector::clearSelect()
{
    if(0 != _selectItem.size())
    {
        for (QSet<Graphic*>::Iterator i = _selectItem.begin(); i != _selectItem.end(); ++i) {
            (*i)->setSelect(false);
            (*i)->updateShape();
        }
    }
    return true;
}

int GraphicSelector::selectSelfKneeBasic(const QPointF& scenePoint, GraphicKnee& knee, Graphic *selectItem)
{
    if(!selectItem)
    {
        return SELECT_NONE;
    }
    switch(selectItem->getType())
    {
    case Graphic::GRAPHIC_BUS:
    {
        BusGraphic*busGraphic = dynamic_cast<BusGraphic*>(selectItem);
        knee.setKneeIndex(busGraphic->queryKneeNode(scenePoint));
        if(knee.getKneeIndex() >= 0)
        {
            return SELECT_KNEE;
        }
    }
        break;
    case Graphic::GRAPHIC_LINE:
    {
        LineGraphic* lineGraphic =  dynamic_cast<LineGraphic*>(selectItem);
        knee = lineGraphic->queryKneeNode(scenePoint);
        if(knee.getKneeIndex() >= 0)
        {
            return SELECT_KNEE;
        }
    }
        break;
    default:
        if(selectItem->getType() < Graphic::GRAPHIC_MAX  ||
                (selectItem->getType() > Graphic::GRAPHIC_CONTROL_BEGIN &&
                selectItem->getType() < Graphic::GRAPHIC_CONTROL_END))
        {
            //外理放大縮小
            _sizeFlag = selectItem->getSizeChangeFlag(scenePoint);
            if(_sizeFlag > 0)
            {
                return SELECT_SIZE;
            }
        }
        if(selectItem->isPointOver(scenePoint))
        {
            return SELECT_NORMAL;
        }
        else
        {
            return SELECT_NONE;
        }
        break;
    }
    return SELECT_NORMAL;
}

int GraphicSelector::selectSelfKnee(const QPointF& scenePoint, Graphic *selectItem)
{
    _selectPoint = scenePoint;
    return selectSelfKneeBasic(scenePoint,_knee,selectItem);
    /*if(!_selectItem)
    {
        return SELECT_NONE;
    }
    switch(_selectItem->getType())
    {
    case Graphic::GRAPHIC_BUS:
    {
        BusGraphic*busGraphic = dynamic_cast<BusGraphic*>(_selectItem);
        _knee.setKneeIndex(busGraphic->queryKneeNode(_selectPoint));
        if(_knee.getKneeIndex() >= 0)
        {
            return SELECT_KNEE;
        }
    }
        break;
    case Graphic::GRAPHIC_LINE:
    {
        LineGraphic* lineGraphic =  dynamic_cast<LineGraphic*>(_selectItem);
        _knee = lineGraphic->queryKneeNode(_selectPoint);
        if(_knee.getKneeIndex() >= 0)
        {
            return SELECT_KNEE;
        }
    }
        break;
    default:
        return SELECT_NORMAL;
        break;
    }
    return SELECT_NORMAL;*/
}

int GraphicSelector::selectItem(Graphic* baseItem, const QPointF& scenePoint, const int &selectType)
{
    if(!baseItem)
    {
        if(0 != _selectItem.size())
        {
            clearSelect();
            _selectItem.clear();
            _currentSelectItem = NULL;
        }
        return SELECT_NONE;
    }
    /*else if (!baseItem) {
        clearSelect();
        _selectItem.clear();
        _currentSelectItem = NULL;
        return SELECT_NONE;
    } */
    if(Qt::ControlModifier & selectType)
    {
        if(Graphic::GRAPHIC_TEXT == baseItem->getType() ||
           (_currentSelectItem && Graphic::GRAPHIC_TEXT  == _currentSelectItem->getType()))
        {
            return SELECT_NORMAL;
        }

        baseItem->setSelect(true);
        baseItem->updateShape();
        _selectItem.insert(baseItem);
        _currentSelectItem = baseItem;
        _selectPoint = scenePoint;
        return SELECT_NORMAL;
    }
    else
    {
        if (_selectItem.end() != _selectItem.find(baseItem))
        {
            if(_selectItem.size() > 1)
            {
                _currentSelectItem = baseItem;
                _selectPoint = scenePoint;
                return SELECT_NORMAL;
            }
            else
            {
                _selectPoint = scenePoint;
                return selectSelfKnee(scenePoint,baseItem);
            }
        }
        else
        {
            if(!_selectItem.empty())
            {
                clearSelect();
                _selectItem.clear();
            }
            baseItem->setSelect(true);
            _selectItem.insert(baseItem);
            baseItem->updateShape();
            _currentSelectItem = baseItem;
            _selectPoint = scenePoint;
            return SELECT_NORMAL;
        }
    }

//    baseItem->setSelect(true);
//    _selectItem.insert(baseItem);
//    baseItem->updateShape();
//    _currentSelectItem = baseItem;
//    _selectPoint = scenePoint;
//    return selectSelfKnee(scenePoint,baseItem);
//    _selectPoint = scenePoint;
//    switch(_selectItem->getType())
//    {
//    case Graphic::GRAPHIC_BUS:
//    {
//        BusGraphic*busGraphic = dynamic_cast<BusGraphic*>(_selectItem);
//        _knee.setKneeIndex(busGraphic->queryKneeNode(_selectPoint));
//        if(_knee.getKneeIndex() >= 0)
//        {
//            return SELECT_KNEE;
//        }
//    }
//        break;
//    case Graphic::GRAPHIC_LINE:
//    {
//        LineGraphic* lineGraphic =  dynamic_cast<LineGraphic*>(_selectItem);
//        _knee = lineGraphic->queryKneeNode(_selectPoint);
//        if(_knee.getKneeIndex() >= 0)
//        {
//            return SELECT_KNEE;
//        }
//    }
//        break;
//    default:
//        return SELECT_NORMAL;
//        break;
//    }

}

bool GraphicSelector::moveSelectItem(const QPointF& scenePoint, Graphic *selectItem,
                                     set<LineMove>& lineMove,bool bSingle)
{
    Graphic* parent = selectItem->parentGraphic();
    if(parent)
    {
        switch(selectItem->getType())
        {
        case Graphic::GRAPHIC_BUS:
            if(_knee.getKneeIndex() >= 0)
            {
                BusGraphic* busGraphic = dynamic_cast<BusGraphic*>(selectItem);
                busGraphic->setKneePos(_knee.getKneeIndex(),scenePoint);
            }
            else
            {
                if(Graphic::GRAPHIC_GROUP == parent->getType())
                {
                    GroupGraphicBase* groupGraphic = dynamic_cast<GroupGraphicBase*>(parent);
                    groupGraphic->moveGraphic(scenePoint - _selectPoint);
                }
            }
            break;
        case Graphic::GRAPHIC_TEXT:
        {
            CaptionGraphic* captionGraphic = dynamic_cast<CaptionGraphic*>(selectItem);
            captionGraphic->setPos(scenePoint - parent->getPosition());
        }
            break;
        default:
        {
            GraphicBase* eleGraphic = dynamic_cast<GraphicBase*>(selectItem);
            if(eleGraphic)
            {
                if(!bSingle)
                {
                    if(Graphic::GRAPHIC_GROUP == parent->getType())
                    {
                        GroupGraphicBase* groupGraphic = (GroupGraphicBase*)parent;
                        groupGraphic->moveGraphic(scenePoint - _selectPoint);
                    }
                    //selectItem->setPosition(selectItem->getPosition() + scenePoint - _selectPoint);
                }
                else
                {
                    if(!eleGraphic->moveAroundBus(scenePoint))
                    {
                        if(Graphic::GRAPHIC_GROUP == parent->getType())
                        {
                            GroupGraphicBase* groupGraphic = (GroupGraphicBase*)parent;
                            groupGraphic->moveGraphic(scenePoint - _selectPoint);
                        }
                    }
                }
            }
            else if(Graphic::GRAPHIC_GROUP == parent->getType())
            {
                GroupGraphicBase* groupGraphic = (GroupGraphicBase*)parent;
                groupGraphic->moveGraphic(scenePoint - _selectPoint);
            }
        }
            break;
        }
    }
    else
    {
        switch(selectItem->getType())
        {
        case Graphic::GRAPHIC_LINE:
            if(bSingle)
            {
                if(GraphicKnee::KNEE_UNKNOW != _knee.getKneeType())
                {
                    LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>(selectItem);
                    lineGraphic->moveKnee(_knee,scenePoint);
                    //进行线路连接
                    linkSelectLine(lineGraphic,false,selectItem);
                }
            }
            else
            {
                LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>(selectItem);
                lineGraphic->movePostion(scenePoint - _selectPoint,lineMove);
            }
            break;
        case Graphic::GRAPHIC_GROUP:
            break;
        case Graphic::GRAPHIC_BUS:
            if(_knee.getKneeIndex() >= 0)
            {
                BusGraphic* busGraphic = dynamic_cast<BusGraphic*>(selectItem);
                busGraphic->setKneePos(_knee.getKneeIndex(),scenePoint);
            }
            else
            {
                selectItem->setPosition(selectItem->getPosition() + scenePoint - _selectPoint);
            }
            break;
        //case Graphic::GR
        default:
        {
            if(_sizeFlag > 0)
            {
                selectItem->changeSizeFromSide(scenePoint,_sizeFlag);
            }
            else
            {
                selectItem->setPosition(selectItem->getPosition() + scenePoint - _selectPoint);
                //做连接判定
                GraphicBase* graphicEle = dynamic_cast<GraphicBase*>(selectItem);
                if(graphicEle)
                {
                    linkSelectEle(graphicEle,false,selectItem);
                }
            }
        }
            //for()
            break;
        }
    }
    //_selectPoint = scenePoint;
    return true;
}
bool GraphicSelector::linkSelectEle(GraphicBase* graphicEle, bool bLink, Graphic *selectItem)
{
    graphicEle->hidePortAnchor();
    set<int> vecJoin = graphicEle->queryUnMountPos();
    graphicEle->hidePortAnchor();
    //QVector<GraphicPortPoint>& vecPortPoint = graphicEle->getJoinPortPoint();
    for(set<int>::iterator iterJoint = vecJoin.begin();
        iterJoint != vecJoin.end(); ++iterJoint)
    {
        int selPos = *iterJoint;
        QPointF joinPoint = graphicEle->getPortPos(selPos) + graphicEle->pos();
        QList<GraphicPort> portList = _drawScene->selectMultiJoinItem(joinPoint);
        for(QList<GraphicPort>::Iterator iterSelPort = portList.begin();
            iterSelPort != portList.end(); ++iterSelPort)
        {
            GraphicPort& tmpSelPort = *iterSelPort;
            Graphic* graphicSel = tmpSelPort.getGraphic();
            if(graphicSel && selectItem != graphicSel && !graphicSel->isJointed(tmpSelPort.getSelPos()))
            {
                graphicEle->showPortAnchor(selPos);
                if(bLink)
                {
                    switch(graphicSel->getType())
                    {
                    case Graphic::GRAPHIC_LINE:
                    {
                        LineGraphic* lineSel = dynamic_cast<LineGraphic*>(graphicSel);

                        lineSel->setGraphicLink(tmpSelPort.getSelPos(),graphicEle,selPos);
                    }
                        break;
                    case Graphic::GRAPHIC_STATION://不可以连厂站
                    {
                    }
                        break;
                    case Graphic::GRAPHIC_BUS:
                    {
                        BusGraphic* busGraphic = dynamic_cast<BusGraphic*>(graphicSel);
                        GroupDeal groupDeal = graphicEle->setPortBus(selPos,busGraphic);
                        groupDeal.doDeal(_drawScene);
                    }
                        break;
                    default://现在
                    {
                        GraphicBase* eleGraphic = dynamic_cast<GraphicBase*>(graphicSel);
                        //修正连点
                        QPointF linkPoint = eleGraphic->getPortPos(tmpSelPort.getSelPos()) + eleGraphic->getPosition();
                        QPointF selPoint = graphicEle->getPortPos(selPos) + graphicEle->getPosition();
                        QGraphicsItem* parentItem = graphicEle->parentItem();
                        if(parentItem)
                        {
                            GroupGraphicBase* parentGroup = dynamic_cast<GroupGraphicBase*>(parentItem);
                            parentGroup->moveGraphic(linkPoint - selPoint);
                        }
                        else
                        {
                            graphicEle->setPosition(graphicEle->getPosition() + linkPoint - selPoint);
                        }
                        GroupDeal groupDeal = eleGraphic->setPortBasic(tmpSelPort.getSelPos(),graphicEle,selPos);
                        groupDeal.doDeal(_drawScene);
                    }
                        break;
                    }

                    //graphicEle->setGraphicLink(selPos,graphicSel,tmpSelPort.getSelPos());
                }
                break;
            }
        }
    }
    graphicEle->update();
    return true;
}

bool GraphicSelector::linkSelectLine(LineGraphic* lineGraphic, bool bLink, Graphic *selectItem)
{
    //进行线路连接
    int selPos = -1;
    lineGraphic->hidePortAnchor();
    if(_knee.isJointed(selPos))
    {
        if(!lineGraphic->isJointed(selPos))
        {
            QPointF joinPoint = lineGraphic->getPortPos(selPos) + lineGraphic->pos();
            QList<GraphicPort> portList = _drawScene->selectMultiJoinItem(joinPoint);
            for(QList<GraphicPort>::Iterator iterSelPort = portList.begin();
                iterSelPort != portList.end(); ++iterSelPort)
            {
                GraphicPort& tmpSelPort = *iterSelPort;
                Graphic* graphicSel = tmpSelPort.getGraphic();
                if(graphicSel && selectItem != graphicSel && !graphicSel->isJointed(tmpSelPort.getSelPos()))
                {
                    lineGraphic->showPortAnchor(selPos);
                    if(bLink)
                    {
                        switch(graphicSel->getType())
                        {
                        case Graphic::GRAPHIC_LINE:
                        {
                            LineGraphic* lineSel = dynamic_cast<LineGraphic*>(graphicSel);
                            lineSel->setLineGraphicLink(tmpSelPort.getSelPos(),lineGraphic,selPos);
                        }
                            break;
                        case Graphic::GRAPHIC_STATION://不可以连厂站
                        {
                            StationGraphic* stationGraphic = dynamic_cast<StationGraphic*>(graphicSel);
                            lineGraphic->linkGraphic(tmpSelPort.getLinkPos(),stationGraphic,Graphic::JOIN_BEGIN);
                        }
                            break;
                        case Graphic::GRAPHIC_BUS:
                        {
                            BusGraphic* busGraphic = dynamic_cast<BusGraphic*>(graphicSel);
                            lineGraphic->setBusGraphicLink(selPos,busGraphic);
                        }
                            break;
                        default://现在
                        {
                            GraphicBase* eleGraphic = dynamic_cast<GraphicBase*>(graphicSel);
                            if(eleGraphic)
                            {
                                lineGraphic->setGraphicLink(selPos,eleGraphic,tmpSelPort.getSelPos());
                            }
                        }
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
    return true;
}

bool GraphicSelector::downSelectItem(const QPointF& scenePoint, Graphic *selectItem)
{
    _selectPoint = scenePoint;
    Graphic* parent = selectItem->parentGraphic();
    selectItem->hidePortAnchor();
    if(parent)
    {
        if(Graphic::GRAPHIC_GROUP == parent->getType())
        {
            GroupGraphicBase* groupGraphic = (GroupGraphicBase*)parent;
            groupGraphic->moveGraphic(scenePoint - _selectPoint);
        }
    }
    else
    {
        //QPointF tmpPoint;
        switch(selectItem->getType())
        {
        case Graphic::GRAPHIC_LINE:
            {
                LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>(selectItem);
                linkSelectLine(lineGraphic,true,selectItem);
            }
            break;
        case Graphic::GRAPHIC_GROUP:
            break;
        case Graphic::GRAPHIC_BUS:
            if(_knee.getKneeIndex() >= 0)
            {
                BusGraphic* busGraphic = dynamic_cast<BusGraphic*>(selectItem);
                busGraphic->setKneePos(_knee.getKneeIndex(),scenePoint);
            }
            else
            {
                selectItem->setPosition(selectItem->getPosition() + scenePoint - _selectPoint);
            }
            break;
        default:
            selectItem->setPosition(selectItem->getPosition() + scenePoint - _selectPoint);

            //_selectItem->setIsDrawJoint(false);
            //做连接判定
            GraphicBase* graphicEle = dynamic_cast<GraphicBase*>(selectItem);
            if(graphicEle)
            {
                linkSelectEle(graphicEle,true,selectItem);
            }
            //for()
            break;
        }
    }
    //_knee.clear();
    return true;
}
int GraphicSelector::getNextMirror(Graphic *selectItem)
{
    if(selectItem)
    {
        switch(selectItem->getType())
        {
        case Graphic::GRAPHIC_TEXT:
        case Graphic::GRAPHIC_STATION:
            return -1;
        default:
            {
                GraphicBase* eleGraphic = dynamic_cast<GraphicBase*>(selectItem);
                if(eleGraphic)
                {
                    if(eleGraphic->getIsMirror())
                    {
                        return 0;
                    }
                    else
                    {
                        return 1;
                    }
                }
            }
        }
        return -1;
    }
    else
    {
        return -1;
    }
}
bool GraphicSelector::mirror(bool bMirror, Graphic *selectItem)
{
    if(selectItem)
    {
        GraphicBase* eleGraphic = dynamic_cast<GraphicBase*>(selectItem);
        if(eleGraphic)
        {
            if(!eleGraphic->hasMirror())
            {
                return false;
            }
            //中端连其他元件时不允许操作
            QVector<GraphicPort>& vecPort = eleGraphic->getPorts();
            for(QVector<GraphicPort>::Iterator iterPort = vecPort.begin();
                iterPort != vecPort.end(); ++iterPort)
            {
                GraphicPort& tmpPort = *iterPort;
                Graphic* graphic = tmpPort.getGraphic();
                if(graphic && Graphic::GRAPHIC_LINE != graphic->getType())
                {
                    return false;
                }
            }

            if(bMirror != eleGraphic->getIsMirror())
            {
                eleGraphic->hide();
                eleGraphic->setIsMirror(bMirror);
                eleGraphic->loadPortPos();
                //eleGraphic->update();
                eleGraphic->show();
                //調整连线
                for(QVector<GraphicPort>::Iterator iterPort = vecPort.begin();
                    iterPort != vecPort.end(); ++iterPort)
                {
                    GraphicPort& tmpPort = *iterPort;
                    Graphic* graphic = tmpPort.getGraphic();
                    if(graphic)
                    {
                        LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>(graphic);
                        lineGraphic->setJointPoint(tmpPort.getLinkPos(),
                                                   eleGraphic->pos() + eleGraphic->getPortPos(tmpPort.getSelPos()));
                        lineGraphic->update();
                    }
                }
                return true;
            }
        }
    }
    return false;
}

double GraphicSelector::scale(double scale, Graphic *selectItem)
{
    if(selectItem)
    {
        GraphicBase* eleGraphic = dynamic_cast<GraphicBase*>(selectItem);
        if(eleGraphic)
        {
            //连其他元件时不允许操作
            QVector<GraphicPort>& vecPort = eleGraphic->getPorts();
            for(QVector<GraphicPort>::Iterator iterPort = vecPort.begin();
                iterPort != vecPort.end(); ++iterPort)
            {
                GraphicPort& tmpPort = *iterPort;
                Graphic* graphic = tmpPort.getGraphic();
                if(graphic && Graphic::GRAPHIC_LINE != graphic->getType())
                {
                    return false;
                }
            }
            if(scale < 0.5)
            {
                scale = 0.5;
            }
            if(scale > 5)
            {
                scale = 5;
            }
            eleGraphic->hide();
            eleGraphic->setScale(scale);
            eleGraphic->loadPortPos();
            //eleGraphic->update();
            eleGraphic->show();
            //調整连线
            for(QVector<GraphicPort>::Iterator iterPort = vecPort.begin();
                iterPort != vecPort.end(); ++iterPort)
            {
                GraphicPort& tmpPort = *iterPort;
                Graphic* graphic = tmpPort.getGraphic();
                if(graphic)
                {
                    LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>(graphic);
                    lineGraphic->setJointPoint(tmpPort.getLinkPos(),
                                               eleGraphic->pos() + eleGraphic->getPortPos(tmpPort.getSelPos()));
                    lineGraphic->update();
                }
            }
            return scale;
        }
    }
    return scale;
}

bool GraphicSelector::delSelectItemJoin(int selPos)
{
    if(1 == _selectItem.size())
    {
        if (!(*_selectItem.begin())) {
            return false;
        }
        switch((*_selectItem.begin())->getType())
        {
        case Graphic::GRAPHIC_STATION://此两个不能删除连接
        case Graphic::GRAPHIC_BUS:
            break;
        case Graphic::GRAPHIC_LINE:
        {
            LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>(*_selectItem.begin());
            lineGraphic->delJoin(selPos);
        }
            break;
        default:
            if((*_selectItem.begin())->getType() < Graphic::GRAPHIC_MAX)
            {
                GraphicBase* eleGraphic = dynamic_cast<GraphicBase*>((*_selectItem.begin()));
                eleGraphic->delJoin(selPos);
                //拆組合
                QGraphicsItem* curItem = dynamic_cast<QGraphicsItem*>(eleGraphic);
                QGraphicsItem* parentItem = eleGraphic->parentItem();
                if(parentItem)
                {
                    GroupGraphicBase* parentGroup = dynamic_cast<GroupGraphicBase*>(parentItem);
                    QList<QGraphicsItem *> childItem = parentGroup->childItems();
                    QSet<QGraphicsItem *> childItemRes;
                    for(QList<QGraphicsItem *>::Iterator iterChild = childItem.begin();
                        iterChild != childItem.end(); ++iterChild)
                    {
                        QGraphicsItem* childItem = *iterChild;
                        childItemRes.insert(childItem);
                    }
                    QSet<QGraphicsItem *> connChild;
                    queryConnChild(childItemRes,connChild,curItem);
                    if(!connChild.empty() && !childItemRes.empty())
                    {
                        int oneNum = 0;
                        if(1 == childItemRes.size())
                        {
                            for(QSet<QGraphicsItem *>::Iterator iterRes= childItemRes.begin();
                                iterRes != childItemRes.end(); ++iterRes)
                            {
                                QGraphicsItem * tmpRes = *iterRes;
                                parentGroup->removeFromGroup(tmpRes);
                            }
                            oneNum++;
                        }
                        if(1 == connChild.size())
                        {
                            for(QSet<QGraphicsItem *>::Iterator iterConn = connChild.begin();
                                iterConn != connChild.end(); ++iterConn)
                            {
                                QGraphicsItem * tmpConn = *iterConn;
                                parentGroup->removeFromGroup(tmpConn);
                            }
                            oneNum++;
                        }
                        if(0 == oneNum)
                        {
                            GroupGraphicBase* parentConn = new GroupGraphicBase();
                            _drawScene->addItem(parentConn);
                            for(QSet<QGraphicsItem *>::Iterator iterConn = connChild.begin();
                                iterConn != connChild.end(); ++iterConn)
                            {
                                QGraphicsItem * tmpConn = *iterConn;
                                parentGroup->removeFromGroup(tmpConn);
                                parentConn->addToGroup(tmpConn);
                            }
                        }
                        else if(oneNum >= 2)
                        {
                            _drawScene->removeItem(parentGroup);
                            delete parentGroup;
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool GraphicSelector::queryConnChild(QSet<QGraphicsItem *>& resChild,
                                     QSet<QGraphicsItem *>& connChild,
                                     QGraphicsItem* curItem)
{

    if(!curItem || connChild.contains(curItem))
    {
        return true;
    }
    resChild.remove(curItem);
    connChild.insert(curItem);
    Graphic* graphic = dynamic_cast<Graphic*>(curItem);
    QVector<GraphicPort>& tmpPorts = graphic->getPorts();
    for(QVector<GraphicPort>::Iterator iterPort = tmpPorts.begin();
        iterPort != tmpPorts.end(); ++iterPort)
    {
        GraphicPort& tmpPort = *iterPort;
        Graphic* tmpGraphic = tmpPort.getGraphic();
        QGraphicsItem* tmpItem = dynamic_cast<QGraphicsItem*>(tmpGraphic);
        switch(tmpGraphic->getType())
        {
        case Graphic::GRAPHIC_BUS:
            queryConnChild(resChild,connChild,tmpItem);
            break;
        default:
            if(tmpGraphic->getType() < Graphic::GRAPHIC_MAX)
            {
                queryConnChild(resChild,connChild,tmpItem);
            }
        }
    }
    return true;
}

bool GraphicSelector::delSelectItemKnee()
{
    if(1 == _selectItem.size())
    {
        if (!(*_selectItem.begin())) {
            return false;
        }
        switch((*_selectItem.begin())->getType())
        {
        case Graphic::GRAPHIC_LINE:
            if(GraphicKnee::KNEE_JOIN== _knee.getKneeType())
            {
                LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>((*_selectItem.begin()));
                lineGraphic->delKnee(_knee);
            }
            break;
        }
    }
    return true;
}

bool GraphicSelector::delSelectItem()
{
    for (QSet<Graphic*>::Iterator i = _selectItem.begin(); i != _selectItem.end(); ++i) {
        if (NULL == *i) {
            return false;
        } else if (! (*i)->getPorts().isEmpty()) {
            return false;
        }
    }
    for (QSet<Graphic*>::Iterator i = _selectItem.begin(); i != _selectItem.end();)
    {
        if(*i)
        {
            switch((*i)->getType())
            {
            case Graphic::GRAPHIC_BUS:
            {
                if((*i)->getPorts().empty())
                {
                    QGraphicsItem* graphicItem = dynamic_cast<QGraphicsItem*>((*i));
                    QGraphicsItem* tmpParent = graphicItem->parentItem();

                    if(tmpParent)
                    {
                         GroupGraphicBase* parent = dynamic_cast<GroupGraphicBase*>(tmpParent);
                         if(parent->childItems().size() <= 1)
                         {
                             _drawScene->removeItem(parent);
                         }
                         else
                         {
                             parent->removeFromGroup(graphicItem);
                         }
                         _drawScene->removeGraphicItem((*i),false);
                    }
                    else
                    {
                        _drawScene->removeGraphicItem((*i));
                    }
                    i = _selectItem.erase(i);
                    _knee.clear();
                    if (i == _selectItem.end()) {
                        return true;
                    }
                } else {
                    ++i;
                }
            }
                break;
            case Graphic::GRAPHIC_LINE:
            {
                if((*i)->getPorts().empty())
                {
                    _drawScene->removeGraphicItem((*i));
                    i = _selectItem.erase(i);
                    _knee.clear();
                    if (i == _selectItem.end()) {
                        return true;
                    }
                } else {
                    ++i;
                }
            }
                break;
            case Graphic::GRAPHIC_TEXT:
                ++i;
                break;
            default:
                if((*i)->getType() < Graphic::GRAPHIC_MAX)
                {
                    if((*i)->getPorts().isEmpty())
                    {
                        QGraphicsItem* graphicItem = dynamic_cast<QGraphicsItem*>((*i));
                        QGraphicsItem* tmpParent = graphicItem->parentItem();

                        if(tmpParent)
                        {
                             GroupGraphicBase* parent = dynamic_cast<GroupGraphicBase*>(tmpParent);
                             if(parent->childItems().size() <= 1)
                             {
                                 _drawScene->removeItem(parent);
                             }
                             else
                             {
                                 parent->removeFromGroup(graphicItem);
                             }
                             _drawScene->removeGraphicItem((*i),false);
                        }
                        else
                        {
                            _drawScene->removeGraphicItem((*i));
                        }
                        i = _selectItem.erase(i);
                        _knee.clear();
                        if (i == _selectItem.end()) {
                            return true;
                        }
                    } else {
                        ++i;
                    }
                }
                else if((*i)->getType() > Graphic::GRAPHIC_CONTROL_BEGIN &&
                        (*i)->getType() < Graphic::GRAPHIC_CONTROL_END)
                {
                    _drawScene->removeGraphicItem((*i),true);
                     i = _selectItem.erase(i);
                }
                else
                {
                    ++i;
                }
                break;

            }
        }
    }
    return false;
}

int GraphicSelector::getNextDirect(Graphic *selectItem)
{
    if(selectItem)
    {
        switch(selectItem->getType())
        {
        case Graphic::GRAPHIC_TEXT:
            {
                CaptionGraphic* captionGraphic = dynamic_cast<CaptionGraphic*>(selectItem);
                switch(captionGraphic->getDirect())
                {
                case Graphic::POS_UP:
                case Graphic::POS_DOWN:
                    return Graphic::POS_RIGHT;
                    break;
                case Graphic::POS_RIGHT:
                case Graphic::POS_LEFT:
                    return Graphic::POS_UP;
                    break;
                }
                break;
            }
        case Graphic::GRAPHIC_STATION:
            return -1;
        default:
            {
                GraphicBase* eleGraphic = dynamic_cast<GraphicBase*>(selectItem);
                if(eleGraphic)
                {
                    switch(eleGraphic->getDirect())
                    {
                    case Graphic::POS_UP:
                        return Graphic::POS_RIGHT;
                        break;
                    case Graphic::POS_DOWN:
                        return Graphic::POS_LEFT;
                    case Graphic::POS_RIGHT:
                        return Graphic::POS_DOWN;
                    case Graphic::POS_LEFT:
                        return Graphic::POS_UP;
                        break;
                    }
                }
                break;
            }
        }
        return -1;
    }
    else
    {
        return -1;
    }
}

bool GraphicSelector::rotate(int direct, Graphic *selectItem)
{
    if(selectItem)
    {
        GraphicBase* eleGraphic = dynamic_cast<GraphicBase*>(selectItem);
        if(eleGraphic)
        {
            if(Graphic::GRAPHIC_STATION == eleGraphic->getType())
            {
                return true;
            }
            if(eleGraphic)
            {
                QVector<GraphicPort>& vecPort = eleGraphic->getPorts();
                for(QVector<GraphicPort>::Iterator iterPort = vecPort.begin();
                    iterPort != vecPort.end(); ++iterPort)
                {
                    GraphicPort& tmpPort = *iterPort;
                    Graphic* graphic = tmpPort.getGraphic();
                    if(graphic && !graphic->isLine())
                    {
                        return false;
                    }
                }
                if(direct != eleGraphic->getDirect())
                {
                    eleGraphic->hide();
                    eleGraphic->setDirect(direct);
                    eleGraphic->loadPortPos();
                    //eleGraphic->update();
                    eleGraphic->show();
                    //調整连线
                    for(QVector<GraphicPort>::Iterator iterPort = vecPort.begin();
                        iterPort != vecPort.end(); ++iterPort)
                    {
                        GraphicPort& tmpPort = *iterPort;
                        Graphic* graphic = tmpPort.getGraphic();
                        if(graphic)
                        {
                            LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>(graphic);
                            lineGraphic->setJointPoint(tmpPort.getLinkPos(),
                                                       eleGraphic->pos() + eleGraphic->getPortPos(tmpPort.getSelPos()));
                            lineGraphic->update();
                        }
                    }
                }
                return true;
            }
        }
        else
        {
            CaptionGraphic* capGraphic = dynamic_cast<CaptionGraphic*>(selectItem);
            if(capGraphic)
            {
                //QRectF tmpRect = capGraphic->boundingRect();
                capGraphic->hide();
                capGraphic->setDirect(direct);
                capGraphic->show();
                //apGraphic->update(tmpRect);
            }
        }
    }
    return false;
}

void GraphicSelector::align(ALIGN alignType) {
    if (HALIGN == alignType) {
        qreal tmpX = _currentSelectItem->getPosition().rx();
        qreal tmpY = _currentSelectItem->getPosition().ry();
        for (QSet<Graphic*>::Iterator i = _selectItem.begin(); i != _selectItem.end(); ++i) {
            QPointF point = (*i)->getPosition();
            if (point.rx() < tmpX) {
                tmpX = point.rx();
                tmpY = point.ry();
            }
        }

        for (QSet<Graphic*>::Iterator i = _selectItem.begin(); i != _selectItem.end(); ++i) {
            QPointF point = (*i)->getPosition();
            point.setY(tmpY);
            (*i)->setPosition(point);
        }
    } else if (VALIGN == alignType) {
        qreal tmpX = _currentSelectItem->getPosition().rx();
        qreal tmpY = _currentSelectItem->getPosition().ry();
        for (QSet<Graphic*>::Iterator i = _selectItem.begin(); i != _selectItem.end(); ++i) {
            QPointF point = (*i)->getPosition();
            if (point.ry() < tmpY) {
                tmpX = point.rx();
                tmpY = point.ry();
            }
        }

        for (QSet<Graphic*>::Iterator i = _selectItem.begin(); i != _selectItem.end(); ++i) {
            QPointF point = (*i)->getPosition();
            point.setX(tmpX);
            (*i)->setPosition(point);
        }
    } else {}
}

//bool GraphicSelector::selectKnee()
//{

//}
