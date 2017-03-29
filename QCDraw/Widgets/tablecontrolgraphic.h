#ifndef TABLECONTROLGRAPHIC_H
#define TABLECONTROLGRAPHIC_H

#include <QTableWidget>
#include "widgetgraphicbase.h"

class TableControlGraphic  : public  WidgetGraphicBase
{
public:
    TableControlGraphic(QWidget* parent = 0);
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
    QTableWidget* _table;//���
};

#endif // TABLECONTROLGRAPHIC_H
