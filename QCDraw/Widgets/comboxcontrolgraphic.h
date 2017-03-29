#ifndef COMBOXCONTROLGRAPHIC_H
#define COMBOXCONTROLGRAPHIC_H

#include "widgetgraphicbase.h"
#include <QComboBox>
class ComboxControlGraphic : public WidgetGraphicBase
{
public:
    ComboxControlGraphic(QWidget* parent = 0);
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
    QComboBox* _combox;//下拉列表框
};

#endif // COMBOXCONTROLGRAPHIC_H
