#ifndef GROUPDEAL_H
#define GROUPDEAL_H

#include <set>
#include <map>
using namespace std;
class GroupGraphicBase;
class QGraphicsScene;
class GroupDeal
{
public:
    enum
    {
        GROUPD_DEL,
        GROUPD_ADD,
        GROUPD_UNKNOW
    };
    GroupDeal()
    {
    }

    GroupDeal(int oper,GroupGraphicBase* group)
    {
        groupGraphic[group] = oper;
    }
    void addDeal(int oper,GroupGraphicBase* group)
    {
        groupGraphic[group] = oper;
    }
    void doDeal(QGraphicsScene* );
    const map<GroupGraphicBase*,int>& getGroupGraphic() const
    {
        return groupGraphic;
    }
private:
    map<GroupGraphicBase*,int> groupGraphic;
};

#endif // GROUPDEAL_H
