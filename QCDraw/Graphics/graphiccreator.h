#ifndef GRAPHICCREATOR_H
#define GRAPHICCREATOR_H

#include <QPointF>
class QCDrawScene;
class Graphic;
class GraphicCreator
{
public:
    GraphicCreator(QCDrawScene* drawScene);
    enum
    {
        CREAT_LINE,
        CREATE_BUS
    };
    enum
    {
        OPER_READY,
        OPER_BEGIN,
        OPER_END
    };
    //设置为CREAT_LINE或CREATE_BUS
    void setCreateType(int type,int flag)
    {
        _type = type;
        _flag = flag;
        _createStep = OPER_READY;
    }
    //開始
    bool beginCreateItem(const QPointF& mousePt);
    bool beginCreateLine(const QPointF& mousePt);
    bool beginCreateBus(const QPointF& mousePt);
    //移動
    bool moveCreateItem(const QPointF& mousePt);
    bool moveCreateLine(const QPointF& mousePt);
    bool moveCreateBus(const QPointF& mousePt);
    //結束
    bool endCreateItem(const QPointF& mousePt);
    bool endCreateLine(const QPointF& mousePt);
    bool endCreateBus(const QPointF& mousePt);
private:
    //给定点是否在选中的元件上
    bool moveCreateLineBef(const QPointF& mousePt);
    QCDrawScene* _drawScene;//画图场景
    Graphic* _dealGraphic;//元件
    int _type;//CREAT_LINE,CREATE_BUS
    int _flag;//CREATE_BUS时为母线方向，CREAT_LINE时为线路类型

    int _createStep;//OPER_READY,OPER_BEGIN,OPER_END
};

#endif // GRAPHICCREATOR_H
