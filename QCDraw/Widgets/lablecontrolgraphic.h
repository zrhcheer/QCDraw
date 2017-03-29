#ifndef LABLECONTROLGRAPHIC_H
#define LABLECONTROLGRAPHIC_H

#include <QLabel>
#include "widgetgraphicbase.h"

class LableControlGraphic  : public  WidgetGraphicBase
{
public:
    LableControlGraphic(QWidget* parent = 0);
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
    QLabel* _lable;//��ǩ
};

#endif // LABLECONTROLGRAPHIC_H
