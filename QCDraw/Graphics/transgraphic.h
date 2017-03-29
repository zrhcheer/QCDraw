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
        TEARTH_Yn=0,//	星形接地接线	0
        TEARTH_Y=1,//	星形接线		1
        TEARTH_D=2//	三角形接线		2
    };
    explicit TransGraphic();
    //恢复
    virtual void restoreGraphic(QDataStream& dataStream);
    virtual void loadXML(rapidxml::xml_node<char> *node);
    //保存
    virtual void saveGraphic(QDataStream& dataStream) const;
    virtual void saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic);
    //设置接地点属性
    void posEarch(int pos,const QPointF& joinPt,double radius,int direct,bool bLong = false);
    //画变压器
    void drawTrans(QPainter *painter,const QPointF& centerPt,double radius,int connType);
    //设置接线方式
    virtual void setEarchType(int pos,int earchType);
    //设置接地状态
    virtual void setEarchState(int pos,bool hasResist,bool  isOpen);
    //设置变压器开合状态
    virtual void setEarchIsOpen(int pos,bool  isOpen);
    //设置接地点是否是断路器
    virtual void setEarchHasResist(int pos,bool  hasResist);
    //设置电压等级
    void setVolLevel(int pos,const ulong64& volLevelId);
    //设置颜色
    void setColor(int pos,const QColor& clr);

signals:
    
public slots:
protected:
    int _connLType;//低压侧接线方式
    int _connMType;//中压侧接线方式
    int _connHType;//高压侧接线方式
    EarthGraphic* earthHGraphic;//高压测接地点
    EarthGraphic* earthLGraphic;//低压侧接地点
    EarthGraphic* earthMGraphic;//中压侧接地点

    ulong64 _volLevelIdH;//高压侧电压等级
    ulong64 _volLevelIdM;//中压侧电压等级
    ulong64 _volLevelIdL;//低压侧电压等级
    QColor _highColor;//用于存储高端的颜色
    QColor _leftColor;
    QColor _lowColor;//用于存储低端的颜色
    QColor _midColor;//用于存储中端的颜色
};

#endif // TRANSGRAPHIC_H
