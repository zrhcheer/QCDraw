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
    //����ΪCREAT_LINE��CREATE_BUS
    void setCreateType(int type,int flag)
    {
        _type = type;
        _flag = flag;
        _createStep = OPER_READY;
    }
    //�_ʼ
    bool beginCreateItem(const QPointF& mousePt);
    bool beginCreateLine(const QPointF& mousePt);
    bool beginCreateBus(const QPointF& mousePt);
    //�Ƅ�
    bool moveCreateItem(const QPointF& mousePt);
    bool moveCreateLine(const QPointF& mousePt);
    bool moveCreateBus(const QPointF& mousePt);
    //�Y��
    bool endCreateItem(const QPointF& mousePt);
    bool endCreateLine(const QPointF& mousePt);
    bool endCreateBus(const QPointF& mousePt);
private:
    //�������Ƿ���ѡ�е�Ԫ����
    bool moveCreateLineBef(const QPointF& mousePt);
    QCDrawScene* _drawScene;//��ͼ����
    Graphic* _dealGraphic;//Ԫ��
    int _type;//CREAT_LINE,CREATE_BUS
    int _flag;//CREATE_BUSʱΪĸ�߷���CREAT_LINEʱΪ��·����

    int _createStep;//OPER_READY,OPER_BEGIN,OPER_END
};

#endif // GRAPHICCREATOR_H
