#ifndef COMBOXCONTROLGRAPHIC_H
#define COMBOXCONTROLGRAPHIC_H

#include "widgetgraphicbase.h"
#include <QComboBox>
class ComboxControlGraphic : public WidgetGraphicBase
{
public:
    ComboxControlGraphic(QWidget* parent = 0);
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
    QComboBox* _combox;//�����б��
};

#endif // COMBOXCONTROLGRAPHIC_H
