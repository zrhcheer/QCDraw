#ifndef DYNAMICPOINT_H
#define DYNAMICPOINT_H

#include"Graphics/graphicbase.h"

class DynamicPointGraphic: public GraphicBase
{
    Q_OBJECT
public:

    DynamicPointGraphic();

    //��ͼ
    virtual void drawGraphic(QPainter *painter);
    virtual void prepareGraphic(QPainter *painter);

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
//    void setLine(LineGraphic* lineGraphic,int pos);

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

protected:
    void timerEvent( QTimerEvent * );

private:

    static const QString _devName;//�豸����
    QColor _flagClr;//��ɫ
    QColor _lightClr;
    bool _isFlag;//�ǲ���������ʾ
};

#endif // DYNAMICPOINT_H
