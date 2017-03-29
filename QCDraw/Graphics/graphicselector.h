#ifndef GRAPHICSELECTOR_H
#define GRAPHICSELECTOR_H
#include "graphicknee.h"
#include "graphic.h"
#include <QSet>
#include <set>

class LineMove;
class LineGraphic;
class GraphicBase;
class QCDrawScene;
class GraphicSelector
{
public:
    GraphicSelector(QCDrawScene* drawScene);
    enum
    {
        SELECT_NORMAL,
        SELECT_KNEE,
        SELECT_SIZE,
        SELECT_NONE
    };

    enum ALIGN {
        HALIGN,
        VALIGN
    };
    //清空
    void clear()
    {
        if(0 != _selectItem.size())
        {
            for (QSet<Graphic*>::Iterator i = _selectItem.begin(); i != _selectItem.end(); ++i) {
                (*i)->setSelect(false);
            }
        }
        _selectItem.clear();
        _currentSelectItem = NULL;
        _knee.setKneeType(GraphicKnee::KNEE_UNKNOW);
        _knee.setBeginLine(NULL);
        _knee.setEndLine(NULL);
    }
    //清空选择项
    bool clearSelect();
    //获取baseItem对应的类型
    int selectItem(Graphic* baseItem, const QPointF& scenePoint, const int &selectType);
    //选中selectItem内的拐点
    int selectSelfKnee(const QPointF& scenePoint, Graphic *selectItem);
    //获取选中的类型
    int selectSelfKneeBasic(const QPointF& scenePoint, GraphicKnee& knee, Graphic *selectItem);
    //移动选中的元件
    bool moveSelectItem(const QPointF& scenePoint, Graphic *selectItem,set<LineMove>& lineMove,bool bSingle=true);
    bool downSelectItem(const QPointF& scenePoint, Graphic *selectItem);

    bool linkSelectEle(GraphicBase* lineGraphic, bool bLink, Graphic *selectItem);
    //元件链接到选中线路上
    bool linkSelectLine(LineGraphic* lineGraphic, bool bLink, Graphic *selectItem);
    //將元件旋轉到指定方向
    bool rotate(int direct, Graphic *selectItem);
    int getNextDirect(Graphic *selectItem);
    int getNextMirror(Graphic *selectItem);
    //对选中元件镜像
    bool mirror(bool bMirror, Graphic *selectItem);
    //获取对选中元件设置的规模大小
    double scale(double scale, Graphic *selectItem);
    //是否删除选中的链接
    bool delSelectItemJoin(int selPos);
    //是否删除选中的元件
    bool delSelectItem();
    //是否删除选中线路中的链接拐点
    bool delSelectItemKnee();

    //根据对齐方式设置位置
    void align(ALIGN alignType);

    //获取当前选中的元件
    Graphic* getCurrentSelectItem(void) {
        return _currentSelectItem;
    }

//    QPointF getCurrentSelectPoint(void) {
//        return _currentSelectPoint;
//    }

//    void setCurrentSelectPoint(QPointF& currentSelectPoint) {
//        _currentSelectPoint = currentSelectPoint;
//    }
    //获取选中的元件
    const QSet<Graphic*>& getSelectItem() const
    {
        return _selectItem;
    }
    QSet<Graphic*>& getSelectItem()
    {
        return _selectItem;
    }
    //添加选中的元件
    void setSelectItem(Graphic* selectItem)
    {
        _selectItem.insert(selectItem);
        _currentSelectItem = selectItem;
    }
    //获取拐点(选中线路或母线时选中的拐点)
    GraphicKnee& getGraphicKnee()
    {
        return _knee;
    }
    //设置拐点(选中线路或母线时选中的拐点)
    void setGraphicKnee(const GraphicKnee& graphicKnee)
    {
        _knee = graphicKnee;
    }
    //获取鼠标选中点
    const QPointF& getSelectPoint()
    {
        return _selectPoint;
    }
    //设置鼠标选中点
    void setSelectPoint(const QPointF& selectPoint)
    {
        _selectPoint = selectPoint;
    }
    //获取方向
    const int& getSizeFlag() const
    {
        return _sizeFlag;
    }

private:
    bool queryConnChild(QSet<QGraphicsItem *>& resChild,
                                         QSet<QGraphicsItem *>& connChild,
                                         QGraphicsItem* curItem);
    //选中相关
    QSet<Graphic*>	_selectItem;//用于保存选中元件
    Graphic* _currentSelectItem;//当前选中图标
    GraphicKnee _knee;//选中线路或母线时选中的拐点，-1是没有选中
    QPointF _selectPoint;//鼠标选中点
    //QPointF _currentSelectPoint;
    QCDrawScene* _drawScene;
    int _sizeFlag;//方向(从这个方向改变大小)
};

#endif // GRAPHICSELECTOR_H
