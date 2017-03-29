#ifndef TRANSGRAPHIC_H
#define TRANSGRAPHIC_H

#include "graphicbase.h"

class EarthGraphic;
class TransGraphic : public GraphicBase
{
    Q_OBJECT
public:
    enum EarchType
    {
        TEARTH_Yn=0,//	���νӵؽ���	0
        TEARTH_Y=1,//	���ν���		1
        TEARTH_D=2//	�����ν���		2
    };
    explicit TransGraphic();
    //�ָ�
    virtual void restoreGraphic(QDataStream& dataStream);
    virtual void loadXML(rapidxml::xml_node<char> *node);
    //����
    virtual void saveGraphic(QDataStream& dataStream) const;
    virtual void saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic);
    //���ýӵص�����
    void posEarch(int pos,const QPointF& joinPt,double radius,int direct,bool bLong = false);
    //����ѹ��
    void drawTrans(QPainter *painter,const QPointF& centerPt,double radius,int connType);
    //���ý��߷�ʽ
    virtual void setEarchType(int pos,int earchType);
    //���ýӵ�״̬
    virtual void setEarchState(int pos,bool hasResist,bool  isOpen);
    //���ñ�ѹ������״̬
    virtual void setEarchIsOpen(int pos,bool  isOpen);
    //���ýӵص��Ƿ��Ƕ�·��
    virtual void setEarchHasResist(int pos,bool  hasResist);
    //���õ�ѹ�ȼ�
    void setVolLevel(int pos,const ulong64& volLevelId);
    //������ɫ
    void setColor(int pos,const QColor& clr);

signals:
    
public slots:
protected:
    int _connLType;//��ѹ����߷�ʽ
    int _connMType;//��ѹ����߷�ʽ
    int _connHType;//��ѹ����߷�ʽ
    EarthGraphic* earthHGraphic;//��ѹ��ӵص�
    EarthGraphic* earthLGraphic;//��ѹ��ӵص�
    EarthGraphic* earthMGraphic;//��ѹ��ӵص�

    ulong64 _volLevelIdH;//��ѹ���ѹ�ȼ�
    ulong64 _volLevelIdM;//��ѹ���ѹ�ȼ�
    ulong64 _volLevelIdL;//��ѹ���ѹ�ȼ�
    QColor _highColor;//���ڴ洢�߶˵���ɫ
    QColor _leftColor;
    QColor _lowColor;//���ڴ洢�Ͷ˵���ɫ
    QColor _midColor;//���ڴ洢�ж˵���ɫ
};

#endif // TRANSGRAPHIC_H
