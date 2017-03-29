#ifndef GRAPHICFACTORY_H
#define GRAPHICFACTORY_H

#include "graphicbase.h"
#include "earthgraphic.h"
#include <QWidget>
#define STATION_SIZE 60

class WidgetGraphicBase;
class GraphicFactory
{
public:
    GraphicFactory();
    //新建图形
    static GraphicBase* createGraphic(int type);
    //新建线路
    static LineGraphic* createLine(int type);
    //新建控件
    static WidgetGraphicBase* createWidget(int type);
};

#endif // GRAPHICFACTORY_H
