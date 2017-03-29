#include "groupgraphicbase.h"

const QString GroupGraphicBase::_devName = CodeConvertor::fromLocal("×éºÏ");

GroupGraphicBase::GroupGraphicBase()
{
    this->setType(GRAPHIC_GROUP);
    this->setZValue(0.1);
}
void GroupGraphicBase::moveGraphic(const QPointF& point)
{
    QList<QGraphicsItem *> groupItem = this->childItems();
    for(QList<QGraphicsItem *>::Iterator iterChild = groupItem.begin();
        iterChild != groupItem.end(); ++iterChild)
    {
        QGraphicsItem* tmpChile = *iterChild;
        Graphic* graphic = dynamic_cast<Graphic*>(tmpChile);
        graphic->setPosition(graphic->getPosition() + point);
    }
}

void GroupGraphicBase::ensureVisible()
{
    QList<QGraphicsItem *> groupItem = this->childItems();
    for(QList<QGraphicsItem *>::Iterator iterChild = groupItem.begin();
        iterChild != groupItem.end(); ++iterChild)
    {
        QGraphicsItem* tmpChile = *iterChild;
        tmpChile->ensureVisible();
    }
}
