QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH +=/usr/local/include

TARGET = QCDraw
TEMPLATE = lib
DESTDIR += ../../../lib

VERSION=3.0

equals(QT_MAJOR_VERSION,4.5.3)
{
 DEFINES+=OLDVERSION
}

SOURCES += qcdrawview.cpp \
    qcdrawscene.cpp \
    Graphics/linegraphic.cpp \
    Graphics/breakergraphic.cpp \
    Graphics/graphicbase.cpp \
    Graphics/graphicfactory.cpp \
    Graphics/stationgraphic.cpp \
    Graphics/busgraphic.cpp \
    Graphics/groupgraphicbase.cpp \
    Graphics/captiongraphic.cpp \
    Graphics/graphicport.cpp \
    Graphics/widthgraphiclineitem.cpp \
    Graphics/transformer2graphic.cpp \
    Graphics/transformer3graphic.cpp \
    Graphics/disconnectorgraphic.cpp \
    Graphics/reactorgraphic.cpp \
    Graphics/splitreactorgraphic.cpp \
    Graphics/earthgraphic.cpp \
    Graphics/groundreactorgraphic.cpp \
    Graphics/shuntcapacitorgraphic.cpp \
    Graphics/grounddisconnectorgraphic.cpp \
    Graphics/graphicconfig.cpp \
    Graphics/nodelink.cpp \
    Graphics/graphicexception.cpp \
    graphicfile.cpp \
    Graphics/graphicportpoint.cpp \
    Graphics/graphicknee.cpp \
    Graphics/graphicselector.cpp \
    Graphics/groupdeal.cpp \
    graphicstorage.cpp \
    Graphics/anchorgraphic.cpp \
    Graphics/equivaluesourcegraphic.cpp \
    Graphics/altermatorgraphic.cpp \
    Graphics/motorgraphic.cpp \
    Graphics/graphiccreator.cpp \
    Graphics/utilfunc.cpp \
    Graphics/idcreator.cpp \
    Graphics/codeconvertor.cpp \
    Graphics/selftransgraphic.cpp \
    Graphics/splittransgraphic.cpp \
    Graphics/loadgraphic.cpp \
    Graphics/serialcapacitorgraphic.cpp \
    Graphics/transgraphic.cpp \
    Graphics/transformer4graphic.cpp \
    Graphics/splittrans4graphic.cpp \
    Timer/graphicactivetimer.cpp \
    Timer/timeoperator.cpp \
    Timer/breakertimeroperator.cpp \
    Timer/stationtimeroperator.cpp \
    Graphics/tickgraphic.cpp \
    Graphics/switchgraphic.cpp \
    Graphics/widgetgraphic.cpp \
    Widgets/tablecontrolgraphic.cpp \
    Widgets/comboxcontrolgraphic.cpp \
    Graphics/graphicshape.cpp \
    Widgets/widgetgraphicbase.cpp \
    Widgets/lablecontrolgraphic.cpp \
    Widgets/pushbuttoncontrolgraphic.cpp \
    Widgets/barchartcontrolgraphic.cpp \
    Widgets/muticurvechartcontrolgraphic.cpp \
    Widgets/simicirclechartcontrolgraphic.cpp \
    UsrDefineWidget/barchart.cpp \
    UsrDefineWidget/muticurvechart.cpp \
    UsrDefineWidget/simicirclechart.cpp \
    Graphics/graphiccursor.cpp \
    Timer/lineflowtimeroperator.cpp \
    Timer/timeval.cpp \
    Graphics/lineflow.cpp \
    SpecialGraphics/dynamicpointgraphic.cpp \
    Graphics/graphic.cpp


HEADERS  +=  qcdrawview.h \
    qcdrawscene.h \
    Graphics/linegraphic.h \
    Graphics/breakergraphic.h \
    Graphics/graphicbase.h \
    Graphics/graphicfactory.h \
    Graphics/stationgraphic.h \
    Graphics/busgraphic.h \
    Graphics/groupgraphicbase.h \
    Graphics/captiongraphic.h \
    Graphics/graphic.h \
    Graphics/graphicport.h \
    Graphics/widthgraphiclineitem.h \
    Graphics/transformer2graphic.h \
    Graphics/transformer3graphic.h \
    Graphics/disconnectorgraphic.h \
    Graphics/reactorgraphic.h \
    Graphics/splitreactorgraphic.h \
    Graphics/earthgraphic.h \
    Graphics/groundreactorgraphic.h \
    Graphics/shuntcapacitorgraphic.h \
    Graphics/grounddisconnectorgraphic.h \
    Graphics/graphicconfig.h \
    Graphics/nodelink.h \
    Graphics/graphicexception.h \
    graphicfile.h \
    Graphics/graphicportpoint.h \
    Graphics/graphicknee.h \
    Graphics/graphicselector.h \
    Graphics/groupdeal.h \
    graphicstorage.h \
    Graphics/anchorgraphic.h \
    Graphics/equivaluesourcegraphic.h \
    Graphics/altermatorgraphic.h \
    Graphics/motorgraphic.h \
    Graphics/graphiccreator.h \
    Graphics/utilfunc.h \
    Graphics/idcreator.h \
    Graphics/codeconvertor.h \
    Graphics/selftransgraphic.h \
    Graphics/splittransgraphic.h \
    Graphics/loadgraphic.h \
    Graphics/serialcapacitorgraphic.h \
    Graphics/transgraphic.h \
    Graphics/transformer4graphic.h \
    Graphics/splittrans4graphic.h \
    Timer/graphicactivetimer.h \
    Timer/timeoperator.h \
    Timer/breakertimeroperator.h \
    Timer/stationtimeroperator.h \
    Graphics/tickgraphic.h \
    Graphics/switchgraphic.h \
    Graphics/widgetgraphic.h \
    Widgets/tablecontrolgraphic.h \
    Widgets/comboxcontrolgraphic.h \
    Graphics/graphicshape.h \
    Widgets/widgetgraphicbase.h \
    Widgets/lablecontrolgraphic.h \
    Widgets/pushbuttoncontrolgraphic.h \
    Widgets/barchartcontrolgraphic.h \
    Widgets/muticurvechartcontrolgraphic.h \
    Widgets/simicirclechartcontrolgraphic.h \
    UsrDefineWidget/barchart.h \
    UsrDefineWidget/muticurvechart.h \
    UsrDefineWidget/simicirclechart.h \
    Graphics/graphiccursor.h \
    Timer/lineflowtimeroperator.h \
    Timer/timeval.h \
    rapidxml/rapidxml.hpp \
    rapidxml/rapidxml_iterators.hpp \
    rapidxml/rapidxml_print.hpp \
    rapidxml/rapidxml_utils.hpp \
    Graphics/lineflow.h \
    SpecialGraphics/dynamicpointgraphic.h

RESOURCES += \
    Image/image.qrc

FORMS += \
    Widgets/shrinkwidget.ui

