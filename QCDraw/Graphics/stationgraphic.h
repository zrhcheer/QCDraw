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
    //��ͼ
    virtual void drawGraphic(QPainter *painter);
    virtual void prepareGraphic(QPainter *painter);
    //�ָ�
    virtual void restoreGraphic(QDataStream& dataStream);
    virtual void loadXML(rapidxml::xml_node<char> *node);
    //����
    virtual void saveGraphic(QDataStream& dataStream) const;
    virtual void saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic);
    //����λ��
    virtual void setPosition(const QPointF& pos);
    //��ȡ���ӵ�λ��
    virtual QPointF  getPortPos(int pos)
    {
        UNUSED(pos);
        return QPointF(0,0);
    }
    //��ȡ�豸����
    virtual const QString& getDevName() const
    {
        return _devName;
    }
    //������·
    void setLine(LineGraphic* lineGraphic,int pos);

    //���ô�С
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
    //���ñ�����С
    virtual void setScale(const float& scale)
    {
        setSize(BASIC_RADIUS * scale);
    }
    //�����Ƿ���T�ڵ�
    void setIsTNode(const bool bTNode)
    {
        _isTNode = bTNode;
    }
   //��ȡ�Ƿ���T�ڵ�
    bool getIsTNode()
    {
        return _isTNode;
    }
    //������ɫ
    void  setFlagColor(const QColor& flagClr)
    {
        _flagClr = flagClr;
    }
    //�����ǲ���������ʾ
    void setIsFlag(bool bFlag)
    {
        if(_isFlag != bFlag)
        {
            _isFlag = bFlag;
            this->update();
        }
    }

private:
    bool _isTNode;//�Ƿ���T�ڵ�
    static const QString _devName;//�豸����
    QColor _flagClr;//��ɫ
    bool _isFlag;//�ǲ���������ʾ
};

#endif // STATIONGRAPHIC_H
