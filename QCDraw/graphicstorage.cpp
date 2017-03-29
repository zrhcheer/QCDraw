#include "graphicstorage.h"
#include "graphicfile.h"
#include "Graphics/graphicfactory.h"
#include "Graphics/linegraphic.h"
#include "Graphics/busgraphic.h"
#include "Graphics/earthgraphic.h"

GraphicStorage::GraphicStorage(bool bUtf8)
{
    _bUtf8 = bUtf8;
}

bool GraphicStorage::saveGraphic(const QString& strPath,QCDrawScene* scene)
{
    int first=strPath.lastIndexOf(".");
    QString type=strPath.right (strPath.length()-first-1);
    if("xml"==type)
    {
        saveXML(strPath,scene);
    }
    else if("qcd"==type)
    {
        saveQCD(strPath,scene);
    }
    return true;
}
bool GraphicStorage::loadGraphic(const QString& strPath,QCDrawScene* scene)
{
    int first=strPath.lastIndexOf(".");
    QString type=strPath.right(strPath.length()-first-1);
    if("xml"==type)
    {
        loadXML(strPath,scene);
    }
    else if("qcd"==type)
    {
        loadQCD(strPath,scene);
    }
    return true;
}
bool GraphicStorage::loadXML(const QString& strPath,QCDrawScene* scene)
{
    GraphicFile file(_bUtf8);
    if(!file.open(strPath,QIODevice::ReadOnly ))
    {
        return false;
    }
    string strXmlPath = "";
    if(_bUtf8)
    {
        strXmlPath = strPath.toUtf8().data();
    }
    else
    {
        strXmlPath = strPath.toStdString();
    }
    rapidxml::file<> fdoc(strXmlPath.c_str());

    rapidxml::xml_document<>doc;
    doc.parse<0>(fdoc.data());
    //获取根节点
    rapidxml::xml_node<char>* root =doc.first_node();
    if(NULL == root)
    {
        return false;
    }
    rapidxml::xml_attribute<char>* value = root->first_attribute();
    string name,width,height;
    while(value)
    {
        name = value->name();
        if("w" == name)
        {
            width = value->value();
        }
        else if("h" == name)
        {
            height = value->value();
        }
        value = value->next_attribute();
    }
    QRectF scenceRect(QPoint(0,0),QSize(atoi(width.c_str()),atoi(height.c_str())));
    scene->clear();
    scene->setSceneRect(scenceRect);
    int type;
    list<GraphicBase*> allEle;
    list<BusGraphic*> allBus;
    list<LineGraphic*> allLine;
    map<ulong64,NodeLineLink> idPorts;
    map<ulong64,Graphic*>& allElement = scene->getAllElement();
    for(rapidxml::xml_node<char>* node = root->first_node();node;node = node->next_sibling())
    {
        type = getTypeFromGraphicName((string)node->name());
        rapidxml::xml_attribute<char>* typeName = node->first_attribute();
        if(type >= 0 && type < Graphic::GRAPHIC_MAX)
        {
            GraphicBase* graphic = GraphicFactory::createGraphic(atoi(typeName->value()));
            graphic->loadXML(node);
            scene->addGraphic(graphic);
            allEle.push_back(graphic);
        }
        else if(type > Graphic::GRAPHIC_CONTROL_BEGIN &&
                type < Graphic::GRAPHIC_CONTROL_END)
        {
            WidgetGraphicBase* widgetGraphic = GraphicFactory::createWidget(atoi(typeName->value()));
            widgetGraphic->loadXML(node);
            scene->addWidget(widgetGraphic);
        }
        else if(Graphic::GRAPHIC_LINE  == type)
        {
            NodeLineLink lineLink;
            string id,ports;
            GraphicPort graphicPort;
            rapidxml::xml_attribute<char>* attr = node->first_attribute();
            while(attr)
            {
                if(0 == strcmp("id",attr->name()))
                {
                    id = attr->value();
                }
                if(0 == strcmp("ports",attr->name()))
                {
                    ports = attr->value();
                }
                attr = attr->next_attribute();
            }
            for(int i = 0;i < ports.size();++i)
            {
                size_t pos = ports.find(",",i);
                graphicPort.setSelPos(atoi((ports.substr(i,pos)).c_str()));
                size_t pos1 = ports.find(",",pos + 1);
                graphicPort.setLinkPos(atoi(ports.substr(pos + 1,pos1 - pos - 1).c_str()));
                size_t pos2 = ports.find(";",pos1 + 1);
                graphicPort.setID(atol(ports.substr(pos1 + 1,pos2 - pos1 - 1).c_str()));
                i = pos2;
                lineLink._link.push_back(graphicPort);
            }
            idPorts.insert(pair<ulong64,NodeLineLink>(atol(id.c_str()),lineLink));
            LineGraphic* line = GraphicFactory::createLine(Graphic::LINE_NOR);
            line->loadXML(node);
            scene->addGraphic(line);
            allLine.push_back(line);
        }
        else if(Graphic::GRAPHIC_BUS  == type)
        {
            BusGraphic* bus = new BusGraphic();
            bus->loadXML(node);
            scene->addGraphic(bus);
            allBus.push_back(bus);
        }
    }
    for(list<BusGraphic*>::iterator iterBus = allBus.begin(); iterBus != allBus.end(); ++iterBus)
    {
        BusGraphic* tmpBus = *iterBus;
        GroupDeal groupDeal = tmpBus->initLink(allElement);
        groupDeal.doDeal(scene);
    }
    for(list<LineGraphic*>::iterator iterLine = allLine.begin(); iterLine != allLine.end(); ++iterLine)
    {
        ulong64 selfID = (*iterLine)->getID();
        map<ulong64,NodeLineLink>::iterator iter = idPorts.find(selfID);
        if(iter != idPorts.end())
        {
            NodeLineLink nodeLineLink = iter->second;
            QList<GraphicPort> portList = nodeLineLink._link;
            for(QList<GraphicPort>::iterator ite = portList.begin();ite != portList.end();++ite)
            {
                ulong64 linkID = ite->getID();
                map<ulong64,Graphic*>::iterator itee = allElement.find(linkID);
                if(itee != allElement.end())
                {
                    Graphic* linkGraphic = itee->second;
                    map<ulong64,Graphic*>::iterator mapIter = allElement.find(selfID);
                    if(mapIter != allElement.end())
                    {
                        Graphic* selfGraphic = mapIter->second;
                        LineGraphic* selfLine = dynamic_cast<LineGraphic*>(selfGraphic);
                        if(Graphic::GRAPHIC_LINE == linkGraphic->getType())
                        {
                            LineGraphic* linkLine = dynamic_cast<LineGraphic*>(linkGraphic);
                            selfLine->setLineGraphicLink(ite->getSelPos(),linkLine,ite->getLinkPos());
                        }
                        else if(Graphic::GRAPHIC_STATION == linkGraphic->getType())
                        {
                            StationGraphic* linkStation = dynamic_cast<StationGraphic*>(linkGraphic);
                            selfLine->linkGraphic(ite->getSelPos(),linkStation,ite->getLinkPos());
                        }
                    }
                }
            }
        }
    }
    for(list<GraphicBase*>::iterator iterBasic = allEle.begin(); iterBasic != allEle.end(); ++iterBasic)
    {
        GraphicBase* tmpEle = *iterBasic;
        GroupDeal groupDeal = tmpEle->initLink(allElement);
        groupDeal.doDeal(scene);
    }
    scene->update();
}

bool GraphicStorage::loadQCD(const QString& strPathName,QCDrawScene* scene)
{
    GraphicFile file(_bUtf8);
    if(!file.open(strPathName,QIODevice::ReadOnly ))
    {
        return false;
    }
    QDataStream out(file.getFile());
    out.setVersion(QDataStream::Qt_4_0);
    quint32 magic;
    out >> magic;
    if(SERIAL_CODE != magic)
    {
        return false;
    }
    try{
        QRectF scenceRect;
        out >> scenceRect;
        scene->clear();
        scene->setSceneRect(scenceRect);
        int type;
        list<NodeLink> vecNodeLink;
        list<BusGraphic*> busAll;
        list<GraphicBase*> allEle;
        list<LineGraphic*> allLine;
        while(!out.atEnd())
        {
            out >> type;
            if(type >= 0 && type < Graphic::GRAPHIC_MAX)
            {
                GraphicBase* graphic = GraphicFactory::createGraphic(type);
                graphic->restoreGraphic(out);
                scene->addGraphic(graphic);
                allEle.push_back(graphic);
            }
            else if(type > Graphic::GRAPHIC_CONTROL_BEGIN &&
                    type < Graphic::GRAPHIC_CONTROL_END)
            {
                WidgetGraphicBase* widgetGraphic = GraphicFactory::createWidget(type);
                widgetGraphic->restoreGraphic(out);
                scene->addWidget(widgetGraphic);
            }
            else
            {
                switch(type)
                {
                //其他图形
                //case Graphic::GRAPHIC_EARTH:
                case Graphic::GRAPHIC_LINE:
                {
                    LineGraphic* line = GraphicFactory::createLine(Graphic::LINE_NOR);
                    line->restoreGraphic(out);
                    scene->addGraphic(line);
                    allLine.push_back(line);
                    break;
                }
                case Graphic::GRAPHIC_BUS:
                {
                    BusGraphic* bus = new BusGraphic();
                    bus->restoreGraphic(out);
                    scene->addGraphic(bus);
                    busAll.push_back(bus);
                    break;
                }
                    break;
                case Graphic::GRAPHIC_SAVE_LINELINK:
                {
                    int num;
                    out >> num;
                    for(int i = 0; i < num;++i)
                    {
                        NodeLink tmpNode;
                        vecNodeLink.push_back(tmpNode);
                        NodeLink& curNodeLink = vecNodeLink.back();
                        curNodeLink.restoreGraphic(out);
                    }
                }
                    break;
                default:
                    throw exception();
                    break;
                }
            }
        }
        //处理线路连接
        map<ulong64,Graphic*>& allElement = scene->getAllElement();
        for(list<NodeLink>::iterator iterNodeLink = vecNodeLink.begin();
            iterNodeLink != vecNodeLink.end(); ++iterNodeLink)
        {
            NodeLink& curNodeLink = *iterNodeLink;
            //连接控件
            NodeLineLink* tmpNodeLink = curNodeLink.getNodeLink();
            for(QList<GraphicPort>::Iterator iterPort = tmpNodeLink->_link.begin();
                iterPort != tmpNodeLink->_link.end(); ++iterPort)
            {
                GraphicPort& tmpPort = *iterPort;
                if(tmpPort.getID() <= 0)
                {
                    continue;
                }
                map<ulong64,Graphic*>::iterator iterEle =  allElement.find(tmpPort.getID());
                if(iterEle != allElement.end())
                {
                    Graphic* graphic = iterEle->second;
                    tmpPort.setGraphic(graphic);
                    if(Graphic::GRAPHIC_LINE == graphic->getType())
                    {
                        LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>(graphic);
                        NodeLink& myNodeLink = lineGraphic->getNodeLink(tmpPort.getLinkPos());
                        myNodeLink.setPort(curNodeLink.getPort());
                    }
                }
                else
                {
                    assert(false);
                }
            }
        }
        for(list<BusGraphic*>::iterator iterBus = busAll.begin(); iterBus != busAll.end(); ++iterBus)
        {
            BusGraphic* tmpBus = *iterBus;
            GroupDeal groupDeal = tmpBus->initLink(allElement);
            //QGraphicsItem* parent = tmpBus->parentItem();
            groupDeal.doDeal(scene);
        }
        for(list<GraphicBase*>::iterator iterBasic = allEle.begin(); iterBasic != allEle.end(); ++iterBasic)
        {
            GraphicBase* tmpEle = *iterBasic;
            GroupDeal groupDeal = tmpEle->initLink(allElement);
            groupDeal.doDeal(scene);
        }
        scene->update();
    }
    catch(exception ex)
    {
        scene->clear();
        return false;
    }
    return true;
}


bool GraphicStorage::saveXML(const QString &strPath, QCDrawScene *scene)
{
    rapidxml::xml_document<> doc; //创建文档对象
    rapidxml::xml_node<>* version = doc.allocate_node(rapidxml::node_pi,doc.allocate_string("xml version='1.0' encoding='GBK'"));
    doc.append_node(version);
    rapidxml::xml_node<>* node = doc.allocate_node(rapidxml::node_element,"root");
    doc.append_node(node);
    char* width = doc.allocate_string(QString::number(scene->width()).toStdString().c_str());
    char* height = doc.allocate_string(QString::number(scene->height()).toStdString().c_str());
    node->append_attribute(doc.allocate_attribute("w",width));
    node->append_attribute(doc.allocate_attribute("h",height));
    map<ulong64,Graphic*>& allElement = scene->getAllElement();
    for(map<ulong64,Graphic*>::iterator iterEle =  allElement.begin();
        iterEle != allElement.end(); ++iterEle)
    {
        Graphic* tmpGraphic = iterEle->second;
        char* typeName = doc.allocate_string(getGraphicNameFromType(tmpGraphic->getType()).c_str());
        rapidxml::xml_node<>* graphic = doc.allocate_node(rapidxml::node_element, typeName,NULL);
        node->append_node(graphic);
        tmpGraphic->saveXML(graphic,doc,tmpGraphic);
    }
    if(_bUtf8)
    {
        std::ofstream out( strPath.toUtf8().data());
        out << doc;
    }
    else
    {
        std::ofstream out( strPath.toStdString().c_str());
        out << doc;
    }
}

bool GraphicStorage::saveQCD(const QString& strPath,QCDrawScene* scene)
{
    try{
        GraphicFile file(_bUtf8);
        if(!file.open(strPath,QIODevice::WriteOnly))
        {
            return false;
        }
        map<ulong64,Graphic*>& allElement = scene->getAllElement();
        QDataStream out(file.getFile());
        //QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_0);
        out << (quint32)SERIAL_CODE;
        out << scene->sceneRect();
        set<NodeLineLink*> vecLineLink;
        for(map<ulong64,Graphic*>::iterator iterEle =  allElement.begin();
            iterEle != allElement.end(); ++iterEle)
        {
            Graphic* tmpGraphic = iterEle->second;
            if(Graphic::GRAPHIC_LINE == tmpGraphic->getType())
            {
                LineGraphic* lineGraphic = dynamic_cast<LineGraphic*>(tmpGraphic);
                //处理开始
                NodeLink& beginJoin = lineGraphic->getNodeLink(Graphic::JOIN_BEGIN);
                NodeLineLink* nodeLink = beginJoin.getNodeLink();
                if(nodeLink)
                {
                    vecLineLink.insert(nodeLink);
                }
                //处理结束
                NodeLink& endJoin = lineGraphic->getNodeLink(Graphic::JOIN_END);
                nodeLink = endJoin.getNodeLink();
                if(nodeLink)
                {
                    vecLineLink.insert(nodeLink);
                }
            }
            tmpGraphic->saveGraphic(out);
        }
        //存控件
        //        set<WidgetGraphicBase*>& allControl = scene->getAllControl();
        //        for(set<WidgetGraphicBase*>::const_iterator iterControl = allControl.begin();
        //            iterControl != allControl.end(); ++iterControl)
        //        {
        //            const WidgetGraphicBase* graphicWidget = *iterControl;
        //            graphicWidget->saveGraphic(out);
        //        }
        //存线路连接
        out << (int)Graphic::GRAPHIC_SAVE_LINELINK;
        out << (int)vecLineLink.size();
        for(set<NodeLineLink*>::iterator iterLineLink =  vecLineLink.begin();
            iterLineLink != vecLineLink.end();++iterLineLink)
        {
            NodeLineLink* tmpLink = *iterLineLink;
            out << tmpLink->_link;
        }

        /*if(!file.open(strPath + ".lnk",QIODevice::WriteOnly))
        {
            return false;
        }
        QDataStream lnkStream(file.getFile());
        lnkStream.setVersion(QDataStream::Qt_4_0);
        lnkStream << (quint32)SERIAL_CODE;
        for(set<NodeLineLink*>::iterator iterLineLink =  vecLineLink.begin();
            iterLineLink != vecLineLink.end();++iterLineLink)
        {
            NodeLineLink* tmpLink = *iterLineLink;
            if(tmpLink)
            {
                lnkStream << tmpLink->_link;
            }
        }*/
    }
    catch(exception ex)
    {
        return false;
    }

    return true;
}

int GraphicStorage::getTypeFromGraphicName(const string name)
{
    if("Station" == name)
    {
        return Graphic::GRAPHIC_STATION;
    }
    else if("Breaker" == name)
    {
        return Graphic::GRAPHIC_BREAKER;
    }
    else if("Trans2" == name)
    {
        return Graphic::GRAPHIC_TRANS2;
    }
    else if("Trans3" == name)
    {
        return Graphic::GRAPHIC_TRANS3;
    }
    else if("Disconnector" == name)
    {
        return Graphic::GRAPHIC_DISCONNECTOR;
    }
    else if("Reactor" == name)
    {
        return Graphic::GRAPHIC_REACTOR;
    }
    else if("ShuntCapacitor" == name)
    {
        return Graphic::GRAPHIC_SHUNTCAPACITOR;
    }
    else if("Splitreactor" == name)
    {
        return Graphic::GRAPHIC_SPLITREACTOR;
    }
    else if("GroundReactor" == name)
    {
        return Graphic::GRAPHIC_GROUNDREACTOR;
    }
    else if("GroundDisconnector" == name)
    {
        return Graphic::GRAPHIC_GROUNDDISCONNECTOR;
    }
    else if("EquiValueSource" == name)
    {
        return Graphic::GRAPHIC_EQUIVALUESOURCE;
    }
    else if("AlterMator" == name)
    {
        return Graphic::GRAPHIC_ALTERMATOR;
    }
    else if("Motor" == name)
    {
        return Graphic::GRAPHIC_MOTOR;
    }
    else if("SelfTrans" == name)
    {
        return Graphic::GRAPHIC_SELFTRANS;
    }
    else if("SplitTrans" == name)
    {
        return Graphic::GRAPHIC_SPLITTRANS;
    }
    else if("Load" == name)
    {
        return Graphic::GRAPHIC_LOAD;
    }
    else if("SerialCapacitor" == name)
    {
        return Graphic::GRAPHIC_SERIALCAPACITOR;
    }
    else if("Trans4" == name)
    {
        return Graphic::GRAPHIC_TRANS4;
    }
    else if("SplitTrans4" == name)
    {
        return Graphic::GRAPHIC_SPLITTRANS4;
    }
    else if("Table" == name)
    {
        return Graphic::GRAPHIC_CONTROL_TABLE;
    }
    else if("ComBox" == name)
    {
        return Graphic::GRAPHIC_CONTROL_COMBOX;
    }
    else if("Lable" == name)
    {
        return Graphic::GRAPHIC_CONTROL_LABLE;
    }
    else if("PushButton" == name)
    {
        return Graphic::GRAPHIC_CONTROL_PUSHBUTTON;
    }
    else if("BarChart" == name)
    {
        return Graphic::GRAPHIC_CONTROL_BARCHART;
    }
    else if("MutiCurveChart" == name)
    {
        return Graphic::GRAPHIC_CONTROL_MUTICURVECHART;
    }
    else if("SimiCircleChart" == name)
    {
        return Graphic::GRAPHIC_CONTROL_SIMICIRCLECHART;
    }
    else if("Line" == name)
    {
        return Graphic::GRAPHIC_LINE;
    }
    else if("Bus" == name)
    {
        return Graphic::GRAPHIC_BUS;
    }
    else if("LineLink" == name)
    {
        return Graphic::GRAPHIC_SAVE_LINELINK;
    }
}

string GraphicStorage::getGraphicNameFromType(const int type)
{
    switch(type)
    {
    case Graphic::GRAPHIC_STATION:
        return "Station";
        break;
    case Graphic::GRAPHIC_BREAKER:
        return "Breaker";
        break;
    case Graphic::GRAPHIC_TRANS2:
        return "Trans2";
        break;
    case Graphic::GRAPHIC_TRANS3:
        return "Trans3";
        break;
    case Graphic::GRAPHIC_DISCONNECTOR:
        return "Disconnector";
        break;
    case Graphic::GRAPHIC_REACTOR:
        return "Reactor";
        break;
    case Graphic::GRAPHIC_SHUNTCAPACITOR:
        return "ShuntCapacitor";
        break;
    case Graphic::GRAPHIC_SPLITREACTOR:
        return "ShuntCapacitor";
        break;
    case Graphic::GRAPHIC_GROUNDREACTOR:
        return "GroundReactor";
        break;
    case Graphic::GRAPHIC_GROUNDDISCONNECTOR:
        return "GroundDisconnector";
        break;
    case Graphic::GRAPHIC_EQUIVALUESOURCE:
        return "EquiValueSource";
        break;
    case Graphic::GRAPHIC_ALTERMATOR:
        return "AlterMator";
        break;
    case Graphic::GRAPHIC_MOTOR:
        return "Motor";
        break;
    case Graphic::GRAPHIC_SELFTRANS:
        return "SelfTrans";
        break;
    case Graphic::GRAPHIC_SPLITTRANS:
        return "SplitTrans";
        break;
    case Graphic::GRAPHIC_LOAD:
        return "Load";
        break;
    case Graphic::GRAPHIC_SERIALCAPACITOR:
        return "SerialCapacitor";
        break;
    case Graphic::GRAPHIC_TRANS4:
        return "Trans4";
        break;
    case Graphic::GRAPHIC_SPLITTRANS4:
        return "SplitTrans4";
        break;
    case Graphic::GRAPHIC_CONTROL_TABLE:
        return "Table";
        break;
    case Graphic::GRAPHIC_CONTROL_COMBOX:
        return "ComBox";
        break;
    case Graphic::GRAPHIC_CONTROL_LABLE:
        return "Lable";
        break;
    case Graphic::GRAPHIC_CONTROL_PUSHBUTTON:
        return "PushButton";
        break;
    case Graphic::GRAPHIC_CONTROL_BARCHART:
        return "BarChart";
        break;
    case Graphic::GRAPHIC_CONTROL_MUTICURVECHART:
        return "MutiCurveChart";
        break;
    case Graphic::GRAPHIC_CONTROL_SIMICIRCLECHART:
        return "SimiCircleChart";
        break;
    case Graphic::GRAPHIC_LINE:
        return "Line";
        break;
    case Graphic::GRAPHIC_BUS:
        return "Bus";
        break;
    }
}
