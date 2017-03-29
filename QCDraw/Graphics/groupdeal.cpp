#include "groupdeal.h"
#include <QGraphicsScene>
#include "groupgraphicbase.h"

void GroupDeal::doDeal(QGraphicsScene* scence)
{
    for(map<GroupGraphicBase*,int>::iterator iterGroup = groupGraphic.begin();
        iterGroup != groupGraphic.end(); ++iterGroup)
    {
        GroupGraphicBase* tmpGroup = iterGroup->first;
        int operation = iterGroup->second;
        if(!tmpGroup)
        {
            continue;
        }
        switch (operation)
        {
        case GROUPD_DEL:
            scence->removeItem(tmpGroup);
            break;
        case GROUPD_ADD:
            scence->addItem(tmpGroup);
            break;
        }
    }
}
