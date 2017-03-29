#ifndef MUTICURVECHARTCONTROLGRAPHIC_H
#define MUTICURVECHARTCONTROLGRAPHIC_H

#include "../UsrDefineWidget/muticurvechart.h"
#include "widgetgraphicbase.h"

class MutiCurveChartControlGraphic  : public  WidgetGraphicBase
{
public:
    MutiCurveChartControlGraphic(QWidget* parent = 0);
    //恢复
    virtual void restoreGraphic(QDataStream& dataStream);
    virtual void loadXML(rapidxml::xml_node<char> *node);
    //保存
    virtual void saveGraphic(QDataStream& dataStream) const;
    virtual void saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic);
    //获取设备名称
    virtual const QString& getDevName() const
    {
        return _devName;
    }
private:
    static const QString _devName;//设备名称
    MutiCurveChart* _mutiCurveChart;//折线图
};

#endif // MUTICURVECHARTCONTROLGRAPHIC_H
