#include "qcdrawscene.h"
#include "Graphics/breakergraphic.h"
#include "Graphics/linegraphic.h"
#include <assert.h>
#include "Graphics/graphicfactory.h"
#include "Graphics/groupgraphicbase.h"
#include <QGraphicsSceneMouseEvent>
#include <QMimeData>
#include <QDebug>
#include <QFile>
#include <set>
#include "graphicfile.h"
#include <QGraphicsWidget>
#include <QCursor>
#include "qcdrawview.h"
#include "graphicstorage.h"
#include "Graphics/utilfunc.h"
#include <QGraphicsProxyWidget>
#include "Graphics/graphiccursor.h"
#include <QApplication>


QCDrawScene::QCDrawScene(QObject *parent) :
    QGraphicsScene(parent) ,
    _selector(this),
    _creator(this),
    _idCreator(_allElement)
{
    _view = NULL;
    _oper = OPER_SELECT;
    _idCreator.setStationId(1);
    _bkColor.setRgb(128,128,128);
    _foreColor.setRgb(255,255,255);
    _isSelectScene = false;
    _rectItem = NULL;
    _config = NULL;
}
QCDrawScene::QCDrawScene(const GraphicConfig* config,QObject *parent)  :
        QGraphicsScene(parent) ,
        _selector(this),
        _creator(this),
        _idCreator(_allElement),
        _config(config)
{
    _view = NULL;
    _oper = OPER_SELECT;
    _idCreator.setStationId(1);
    _bkColor.setRgb(128,128,128);
    _foreColor.setRgb(255,255,255);
    _isSelectScene = false;
    _rectItem = NULL;
}

void QCDrawScene::setView(QCDrawView* view)
{
    _view = view;
    _config =  _view->getConfig();
}

bool QCDrawScene::saveGraphic(const QString& strPath)
{
    GraphicStorage storage(_config->getIsUtf8());
     return storage.saveGraphic(strPath,this);
}

bool QCDrawScene::loadGraphic(const QString& strPathName)
{
    GraphicStorage storage(_config->getIsUtf8());
    return storage.loadGraphic(strPathName,this);
}

//保存路径测试数据
bool QCDrawScene::saveGraphicTest(const QString& strPath)
{
    GraphicFile file(_config->getIsUtf8());
    if(!file.open(strPath,QIODevice::WriteOnly))
    {
        return false;
    }
    map<ulong64,Graphic*>& allElement = getAllElement();
    QTextStream out(file.getFile());
    out << "<Graphic>\n";
    out << "ID\tName\tLink\n";
    for(map<ulong64,Graphic*>::iterator iterEle = allElement.begin();
        iterEle != allElement.end(); ++iterEle)
    {
        Graphic* tmpGraphic = iterEle->second;
        QVector<GraphicPort>& port = tmpGraphic->getPorts();

        out << tmpGraphic->getID() << "\t";
        const QString& strName =  tmpGraphic->getName();
        if(strName.isEmpty())
        {
            out << "NULL" << "\t";
        }
        else
        {
            out << tmpGraphic->getName() << "\t";
        }

         if(port.empty())
         {
             out << "NULL";
         }
         else
         {
             QVector<GraphicPort>::const_iterator iterPort =  port.begin();
             const GraphicPort& tmpPort = *iterPort++;
             out << tmpPort.getSelPos() << "," << tmpPort.getLinkPos() << "," << tmpPort.getID();
             for(;iterPort != port.end(); ++iterPort)
             {
                 const GraphicPort& tmpPort = *iterPort;
                 out << ";" <<  tmpPort.getSelPos() << "," << tmpPort.getLinkPos() << "," << tmpPort.getID();
             }
         }
         out << "\n";
    }
    out << "</Graphic>\n";
    return true;
}

bool QCDrawScene::loadPixmap(QPixmap& pix)
{
    QRectF tmpRect = this->sceneRect();
    pix = QPixmap(tmpRect.width(),tmpRect.height());
    QPainter painter(&pix);
    this->render(&painter);   //关键函数
    return true;
}

void QCDrawScene::removeGraphicItem(Graphic * item,bool bDel)
{
    map<ulong64,Graphic*>::iterator iterItem =  _allElement.find(item->getID());
    if(iterItem != _allElement.end())
    {
        _allElement.erase(iterItem);
    }
    if(bDel)
    {
        QGraphicsItem* itemTmp = dynamic_cast<QGraphicsItem*>(item);
        if(itemTmp)
        {
            this->removeItem(itemTmp);
        }
        else
        {
            WidgetGraphicBase* widget =  dynamic_cast<WidgetGraphicBase*>(item);
            if(widget)
            {
            }
        }
        delete item;
    }
}
void QCDrawScene::removeGraphicTotal(Graphic * item)
{
    switch(item->getType())
    {
    case Graphic::GRAPHIC_LINE:
    {
        LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>(item);
        lineGraphic->unlinkGraphic();
        removeGraphicItem(item);
    }
        break;
    case Graphic::GRAPHIC_STATION:
    {
        StationGraphic* stationGraphic = dynamic_cast<StationGraphic*>(item);
        stationGraphic->unlinkGraphic();
        removeGraphicItem(item);
    }
        break;
    }
}
void QCDrawScene::removeGraphicTotalByID(const ulong64& id)
{
    map<ulong64,Graphic*>::iterator iterEle = _allElement.find(id);
    if(iterEle != _allElement.end())
    {
        removeGraphicTotal(iterEle->second);
    }
}



void QCDrawScene::calcGraphicNode(map<TopoJoin,int>& mapJoin,Graphic* tmpGraphic,int& nodeInc)
{

    map<TopoJoin,long> tmpJoinMap;
    map<int,set<long> > vecNodeHas;
    vector<int> vecPosNode;
    vecPosNode.resize(3);
    vecPosNode[0] = nodeInc++;

    bool bVir = false;
    if(Graphic::GRAPHIC_LINE == tmpGraphic->getType())
    {
        LineGraphic* lineGraphic= dynamic_cast<LineGraphic*>(tmpGraphic);
        if(lineGraphic->getLineType() & Graphic::LINE_VIR)
        {
            bVir = true;
        }
    }
    if(bVir)
    {
        vecPosNode[1] = vecPosNode[0];
        vecPosNode[2] = vecPosNode[0];
    }
    else
    {
        vecPosNode[1] = nodeInc++;
        vecPosNode[2] = nodeInc++;
    }

    TopoJoin tmpJoin;
    const QVector<GraphicPort>& vecPort = tmpGraphic->getPorts();
    for(QVector<GraphicPort>::const_iterator iterPort = vecPort.begin();
        iterPort != vecPort.end(); ++iterPort)
    {
        const  GraphicPort& tmpPort = *iterPort;
        const Graphic* graphic = tmpPort.getGraphic();

        tmpJoin._id = tmpGraphic->getID();
        tmpJoin._name = tmpGraphic->getName();//为測試
        tmpJoin._pos = tmpPort.getSelPos();
        tmpJoinMap[tmpJoin] = vecPosNode[tmpPort.getSelPos()];
        map<TopoJoin,int>::const_iterator iterAllJoin = mapJoin.find(tmpJoin);
        if(iterAllJoin != mapJoin.end())
        {
            vecNodeHas[tmpPort.getSelPos()].insert(iterAllJoin->second);
        }

        tmpJoin._id = graphic->getID();
        tmpJoin._name = graphic->getName();//为測試
        tmpJoin._pos = tmpPort.getLinkPos();
        tmpJoinMap[tmpJoin] = vecPosNode[tmpPort.getSelPos()];
        iterAllJoin = mapJoin.find(tmpJoin);
        if(iterAllJoin != mapJoin.end())
        {
            vecNodeHas[tmpPort.getSelPos()].insert(iterAllJoin->second);
        }

        if(Graphic::GRAPHIC_LINE == graphic->getType())
        {
            const LineGraphic* lineOther = dynamic_cast<const LineGraphic*>(graphic);
            if(lineOther->getLineType() & Graphic::LINE_VIR)
            {
                int posOther = tmpPort.getLinkPos();
                switch(posOther)
                {
                case Graphic::JOIN_BEGIN:
                    posOther = Graphic::JOIN_END;
                    break;
                case Graphic::JOIN_END:
                    posOther = Graphic::JOIN_BEGIN;
                    break;
                }

                tmpJoin._id = graphic->getID();
                tmpJoin._name = graphic->getName();//为測試
                tmpJoin._pos = posOther;
                tmpJoinMap[tmpJoin] = vecPosNode[tmpPort.getSelPos()];
                iterAllJoin = mapJoin.find(tmpJoin);
                if(iterAllJoin != mapJoin.end())
                {
                    vecNodeHas[tmpPort.getSelPos()].insert(iterAllJoin->second);
                }
            }
        }
    }

    for(map<int,set<long> >::iterator iterNodeHas = vecNodeHas.begin();
        iterNodeHas != vecNodeHas.end(); ++iterNodeHas)
    {
        int i = iterNodeHas->first;
        set<long>  vecNodePos = iterNodeHas->second;
        if(!vecNodePos.empty())
        {
            int curNode = *vecNodePos.begin();
            for(map<TopoJoin,int>::iterator iterAllJoin = mapJoin.begin();
                iterAllJoin != mapJoin.end(); ++iterAllJoin)
            {
                int& tmpNode = iterAllJoin->second;
                if(vecNodePos.end() != vecNodePos.find(tmpNode))
                {
                    tmpNode = curNode;
                }
            }

            int nodeAdd = vecPosNode[i];
            for(map<TopoJoin,long>::iterator iterOneJoin = tmpJoinMap.begin();
                iterOneJoin != tmpJoinMap.end(); ++iterOneJoin)
            {
                if(nodeAdd == iterOneJoin->second)
                {
                    iterOneJoin->second = curNode;
                }
            }

        }
    }

    for(map<TopoJoin,long>::iterator iterOneJoin = tmpJoinMap.begin();
        iterOneJoin != tmpJoinMap.end(); ++iterOneJoin)
    {
        mapJoin.insert(make_pair(iterOneJoin->first,iterOneJoin->second));
    }
}

//得到拓扑图
bool QCDrawScene::calcGraphicTopo(map<TopoJoin,int>& mapJoin)
{
    mapJoin.clear();
    //map<long,set<TopoJoin*> > mapNode;
    int nodeInc = 1;
    for(map<ulong64,Graphic*>::iterator iterEle = _allElement.begin();
        iterEle != _allElement.end(); ++iterEle)
    {
        Graphic* tmpGraphic = iterEle->second;
        calcGraphicNode(mapJoin,tmpGraphic,nodeInc);
    }

    for(map<TopoJoin,int>::iterator iterJoin = mapJoin.begin();
        iterJoin != mapJoin.end(); ++iterJoin)
    {
        const TopoJoin& tmpJoin = iterJoin->first;
        map<ulong64,Graphic*>::iterator iterEle  = _allElement.find(tmpJoin._id);
        if(iterEle != _allElement.end())
        {
            Graphic* tmpGraphic = iterEle->second;
            if(Graphic::GRAPHIC_LINE == tmpGraphic->getType())
            {
                LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>(tmpGraphic);
                if(lineGraphic->getLineType() & Graphic::LINE_VIR)
                {
                    mapJoin.erase(iterJoin);
                }
            }
        }
        else
        {
            assert(false);
        }
    }

    return true;
}

void QCDrawScene::rotateSelectItem()
{
    QSet<Graphic*> graphics = _selector.getSelectItem();
    for (QSet<Graphic*>::Iterator i = graphics.begin(); i != graphics.end(); ++i) {
        int direct = _selector.getNextDirect(*i);
        if(direct >=0 )
        {
            _selector.rotate(direct,*i);
        }
    }
}
void QCDrawScene::createBus(int direct)
{
    _oper = OPER_CREATE;
    _creator.setCreateType(GraphicCreator::CREATE_BUS,direct);
}
void QCDrawScene::createLine(int lineType)
{
    _oper = OPER_CREATE;
    _creator.setCreateType(GraphicCreator::CREAT_LINE,lineType);
}

void QCDrawScene::showSelectItem(Graphic*selGraphic)
{
    selGraphic->setSelect(true);
    _selector.clear();
    _selector.setSelectItem(selGraphic);
    emit selectElement(_selector,Qt::NoButton,true);
}

void QCDrawScene::mirrorSelectItem()
{
    QSet<Graphic*> graphics = _selector.getSelectItem();
    for (QSet<Graphic*>::Iterator i = graphics.begin(); i != graphics.end(); ++i) {
        int bMirror = _selector.getNextMirror(*i);
        if(bMirror >=0 )
        {
            _selector.mirror(bMirror,*i);
        }
    }
}
double QCDrawScene::scaleSelectItem(double scale)
{
    QSet<Graphic*> graphics = _selector.getSelectItem();
    for (QSet<Graphic*>::Iterator i = graphics.begin(); i != graphics.end(); ++i) {
        if(scale > 0)
        {
            return _selector.scale(scale,*i);
        }
    }
    return scale;
}

bool QCDrawScene::delSelectItem()
{
    return _selector.delSelectItem();
}
bool QCDrawScene::delSelectLineKnee()
{
    return _selector.delSelectItemKnee();
}
bool QCDrawScene::delSelectJoin(int selPos)
{
    return _selector.delSelectItemJoin(selPos);
}

void QCDrawScene::getCanvasSize(int& width,int& height)
{
    QRectF rec = this->sceneRect();
    width = rec.width();
    height = rec.height();
}
void QCDrawScene::setCanvasSize(int& width,int& height)
{
    //QRectF sceneRect = this->sceneRect();
    QRectF tmpRect = itemsBoundingRect ();
    if(tmpRect.width() > width)
    {
        width = tmpRect.width();
    }
    if(tmpRect.height() > height)
    {
        height = tmpRect.height();
    }
    if(width < 10)
    {
        width = 100;
    }
    if(height < 10)
    {
        height = 100;
    }
    this->setSceneRect(tmpRect.left(),tmpRect.top(),width,height);
    this->update();
}

void	QCDrawScene::mousePressEvent (QGraphicsSceneMouseEvent * mouseEvent)
{
    //dcb edit
    int typeMouse = Qt::NoButton;
    Qt::KeyboardModifiers modifiers = mouseEvent->modifiers();
    if (mouseEvent->buttons() & Qt::LeftButton && (modifiers & Qt::ControlModifier))
    {
        typeMouse = (int)Qt::LeftButton | Qt::ControlModifier;
    }
    else if(mouseEvent->buttons() & Qt::RightButton)
    {
        typeMouse = Qt::RightButton;
    } else if (mouseEvent->buttons() & Qt::LeftButton) {
        typeMouse = Qt::LeftButton;
    }
    if(Qt::NoButton == typeMouse)
    {
        QGraphicsScene::mousePressEvent(mouseEvent);
        return ;
    }
    QPointF scenePoint = mouseEvent->scenePos();
    limitPoint(scenePoint);
    switch(_oper)
    {
    case OPER_CREATE:
        _creator.beginCreateItem(scenePoint);
        break;
    case OPER_SELECT:
    {
        //判定是不是落在选中元件上
        Graphic* baseItem = selectSingleItem(scenePoint);
        Graphic* befItem = _selector.getCurrentSelectItem();
        int selFlag = _selector.selectItem(baseItem,scenePoint,typeMouse);
        Graphic* curSelItem = _selector.getCurrentSelectItem();
        if(_selector.getSelectItem().size() > 1)
        {
            switch(selFlag)
            {
            case GraphicSelector::SELECT_NONE:
                if(_view)
                {
                    GraphicCursor::getInstance()->setOverrideCursor(GraphicCursor::CURSOR_ARROW);
                }
                break;
            default:
                if(_view)
                {
                    GraphicCursor::getInstance()->setOverrideCursor(GraphicCursor::CURSOR_TRI);
                }
                break;
            }
        }
        else
        {
            switch(selFlag)
            {
            case GraphicSelector::SELECT_NORMAL:
                if(_view)
                {
                    GraphicCursor::getInstance()->setOverrideCursor(GraphicCursor::CURSOR_TRI);
                }
                break;
            case GraphicSelector::SELECT_NONE:
                _beginPoint = scenePoint;
                _isSelectScene = true;

                GraphicCursor::getInstance()->setOverrideCursor(GraphicCursor::CURSOR_ARROW);
                break;
            case GraphicSelector::SELECT_KNEE:
                GraphicCursor::getInstance()->setOverrideCursor(GraphicCursor::CURSOR_PEN);
                break;
            case GraphicSelector::SELECT_SIZE:
                GraphicCursor::getInstance()->setOverrideCursorFromSize(_selector.getSizeFlag());
                break;
            }
        }
        if(curSelItem != befItem)
        {
            emit selectElement(_selector,typeMouse,true);
        }
        else
        {
            emit selectElement(_selector,typeMouse,false);
        }
    }
        break;
    default:
        break;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}
void QCDrawScene::movePosition( int&chose) //add ljj
{
    QPointF scenePoint; //鼠标x y
    limitPoint(scenePoint);
    QSet<Graphic*> graphics = _selector.getSelectItem();

    if(0 != graphics.size())
    {
        set<LineMove> lineMoveVec;
        for (QSet<Graphic*>::Iterator i = graphics.begin(); i != graphics.end(); ++i) {
            switch(chose)
            {
            case MOVE_UP:
            {
                scenePoint.setX((*i)->getPosition().rx());
                scenePoint.setY(--((*i)->getPosition().ry()));
            }
                break;
            case MOVE_DOWN:
            {
                scenePoint.setX((*i)->getPosition().rx());
                scenePoint.setY(++((*i)->getPosition().ry()));
            }
                break;
            case MOVE_LEFT:
            {
                scenePoint.setY((*i)->getPosition().ry());
                scenePoint.setX(--((*i)->getPosition().rx()));
            }
                break;
            case MOVE_RIGHT:
            {
                scenePoint.setY((*i)->getPosition().ry());
                scenePoint.setX(++((*i)->getPosition().rx()));
            }
                break;
            }
            limitPoint(scenePoint);
            _selector.setSelectPoint((*i)->getPosition());
            _selector.moveSelectItem(scenePoint,(*i),lineMoveVec);  //
        }
    }
}

void	QCDrawScene::limitPoint(QPointF& scenePoint )
{
    QRectF rectScene = this->sceneRect();
    if(scenePoint.x() < rectScene.left())
    {
        scenePoint.setX(rectScene.left());
    }
    else if(scenePoint.x() > rectScene.right())
    {
        scenePoint.setX(rectScene.right());
    }
    if(scenePoint.y() < rectScene.top())
    {
        scenePoint.setY(rectScene.top());
    }
    else if(scenePoint.y() > rectScene.bottom())
    {
        scenePoint.setY(rectScene.bottom());
    }
}

void	QCDrawScene::mouseMoveEvent (QGraphicsSceneMouseEvent * mouseEvent)
{
    if(_config->getLock())
    {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
        return;
    }
    QPointF scenePoint = mouseEvent->scenePos();
    limitPoint(scenePoint);
    switch(_oper)
    {
    case OPER_CREATE:
        _creator.moveCreateItem(scenePoint);
        break;
    case OPER_SELECT:
    {
        if(_isSelectScene)
        {
            selectScene(scenePoint);
            QGraphicsScene::mouseMoveEvent(mouseEvent);
            return;
        }
        QSet<Graphic*>& graphics = _selector.getSelectItem();
        Graphic* currentGraphic = _selector.getCurrentSelectItem();
//        if(!graphics.size())
//        {
//            QGraphicsScene::mouseMoveEvent(mouseEvent);
//            return;
//        }
        if (!(mouseEvent->buttons() & Qt::LeftButton))
        {
            //QPointF scenePoint = mouseEvent->scenePos();
            //Graphic* baseItem = selectSingleItem(scenePoint);

//            if (!currentGraphic) {
//                GraphicCursor::getInstance()->setCursorForID(_view,GraphicCursor::CURSOR_ARROW);
//                QGraphicsScene::mouseMoveEvent(mouseEvent);
//                return;
//            }
            if(graphics.size() > 1)
            {
                Graphic* baseItem = selectSingleItem(scenePoint);
                const QSet<Graphic*>& selAllItem = _selector.getSelectItem();
                if(selAllItem.end() != selAllItem.find(baseItem))
                {
                    GraphicCursor::getInstance()->setOverrideCursor(GraphicCursor::CURSOR_TRI);
                }
                else
                {
                    GraphicCursor::getInstance()->setOverrideCursor(GraphicCursor::CURSOR_ARROW);
                }
            }
            else
            {
                GraphicKnee knee;
                Graphic* baseItem = selectSingleItem(scenePoint);
                switch(_selector.selectSelfKneeBasic(scenePoint,knee,baseItem))
                {
//                case GraphicSelector::SELECT_NONE:
                case GraphicSelector::SELECT_NORMAL:
                    GraphicCursor::getInstance()->setOverrideCursor(GraphicCursor::CURSOR_TRI);
                    break;
                case GraphicSelector::SELECT_KNEE:
                    GraphicCursor::getInstance()->setOverrideCursor(GraphicCursor::CURSOR_PEN);
                    break;
                case GraphicSelector::SELECT_SIZE:
                    GraphicCursor::getInstance()->setOverrideCursorFromSize(_selector.getSizeFlag());
                    break;
                default:
                    GraphicCursor::getInstance()->setOverrideCursor(GraphicCursor::CURSOR_ARROW);
                    break;
                }
            }
            QGraphicsScene::mouseMoveEvent(mouseEvent);
            return;
        }

        //QPointF scenePoint = mouseEvent->scenePos();
        if(graphics.size() > 1)
        {
            set<Graphic*> parentSet;
            set<LineMove> lineMoveVec;
            for (QSet<Graphic*>::Iterator iterGraphic = graphics.begin();
                 iterGraphic != graphics.end(); ++iterGraphic) {
                Graphic* tmpGraphic = *iterGraphic;
//                if (currentGraphic->getPosition() == (*i)->getPosition()) {
//                    continue;
//                }
 //               temp = scenePoint - currentGraphic->getPosition() + (*i)->getPosition();
//                _selector.setSelectPoint(_selector.getCurrentSelectPoint() - currentGraphic->getPosition() + (*i)->getPosition());
                Graphic* parentGraphic = tmpGraphic->parentGraphic();
                if(parentGraphic)
                {
                    if(parentSet.end() == parentSet.find(parentGraphic))
                    {
                        parentSet.insert(parentGraphic);
                        _selector.moveSelectItem(scenePoint,tmpGraphic,lineMoveVec,false);
                    }
                }
                else
                {
                    _selector.moveSelectItem(scenePoint,tmpGraphic,lineMoveVec,false);
                }

            }
            _selector.setSelectPoint(scenePoint);
        }
        else if(!graphics.empty())
        {
            set<LineMove> lineMoveVec;
            _selector.moveSelectItem(scenePoint,currentGraphic,lineMoveVec);
            _selector.setSelectPoint(scenePoint);
        }
        break;
    }
    }
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void	QCDrawScene::mouseReleaseEvent (QGraphicsSceneMouseEvent * mouseEvent)
{
    if(_config->getLock())
    {
        QGraphicsScene::mouseReleaseEvent(mouseEvent);
        return;
    }
    QPointF scenePoint = mouseEvent->scenePos();
    limitPoint(scenePoint);
    switch(_oper)
    {
    case OPER_CREATE:
        _creator.endCreateItem(scenePoint);
        _oper = OPER_SELECT;
        break;
    case OPER_SELECT:
        if(_isSelectScene)
        {
            if (_rectItem) {
                removeItem(_rectItem);
                delete _rectItem;
                _rectItem = NULL;
                showSelectSceneItems(scenePoint);
            }
            _isSelectScene = false;
            QGraphicsScene::mouseReleaseEvent(mouseEvent);
            return ;
        }
        QSet<Graphic*> graphics = _selector.getSelectItem();
        Graphic* currentGraphic = _selector.getCurrentSelectItem();
        if(!graphics.size() || !currentGraphic)
        {

            QGraphicsScene::mouseReleaseEvent(mouseEvent);
            return;
        }

        for (QSet<Graphic*>::Iterator i = graphics.begin(); i != graphics.end(); ++i) {
            QPointF temp = scenePoint;
            temp = scenePoint - currentGraphic->getPosition() + (*i)->getPosition();
            _selector.setSelectPoint((*i)->getPosition());
            _selector.downSelectItem(temp,*i);
        }
//        if(_view)
//        {
//            _view->setCursorForID(GraphicCursor::CURSOR_ARROW);
//        }
    }
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

//void QCDrawScene::setCursorFromID(int indexCursor)
//{
//    if(_view)
//    {
//        _view->setCursorForID(indexCursor);
//    }
//}

QList<GraphicPort> QCDrawScene::selectMultiJoinItem(const QPointF& selPoint)
{
    QList<GraphicPort> linkPort;
    QRectF selRect(selPoint.x() - PORTSIZE,selPoint.y() - PORTSIZE,PORTSIZE * 2,PORTSIZE * 2 );
    QList<QGraphicsItem *> selItems = this->items(selRect);
    for(QList<QGraphicsItem *>::Iterator iterItem = selItems.begin();
        iterItem != selItems.end(); ++iterItem)
    {
        QGraphicsItem* curItem = *iterItem;
        Graphic* graphic = dynamic_cast<Graphic*>(curItem);
        if(graphic)
        {
            switch(graphic->getType())
            {
            case Graphic::GRAPHIC_BUS:
                {
                    GraphicPort tmpPort;
                    tmpPort.setSelPos(0);
                    tmpPort.setGraphic(graphic);
                    linkPort.push_back(tmpPort);
                }
                break;
            default:
                {
                    QVector<GraphicPortPoint>& vecPortPoint = graphic->getJoinPortPoint();
                    for(int i = 0; i < vecPortPoint.size(); i++)
                    {
                        if(UtilFunc::manhattanLength(selPoint - vecPortPoint[i].getJoinPoint() - graphic->getPosition()) < PORTSIZE)
                        {
                            GraphicPort tmpPort;
                            tmpPort.setSelPos(i);
                            tmpPort.setGraphic(graphic);
                            linkPort.push_back(tmpPort);
                            break;
                        }
                    }
                }
                break;
            }
        }
        else
        {
            QGraphicsItem* graphicItem = curItem->parentItem();
            while(graphicItem)
            {
                graphic = dynamic_cast<Graphic*>(graphicItem);
                bool bOut = false;
                if(graphic)
                {
                    switch(graphic->getType())
                    {
                    case Graphic::GRAPHIC_BUS:
                        {
                            GraphicPort tmpPort;
                            tmpPort.setSelPos(0);
                            tmpPort.setGraphic(graphic);
                            linkPort.push_back(tmpPort);
                            bOut = true;
                        }
                        break;
                    default:
                        {
                            QVector<GraphicPortPoint>& vecPortPoint = graphic->getJoinPortPoint();
                            for(int i = 0; i < vecPortPoint.size(); i++)
                            {
                                if(UtilFunc::manhattanLength(selPoint - vecPortPoint[i].getJoinPoint() - graphic->getPosition()) < PORTSIZE)
                                {
                                    GraphicPort tmpPort;
                                    tmpPort.setSelPos(i);
                                    tmpPort.setGraphic(graphic);
                                    linkPort.push_back(tmpPort);
                                    bOut = true;
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
                graphicItem = graphicItem->parentItem();
                if(bOut)
                {
                     break;
                }
            }

        }
    }
    return linkPort;
}

Graphic* QCDrawScene::selectSingleItem(const QPointF& selPoint)
{
    QList<QGraphicsItem *> selItems = this->items(selPoint);
    for(QList<QGraphicsItem *>::Iterator iterItem = selItems.begin();
        iterItem != selItems.end(); ++iterItem)
    {
        QGraphicsItem* curItem = *iterItem;
        Graphic* graphic = findCurrentEle(curItem,true);
        return graphic;
//        if(graphic)
//        {
//            switch(graphic->getType())
//            {
//            case Graphic::GRAPHIC_LINE:
//            case  Graphic::GRAPHIC_BUS:
//            case Graphic::GRAPHIC_TEXT:
//                return graphic;
//                break;
//            default:
//                if(graphic->getType() < Graphic::GRAPHIC_MAX)
//                {
//                    return graphic;
//                }
//                else if(graphic->getType() > Graphic::GRAPHIC_CONTROL_BEGIN &&
//                        graphic->getType() < Graphic::GRAPHIC_CONTROL_END)
//                {
//                    return graphic;
//                }
//            }
//        }
//        else
//        {
//            QGraphicsProxyWidget* proxyWidget = dynamic_cast<QGraphicsProxyWidget*>(curItem);
//            if(proxyWidget)
//            {
//                QWidget* widget = proxyWidget->widget();
//                Graphic* graphicWidget = dynamic_cast<Graphic*>(widget);
//                if(graphicWidget)
//                {
//                    return graphicWidget;
//                }
//            }
//            else
//            {
//                QGraphicsItem* graphicItem = curItem->parentItem();
//                while(graphicItem)
//                {
//                    graphic = dynamic_cast<Graphic*>(graphicItem);
//                    bool bOut = false;
//                    if(graphic)
//                    {
//                        switch(graphic->getType())
//                        {
//                        case Graphic::GRAPHIC_LINE:
//                        case  Graphic::GRAPHIC_BUS:
//                            return graphic;
//                            break;
//                        default:
//                            {
//                                if(graphic->getType() < Graphic::GRAPHIC_MAX)
//                                {
//                                    return graphic;
//                                }
//                            }
//                            break;
//                        }
//                    }
//                    graphicItem = graphicItem->parentItem();
//                    if(bOut)
//                    {
//                         break;
//                    }
//                }
//            }
//        }
    }
    return NULL;
}

void	QCDrawScene::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    if (!(mouseEvent->buttons() & Qt::LeftButton))
    {
        QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
        return;
    }
    //QTransform deviceTransform;
    QPointF scenePoint = mouseEvent->scenePos();
    Graphic* baseItem = selectSingleItem(scenePoint);
    if(!baseItem)
    {
        QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
        return;
    }
    //如果是接地則取他的上一級
    switch(baseItem->getType())
    {
    case Graphic::GRAPHIC_STATION:
    case Graphic::GRAPHIC_LINE:
        emit clickElement(baseItem);
        break;
    }
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void	QCDrawScene::drawBackground ( QPainter * painter, const QRectF & rect )
{
    painter->fillRect(rect,QBrush(_bkColor));
    QRectF rectScene = this->sceneRect();
    painter->fillRect(rectScene,QBrush(_foreColor));
}

void  QCDrawScene::dragEnterEvent (QGraphicsSceneDragDropEvent * event)
{
    //qDebug("dragEnterEvent: enter drag mode ............");

    if(event->mimeData()->hasFormat("custom/graphic") ||
            event->mimeData()->hasFormat("custom/control"))
    {
        //m_dragMode = 1;
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
        QGraphicsScene::dragEnterEvent(event);
    }
}

void  QCDrawScene::dragLeaveEvent (QGraphicsSceneDragDropEvent* event)
{
    //qDebug("exit topotree, exit drag mode ............");
    //m_dragMode = 0;
    QGraphicsScene::dragLeaveEvent(event);
}

void  QCDrawScene::dragMoveEvent (QGraphicsSceneDragDropEvent * event)
{
    if(event->mimeData()->hasFormat("custom/graphic") || event->mimeData()->hasFormat("custom/control"))
    {
        event->acceptProposedAction();
        return;
    }

    event->ignore();
    QGraphicsScene::dragMoveEvent(event);
}

void  QCDrawScene::dropEvent (QGraphicsSceneDragDropEvent* event)
{
    if(event->mimeData()->hasFormat("custom/graphic"))
    {
        QByteArray data = event->mimeData()->data("custom/graphic");
        int type = data.toInt();
        GraphicBase* base = GraphicFactory::createGraphic(type);
        if(base)
        {
            base->setID(_idCreator.createId());
            QPointF scenePoint = event->scenePos();
            base->setPos(scenePoint);
            //base->setCenter(tmpPoint.x(),tmpPoint.y());
            base->setScale(1);
            base->loadPortPos();
            this->addGraphic(base);
            event->acceptProposedAction();
            return;
        }
    }
    else if(event->mimeData()->hasFormat("custom/control"))
    {
        QByteArray data = event->mimeData()->data("custom/control");
        int type = data.toInt();
        WidgetGraphicBase* base = GraphicFactory::createWidget(type);
        if(base)
        {
            base->setID(_idCreator.createId());
            QPointF scenePoint = event->scenePos();
            base->setPosition(scenePoint.toPoint());
            //base->setCenter(tmpPoint.x(),tmpPoint.y());
            //base->setScale(1);
            //base->loadPortPos();
            this->addWidget(base);
            event->acceptProposedAction();
            return;
        }
    }
    event->ignore();
    QGraphicsScene::dropEvent(event);
}

void QCDrawScene::horizontalAlign(void) {
    _selector.align(GraphicSelector::HALIGN);
}

void QCDrawScene::verticalAlign(void) {
     _selector.align(GraphicSelector::VALIGN);
}

void QCDrawScene::selectScene(QPointF& point) {
    QRectF rect(_beginPoint,point);
    rect = rect.normalized();
    if(_rectItem)
    {
        _rectItem->setRect(rect);
    }
    else
    {
        _rectItem = new QGraphicsRectItem(rect);
        addItem(_rectItem);
    }
}


Graphic* QCDrawScene::findCurrentEle(QGraphicsItem* curItem,bool bBasic)
{
    Graphic* graphic = dynamic_cast<Graphic*>(curItem);
    if(graphic)
    {
        if(bBasic)
        {
            switch(graphic->getType())
            {
            case Graphic::GRAPHIC_TEXT:
                return graphic;
                break;
            case Graphic::GRAPHIC_CONTROL_SHRINK:
                return graphic;
                break;
            }
        }
        switch(graphic->getType())
        {
        case Graphic::GRAPHIC_LINE:
        case  Graphic::GRAPHIC_BUS:
            return graphic;
            break;

        case Graphic::GRAPHIC_EARTH:
        case Graphic::GRAPHIC_TICK:
        {
            Graphic* parantGraphic = graphic->parentGraphic();
            switch (parantGraphic->getType())
            {
            case Graphic::GRAPHIC_LINE:
            case  Graphic::GRAPHIC_BUS:
               return parantGraphic;
            default:
               if(parantGraphic->getType() < Graphic::GRAPHIC_MAX)
               {
                   return parantGraphic;
               }
               else if(parantGraphic->getType() > Graphic::GRAPHIC_CONTROL_BEGIN &&
                       parantGraphic->getType() < Graphic::GRAPHIC_CONTROL_END)
               {
                   return parantGraphic;
               }
               break;
            }
        }
            break;
        default:
            if(graphic->getType() < Graphic::GRAPHIC_MAX)
            {
                return graphic;
            }
            else if(graphic->getType() > Graphic::GRAPHIC_CONTROL_BEGIN &&
                    graphic->getType() < Graphic::GRAPHIC_CONTROL_END)
            {
                return graphic;
            }
        }
    }
    else
    {
        QGraphicsProxyWidget* proxyWidget = dynamic_cast<QGraphicsProxyWidget*>(curItem);
        if(proxyWidget)
        {
            QWidget* widget = proxyWidget->widget();
            Graphic* graphicWidget = dynamic_cast<Graphic*>(widget);
            if(graphicWidget)
            {
                return graphicWidget;
            }
        }
        else
        {
            QGraphicsItem* graphicItem = curItem->parentItem();
            while(graphicItem)
            {
                graphic = dynamic_cast<Graphic*>(graphicItem);
                bool bOut = false;
                if(graphic)
                {
                    switch(graphic->getType())
                    {
                    case Graphic::GRAPHIC_LINE:
                    case  Graphic::GRAPHIC_BUS:
                        return graphic;
                        break;
                    default:
                        {
                            if(graphic->getType() < Graphic::GRAPHIC_MAX)
                            {
                                return graphic;
                            }
                        }
                        break;
                    }
                }
                graphicItem = graphicItem->parentItem();
                if(bOut)
                {
                     break;
                }
            }
        }
    }
    return NULL;
}

void QCDrawScene::showSelectSceneItems(QPointF &point) {
    QRectF tmp(_beginPoint,point);
    tmp = tmp.normalized();
    QList<QGraphicsItem*> selectItems = items(tmp);
    for (QList<QGraphicsItem*>::Iterator i = selectItems.begin(); i != selectItems.end(); ++i)
    {
        QGraphicsItem* item = *i;
        Graphic* graphic = findCurrentEle(item);
        if(graphic)
        {
            _selector.selectItem(graphic,point, (int)Qt::LeftButton | (int)Qt::ControlModifier);
        }
//        Graphic* convert = dynamic_cast<Graphic*>(*i);
//        if (convert) {
//            if (Graphic::GRAPHIC_MAX > convert->getType() ||
//                    (convert->getType() > Graphic::GRAPHIC_CONTROL_BEGIN && convert->getType() < Graphic::GRAPHIC_CONTROL_END) ||
//                    (convert->getType() == Graphic::GRAPHIC_LINE) || (convert->getType() == Graphic::GRAPHIC_BUS) )
//            {
//                _selector.selectItem(convert,point,(Qt::LeftButton | Qt::ControlModifier));
//            }
//        }
//        else
//        {
//            QGraphicsProxyWidget* proxyWidget = dynamic_cast<QGraphicsProxyWidget*>(*i);
//            if(proxyWidget)
//            {
//                QWidget* widget = proxyWidget->widget();
//                Graphic* graphicWidget = dynamic_cast<Graphic*>(widget);
//                if(graphicWidget)
//                {
//                   _selector.selectItem(graphicWidget,point,(Qt::LeftButton | Qt::ControlModifier));
//                }
//            }
//        }
    }
//    for (map<ulong64,Graphic*>::iterator i = _allElement.begin(); i != _allElement.end(); ++i) {
//        QPointF tmp = i->second->getPosition();
//        if (tmp.x() > tmpBegin.x() && tmp.y() > tmpBegin.y() && tmp.x() < tmpEnd.x() && tmp.y() < tmpEnd.y()) {
//            _selector.selectItem(i->second,QPointF(tmp.rx() + (i->second->getSize().width() / 2), tmp.ry() + (i->second->getSize().height() / 2)),(Qt::LeftButton | Qt::ControlModifier));
//        }
//    }
}
