#ifndef SIMICIRCLECHATCONTROLGRAPHIC_H
#define SIMICIRCLECHATCONTROLGRAPHIC_H

#include "../UsrDefineWidget/simicirclechart.h"
#include "widgetgraphicbase.h"

class SimiCircleChartControlGraphic  : public  WidgetGraphicBase
{
public:
    SimiCircleChartControlGraphic(QWidget* parent = 0);
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
    SimiCircleChart* _simiCircleChart;//����ͼ
};

#endif // SIMICIRCLECHATCONTROLGRAPHIC_H
