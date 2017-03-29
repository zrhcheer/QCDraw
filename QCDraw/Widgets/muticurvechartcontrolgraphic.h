#ifndef MUTICURVECHARTCONTROLGRAPHIC_H
#define MUTICURVECHARTCONTROLGRAPHIC_H

#include "../UsrDefineWidget/muticurvechart.h"
#include "widgetgraphicbase.h"

class MutiCurveChartControlGraphic  : public  WidgetGraphicBase
{
public:
    MutiCurveChartControlGraphic(QWidget* parent = 0);
    //�ָ�
    virtual void restoreGraphic(QDataStream& dataStream);
    virtual void loadXML(rapidxml::xml_node<char> *node);
    //����
    virtual void saveGraphic(QDataStream& dataStream) const;
    virtual void saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic);
    //��ȡ�豸����
    virtual const QString& getDevName() const
    {
        return _devName;
    }
private:
    static const QString _devName;//�豸����
    MutiCurveChart* _mutiCurveChart;//����ͼ
};

#endif // MUTICURVECHARTCONTROLGRAPHIC_H
