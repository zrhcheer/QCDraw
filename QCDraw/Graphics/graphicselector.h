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
    //���
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
    //���ѡ����
    bool clearSelect();
    //��ȡbaseItem��Ӧ������
    int selectItem(Graphic* baseItem, const QPointF& scenePoint, const int &selectType);
    //ѡ��selectItem�ڵĹյ�
    int selectSelfKnee(const QPointF& scenePoint, Graphic *selectItem);
    //��ȡѡ�е�����
    int selectSelfKneeBasic(const QPointF& scenePoint, GraphicKnee& knee, Graphic *selectItem);
    //�ƶ�ѡ�е�Ԫ��
    bool moveSelectItem(const QPointF& scenePoint, Graphic *selectItem,set<LineMove>& lineMove,bool bSingle=true);
    bool downSelectItem(const QPointF& scenePoint, Graphic *selectItem);

    bool linkSelectEle(GraphicBase* lineGraphic, bool bLink, Graphic *selectItem);
    //Ԫ�����ӵ�ѡ����·��
    bool linkSelectLine(LineGraphic* lineGraphic, bool bLink, Graphic *selectItem);
    //��Ԫ�����D��ָ������
    bool rotate(int direct, Graphic *selectItem);
    int getNextDirect(Graphic *selectItem);
    int getNextMirror(Graphic *selectItem);
    //��ѡ��Ԫ������
    bool mirror(bool bMirror, Graphic *selectItem);
    //��ȡ��ѡ��Ԫ�����õĹ�ģ��С
    double scale(double scale, Graphic *selectItem);
    //�Ƿ�ɾ��ѡ�е�����
    bool delSelectItemJoin(int selPos);
    //�Ƿ�ɾ��ѡ�е�Ԫ��
    bool delSelectItem();
    //�Ƿ�ɾ��ѡ����·�е����ӹյ�
    bool delSelectItemKnee();

    //���ݶ��뷽ʽ����λ��
    void align(ALIGN alignType);

    //��ȡ��ǰѡ�е�Ԫ��
    Graphic* getCurrentSelectItem(void) {
        return _currentSelectItem;
    }

//    QPointF getCurrentSelectPoint(void) {
//        return _currentSelectPoint;
//    }

//    void setCurrentSelectPoint(QPointF& currentSelectPoint) {
//        _currentSelectPoint = currentSelectPoint;
//    }
    //��ȡѡ�е�Ԫ��
    const QSet<Graphic*>& getSelectItem() const
    {
        return _selectItem;
    }
    QSet<Graphic*>& getSelectItem()
    {
        return _selectItem;
    }
    //���ѡ�е�Ԫ��
    void setSelectItem(Graphic* selectItem)
    {
        _selectItem.insert(selectItem);
        _currentSelectItem = selectItem;
    }
    //��ȡ�յ�(ѡ����·��ĸ��ʱѡ�еĹյ�)
    GraphicKnee& getGraphicKnee()
    {
        return _knee;
    }
    //���ùյ�(ѡ����·��ĸ��ʱѡ�еĹյ�)
    void setGraphicKnee(const GraphicKnee& graphicKnee)
    {
        _knee = graphicKnee;
    }
    //��ȡ���ѡ�е�
    const QPointF& getSelectPoint()
    {
        return _selectPoint;
    }
    //�������ѡ�е�
    void setSelectPoint(const QPointF& selectPoint)
    {
        _selectPoint = selectPoint;
    }
    //��ȡ����
    const int& getSizeFlag() const
    {
        return _sizeFlag;
    }

private:
    bool queryConnChild(QSet<QGraphicsItem *>& resChild,
                                         QSet<QGraphicsItem *>& connChild,
                                         QGraphicsItem* curItem);
    //ѡ�����
    QSet<Graphic*>	_selectItem;//���ڱ���ѡ��Ԫ��
    Graphic* _currentSelectItem;//��ǰѡ��ͼ��
    GraphicKnee _knee;//ѡ����·��ĸ��ʱѡ�еĹյ㣬-1��û��ѡ��
    QPointF _selectPoint;//���ѡ�е�
    //QPointF _currentSelectPoint;
    QCDrawScene* _drawScene;
    int _sizeFlag;//����(���������ı��С)
};

#endif // GRAPHICSELECTOR_H
