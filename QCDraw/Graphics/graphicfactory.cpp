#include "graphicfactory.h"
#include "breakergraphic.h"
#include "linegraphic.h"
#include "stationgraphic.h"
#include "transformer2graphic.h"
#include "transformer3graphic.h"
#include "disconnectorgraphic.h"
#include "reactorgraphic.h"
#include "splitreactorgraphic.h"
#include "groundreactorgraphic.h"
#include"shuntcapacitorgraphic.h"
#include"grounddisconnectorgraphic.h"
#include"equivaluesourcegraphic.h"
#include"altermatorgraphic.h"
#include"motorgraphic.h"
#include"selftransgraphic.h"
#include"splittransgraphic.h"
#include"loadgraphic.h"
#include "serialcapacitorgraphic.h"
#include"transformer4graphic.h"
#include"splittrans4graphic.h"
#include "Widgets/tablecontrolgraphic.h"
#include "Widgets/comboxcontrolgraphic.h"
#include "Widgets/lablecontrolgraphic.h"
#include "Widgets/pushbuttoncontrolgraphic.h"
#include "Widgets/barchartcontrolgraphic.h"
#include "Widgets/muticurvechartcontrolgraphic.h"
#include "Widgets/simicirclechartcontrolgraphic.h"
#include"SpecialGraphics/dynamicpointgraphic.h"

GraphicFactory::GraphicFactory()
{
}
LineGraphic* GraphicFactory::createLine(int lineType)
{
    LineGraphic* line = NULL;
    line = new LineGraphic();
    line->setLineType(lineType);
    return line;
}
WidgetGraphicBase* GraphicFactory::createWidget(int type)
{
    WidgetGraphicBase*  widget = NULL;
    switch(type)
    {
    case Graphic::GRAPHIC_CONTROL_TABLE:
        widget = new TableControlGraphic();
        break;
    case Graphic::GRAPHIC_CONTROL_COMBOX:
        widget = new ComboxControlGraphic();
        break;
    case Graphic::GRAPHIC_CONTROL_LABLE:
        widget = new LableControlGraphic();
        break;
    case Graphic::GRAPHIC_CONTROL_PUSHBUTTON:
        widget = new PushButtonControlGraphic();
        break;
    case Graphic::GRAPHIC_CONTROL_BARCHART:
        widget = new BarChatControlGraphic();
        break;
    case Graphic::GRAPHIC_CONTROL_MUTICURVECHART:
        widget = new MutiCurveChartControlGraphic();
        break;
    case Graphic::GRAPHIC_CONTROL_SIMICIRCLECHART:
        widget = new SimiCircleChartControlGraphic();
        break;
    default:
        break;
    }
    return widget;
}

GraphicBase* GraphicFactory::createGraphic(int type)
{
    GraphicBase*  graphic = NULL;
    switch(type)
    {
    case Graphic::GRAPHIC_STATION:
        graphic = new StationGraphic();
        break;
    case Graphic::GRAPHIC_BREAKER:
        graphic = new BreakerGraphic();
        break;
    case Graphic::GRAPHIC_TRANS2:
        graphic = new Transformer2Graphic();
        break;
    case Graphic::GRAPHIC_TRANS3:
        graphic = new Transformer3Graphic();
        break;
    case Graphic::GRAPHIC_TRANS4:
        graphic = new Transformer4Graphic();
        break;
    case Graphic::GRAPHIC_SPLITTRANS4:
        graphic = new SplitTrans4Graphic();
        break;
    case Graphic::GRAPHIC_DISCONNECTOR:
        graphic = new DisconnectorGraphic();
        break;
    case Graphic::GRAPHIC_REACTOR:
        graphic = new ReactorGraphic();
        break;
    case Graphic::GRAPHIC_SHUNTCAPACITOR:
        graphic = new ShuntCapacitorGraphic();
        break;
    case Graphic::GRAPHIC_SERIALCAPACITOR:
        graphic = new SerialCapacitorGraphic();
        break;
    case Graphic::GRAPHIC_EQUIVALUESOURCE:
        graphic = new EquiValueSourceGraphic();
        break;
    case Graphic::GRAPHIC_ALTERMATOR:
        graphic = new AlterMatorGraphic();
        break;
    case Graphic::GRAPHIC_SPLITREACTOR:
        graphic = new SplitReactorGraphic();
        break;
    case Graphic::GRAPHIC_GROUNDREACTOR:
        graphic = new GroundReactorGraphic();
        break;
    case Graphic::GRAPHIC_GROUNDDISCONNECTOR:
        graphic = new GroundDisconnectorGraphic();
        break;
    case Graphic::GRAPHIC_SELFTRANS:
        graphic = new SelfTransGraphic();
        break;
    case Graphic::GRAPHIC_MOTOR:
        graphic = new MotorGraphic();
        break;
    case Graphic::GRAPHIC_SPLITTRANS:
        graphic = new SplitTransGraphic();
        break;
    case Graphic::GRAPHIC_LOAD:
        graphic = new LoadGraphic();
        break;
    case Graphic::GRAPHIC_DYNAMIC:
        graphic = new DynamicPointGraphic();
    }
    return graphic;
}
