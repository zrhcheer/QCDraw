#ifndef SWITCHGRAPHIC_H
#define SWITCHGRAPHIC_H

#include "graphicbase.h"

class SwitchGraphic : public GraphicBase
{
    Q_OBJECT
public:
    SwitchGraphic();
    //获取链接点位置
    virtual QPointF  getPortPos(int pos);
    //设置开合状态
    void setOpen(const bool& bOpen)
    {
        if(  _bOpen != bOpen)
        {
            _bOpen = bOpen;
            update();
        }
    }
    //获取开合状态
    bool getOpen() const
    {
        return _bOpen;
    }


protected:
    bool _bOpen;//开合状态
};

#endif // SWITCHGRAPHIC_H
