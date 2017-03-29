#ifndef SWITCHGRAPHIC_H
#define SWITCHGRAPHIC_H

#include "graphicbase.h"

class SwitchGraphic : public GraphicBase
{
    Q_OBJECT
public:
    SwitchGraphic();
    //��ȡ���ӵ�λ��
    virtual QPointF  getPortPos(int pos);
    //���ÿ���״̬
    void setOpen(const bool& bOpen)
    {
        if(  _bOpen != bOpen)
        {
            _bOpen = bOpen;
            update();
        }
    }
    //��ȡ����״̬
    bool getOpen() const
    {
        return _bOpen;
    }


protected:
    bool _bOpen;//����״̬
};

#endif // SWITCHGRAPHIC_H
