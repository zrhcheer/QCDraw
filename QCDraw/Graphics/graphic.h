#ifndef GRAPHIC_H
#define GRAPHIC_H
#include <QObject>
#include <QColor>
#include <QPointF>
#include <QSize>
#include <QVector>
#include <math.h>
#include <assert.h>
#include "graphicportpoint.h"
#include <string>
using namespace std;
#include "graphicport.h"
#include "codeconvertor.h"
#include "rapidxml/rapidxml_print.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml.hpp"

typedef unsigned long long ulong64;

#define UNUSED(x) (void)x

#define M_RADIUS (M_PI/180)
#define CROSS_PERCENT 0.9
#define RADIUS_PERCENT 1.2
#define RADIUS2_PERCENT 0.7
#define HORIZONTAL_PERCENT 0.8
#define HORIZONTAL2_PERCENT 0.4/////
#define BASIC_SQARE 16
#define BASIC_RADIUS 20
#define PORTSIZE 3
#define MIN_LINE_LEN 20

class ShrinkTick;
class Graphic /*: public QObject*/
{
public:
    enum
    {
        SIZECH_LEFT = 0x01,
        SIZECH_RIGHT = 0x02,
        SIZECH_TOP = 0x04,
        SIZECH_BOM = 0x08,
        SIZECH_NONE = 0x00
    };
    enum GraphicType
    {
        //通用图标
        GRAPHIC_STATION,
        GRAPHIC_BREAKER,//1
        GRAPHIC_TRANS2,//2
        GRAPHIC_TRANS3,
        GRAPHIC_DISCONNECTOR,//4
        GRAPHIC_REACTOR,
        GRAPHIC_SHUNTCAPACITOR,//并联电容器6
        GRAPHIC_SPLITREACTOR,
        GRAPHIC_GROUNDREACTOR,
        GRAPHIC_GROUNDDISCONNECTOR,//9
        GRAPHIC_EQUIVALUESOURCE,
        GRAPHIC_ALTERMATOR,
        GRAPHIC_MOTOR,
        GRAPHIC_SELFTRANS,//13
        GRAPHIC_SPLITTRANS,
        GRAPHIC_LOAD,
        GRAPHIC_SERIALCAPACITOR,//串联电容器16
        GRAPHIC_TRANS4,//17
        GRAPHIC_SPLITTRANS4,
        GRAPHIC_DYNAMIC,
        GRAPHIC_MAX,

        GRAPHIC_CONTROL_BEGIN = 300,
        GRAPHIC_CONTROL_TABLE,
        GRAPHIC_CONTROL_COMBOX,
        GRAPHIC_CONTROL_LABLE,
        GRAPHIC_CONTROL_PUSHBUTTON,
        GRAPHIC_CONTROL_BARCHART,
        GRAPHIC_CONTROL_MUTICURVECHART,
        GRAPHIC_CONTROL_SIMICIRCLECHART,
        GRAPHIC_CONTROL_SHRINK,
        GRAPHIC_CONTROL_END,
        //其他图形
        GRAPHIC_OTHER=1000,
        GRAPHIC_EARTH,
        GRAPHIC_LINE,
        GRAPHIC_BUS,
        GRAPHIC_GROUP,
        GRAPHIC_TEXT,
        GRAPHIC_TICK,
        //为保存做
        GRAPHIC_SAVE_LINELINK = -1
    };
    enum LineType
    {
        LINE_NOR,//线路
        LINE_EQUI,//等值线
        LINE_VIR,//虚线
        LINE_MASK=0xff,
        LINE_IN = 0x000,
        LINE_OUT = 0x100
    };
    enum LineOutType//出线类型
    {
        OUT_BEGIN,
        OUT_END,
        OUT_NONE
    };
    enum GraphicPos
    {
        POS_UP,
        POS_RIGHT,
        POS_DOWN,
        POS_LEFT
    };
    enum JointLineEm
    {
        JOIN_BEGIN,
        JOIN_HIGH = JOIN_BEGIN,
        JOIN_END,
        JOIN_LOW  = JOIN_END,
        JOIN_MID,
        JOIN_MAX,
        JOIN_UN
    };
    virtual ~Graphic()
    {
    }

    Graphic()
    {
        _shrink = NULL;
        _bSelected  = false;
    }

    //得到放大縮小的方向
    virtual int getSizeChangeFlag(const QPointF& point)
    {
        UNUSED(point);
        return 0;
    }
    //从某一方向改变大小
    virtual void changeSizeFromSide(const QPointF& curPoint,const int& sizeFlag)
    {
        UNUSED(curPoint);
        UNUSED(sizeFlag);
    }
    //判断给的点是否在窗体上
    virtual bool isPointOver(const QPointF& point) const
    {
        UNUSED(point);
        return true;
    }
    //设置光标
    virtual bool setCursorForSize(int sizeFlag)
    {
        UNUSED(sizeFlag);
        return false;
    }
    //设置光标
    virtual bool setCursorForID(int id)
    {
        UNUSED(id);
        return false;
    }
    //确保可见
    virtual void ensureVisible() = 0;
    //恢复
    virtual void restoreGraphic(QDataStream& dataStream) = 0;
    virtual void loadXML(rapidxml::xml_node<char>*node) = 0;
    //保存
    virtual void saveGraphic(QDataStream& dataStream) const=0;
    virtual void saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic) = 0;
    //获取链接点
    virtual QVector<GraphicPort>& getPorts() = 0;
    //获取链接点位置
    virtual QPointF  getPortPos(int pos) = 0;
    //获取链接点及其类型
    virtual QVector<GraphicPortPoint>&  getJoinPortPoint()
    {
        return _portPoints;
    }
    //是否链接
    virtual bool isJointed(int selPos){UNUSED(selPos);return false;}
    //删除链接
    virtual bool  delLink(int selPos,Graphic* graphic) = 0;
    virtual bool delJoin(int selPos) = 0;

    //显示锚
    virtual void showPortAnchor(int selPos){UNUSED(selPos);}
    //隐藏锚
    virtual void hidePortAnchor(int selPos){UNUSED(selPos);}
    virtual void hidePortAnchor(){}
    //获取大小
    virtual const QSize& getSize() const=0;
    //设置位置
    virtual void setPosition(const QPointF& pos) = 0;
    //获取位置
    virtual QPointF getPosition() const = 0;
    //更新
    virtual void updateShape() = 0;
    //获取父图
    virtual Graphic* parentGraphic() = 0;
    //获取类型
    const int& getType() const
    {
        return _type;
    }
    //设置类型
    void setType(const int& type)
    {
        _type = type;
    }
     //是否是线路
    bool isLine()
    {
        switch(_type)
        {
        case GRAPHIC_LINE:
            return true;
        }
        return false;
    }
    //是否是刀闸/断路器/接地刀闸
    bool isBreakerDisConnector() //dcb edited
    {
        switch(_type)
        {
        case GRAPHIC_DISCONNECTOR:
        case GRAPHIC_BREAKER:
        case GRAPHIC_GROUNDDISCONNECTOR:
            return true;
        }
        return false;
    }
    //是否是变压器
    bool isTrans()
    {
        switch(_type)
        {
        case GRAPHIC_TRANS2:
        case GRAPHIC_TRANS3:
        case GRAPHIC_SELFTRANS:
        case GRAPHIC_SPLITTRANS:
            return true;
        }
        return false;
    }
    //是否是2卷变
    bool is2Trans()
    {
        switch(_type)
        {
        case GRAPHIC_TRANS2:
//        case GRAPHIC_SELFTRANS:
            return true;
        }
        return false;
    }
    //是否是3卷变
    bool is3Trans()
    {
        switch(_type)
        {
        case GRAPHIC_TRANS3:
//        case GRAPHIC_SPLITTRANS:
            return true;
        }
        return false;
    }
    //获取选择状态
    const bool& getSelect() const
    {
        return _bSelected;
    }
    //设置选择状态
    virtual void setSelect(const bool& select)
    {
        if(_bSelected != select)
        {
            _bSelected = select;
            updateShape();
        }
    }
    //获取电压等级
    ulong64 getVolLevel()
    {
        return _volLevelId;
    }
    //设置电压等级
    void setVolLevel(const ulong64 volLevelId)
    {
        _volLevelId = volLevelId;
    }
    //设置颜色
    virtual void setColor(const QColor& color)
    {
        if(_color != color)
        {
            _color = color;
            this->updateShape();
        }
    }
    virtual void setColor(const int& red,const int& green,const int& blue)
    {
        QColor color;
        color.setRgb(red,green,blue);
        this->setColor(color);
    }
    //获取颜色
    const QColor& getColor() const
    {
        return _color;
    }
        //获取设备名称
    virtual const QString& getDevName() const = 0;
    //获取名称
    const QString& getName() const
    {
        return _name;
    }
    //设置名称
    void setName(const QString& strName)
    {
        _name = strName;
    }

    //设置标签
    virtual void setCaption(const QString& caption)
    {
        UNUSED(caption);
    }

    //设置编号
    void setID(const ulong64& id)
    {
        _id = id;
    }
    //获取编号
    const ulong64& getID() const
    {
        return _id;
    }
    //获取方向
    const int& getDirect() const
    {
        return _direct;
    }
    //设置方向
    void setDirect(int direct)
    {
        _direct = direct;
    }
    //获取镜像状态
    bool getIsMirror()
    {
        return _bMirror;
    }
    //设置镜像状态
    virtual  void setIsMirror(const bool bMirror)
    {
        _bMirror = bMirror;
    }
    //是否可以镜像
    virtual bool hasMirror()
    {
        return false;
    }

    void setShrink(ShrinkTick* shrink);

protected:
    int _direct;//方向
    int _type;//类型
    bool _bSelected;//是不是选择状态
    ulong64 _volLevelId;//电压等级
    QColor _color;//用于保存颜色
    QString _name;//名称
    ulong64 _id;//编号
    bool _bMirror;//是不是镜像状态
    QVector<GraphicPortPoint> _portPoints;//用于存连接点及其类型
    ShrinkTick* _shrink;
};
#endif // GRAPHIC_H
