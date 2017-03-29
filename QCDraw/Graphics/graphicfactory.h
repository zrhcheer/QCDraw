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
    //�½�ͼ��
    static GraphicBase* createGraphic(int type);
    //�½���·
    static LineGraphic* createLine(int type);
    //�½��ؼ�
    static WidgetGraphicBase* createWidget(int type);
};

#endif // GRAPHICFACTORY_H
