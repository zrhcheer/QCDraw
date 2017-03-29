#ifndef STATIONGRAPHIC_H
#define STATIONGRAPHIC_H
#include "graphicbase.h"

#include "graphicport.h"

class LineGraphic;
class StationGraphic : public GraphicBase
{
    Q_OBJECT
public:

    StationGraphic();
    //画图
    virtual void drawGraphic(QPainter *painter);
    virtual void prepareGraphic(QPainter *painter);
    //恢复
    virtual void restoreGraphic(QDataStream& dataStream);
    virtual void loadXML(rapidxml::xml_node<char> *node);
    //保存
    virtual void saveGraphic(QDataStream& dataStream) const;
    virtual void saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic);
    //设置位置
    virtual void setPosition(const QPointF& pos);
    //获取链接点位置
    virtual QPointF  getPortPos(int pos)
    {
        UNUSED(pos);
        return QPointF(0,0);
    }
    //获取设备名称
    virtual const QString& getDevName() const
    {
        return _devName;
    }
    //设置线路
    void setLine(LineGraphic* lineGraphic,int pos);

    //设置大小
    virtual void setSize(const int& height)
    {
        if(height < ELE_MIN_SIZE)
        {
            _size.setHeight(ELE_MIN_SIZE);
        }
        else
        {
            _size.setHeight(height);
        }
        _size.setWidth(_size.height());
    }
    //设置比例大小
    virtual void setScale(const float& scale)
    {
        setSize(BASIC_RADIUS * scale);
    }
    //设置是否是T节点
    void setIsTNode(const bool bTNode)
    {
        _isTNode = bTNode;
    }
   //获取是否是T节点
    bool getIsTNode()
    {
        return _isTNode;
    }
    //设置颜色
    void  setFlagColor(const QColor& flagClr)
    {
        _flagClr = flagClr;
    }
    //设置是不是显重显示
    void setIsFlag(bool bFlag)
    {
        if(_isFlag != bFlag)
        {
            _isFlag = bFlag;
            this->update();
        }
    }

private:
    bool _isTNode;//是否是T节点
    static const QString _devName;//设备名称
    QColor _flagClr;//颜色
    bool _isFlag;//是不是显重显示
};

#endif // STATIONGRAPHIC_H
