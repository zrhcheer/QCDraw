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
        //ͨ��ͼ��
        GRAPHIC_STATION,
        GRAPHIC_BREAKER,//1
        GRAPHIC_TRANS2,//2
        GRAPHIC_TRANS3,
        GRAPHIC_DISCONNECTOR,//4
        GRAPHIC_REACTOR,
        GRAPHIC_SHUNTCAPACITOR,//����������6
        GRAPHIC_SPLITREACTOR,
        GRAPHIC_GROUNDREACTOR,
        GRAPHIC_GROUNDDISCONNECTOR,//9
        GRAPHIC_EQUIVALUESOURCE,
        GRAPHIC_ALTERMATOR,
        GRAPHIC_MOTOR,
        GRAPHIC_SELFTRANS,//13
        GRAPHIC_SPLITTRANS,
        GRAPHIC_LOAD,
        GRAPHIC_SERIALCAPACITOR,//����������16
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
        //����ͼ��
        GRAPHIC_OTHER=1000,
        GRAPHIC_EARTH,
        GRAPHIC_LINE,
        GRAPHIC_BUS,
        GRAPHIC_GROUP,
        GRAPHIC_TEXT,
        GRAPHIC_TICK,
        //Ϊ������
        GRAPHIC_SAVE_LINELINK = -1
    };
    enum LineType
    {
        LINE_NOR,//��·
        LINE_EQUI,//��ֵ��
        LINE_VIR,//����
        LINE_MASK=0xff,
        LINE_IN = 0x000,
        LINE_OUT = 0x100
    };
    enum LineOutType//��������
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

    //�õ��Ŵ�sС�ķ���
    virtual int getSizeChangeFlag(const QPointF& point)
    {
        UNUSED(point);
        return 0;
    }
    //��ĳһ����ı��С
    virtual void changeSizeFromSide(const QPointF& curPoint,const int& sizeFlag)
    {
        UNUSED(curPoint);
        UNUSED(sizeFlag);
    }
    //�жϸ��ĵ��Ƿ��ڴ�����
    virtual bool isPointOver(const QPointF& point) const
    {
        UNUSED(point);
        return true;
    }
    //���ù��
    virtual bool setCursorForSize(int sizeFlag)
    {
        UNUSED(sizeFlag);
        return false;
    }
    //���ù��
    virtual bool setCursorForID(int id)
    {
        UNUSED(id);
        return false;
    }
    //ȷ���ɼ�
    virtual void ensureVisible() = 0;
    //�ָ�
    virtual void restoreGraphic(QDataStream& dataStream) = 0;
    virtual void loadXML(rapidxml::xml_node<char>*node) = 0;
    //����
    virtual void saveGraphic(QDataStream& dataStream) const=0;
    virtual void saveXML(rapidxml::xml_node<char> *node,rapidxml::xml_document<> &doc,Graphic* graphic) = 0;
    //��ȡ���ӵ�
    virtual QVector<GraphicPort>& getPorts() = 0;
    //��ȡ���ӵ�λ��
    virtual QPointF  getPortPos(int pos) = 0;
    //��ȡ���ӵ㼰������
    virtual QVector<GraphicPortPoint>&  getJoinPortPoint()
    {
        return _portPoints;
    }
    //�Ƿ�����
    virtual bool isJointed(int selPos){UNUSED(selPos);return false;}
    //ɾ������
    virtual bool  delLink(int selPos,Graphic* graphic) = 0;
    virtual bool delJoin(int selPos) = 0;

    //��ʾê
    virtual void showPortAnchor(int selPos){UNUSED(selPos);}
    //����ê
    virtual void hidePortAnchor(int selPos){UNUSED(selPos);}
    virtual void hidePortAnchor(){}
    //��ȡ��С
    virtual const QSize& getSize() const=0;
    //����λ��
    virtual void setPosition(const QPointF& pos) = 0;
    //��ȡλ��
    virtual QPointF getPosition() const = 0;
    //����
    virtual void updateShape() = 0;
    //��ȡ��ͼ
    virtual Graphic* parentGraphic() = 0;
    //��ȡ����
    const int& getType() const
    {
        return _type;
    }
    //��������
    void setType(const int& type)
    {
        _type = type;
    }
     //�Ƿ�����·
    bool isLine()
    {
        switch(_type)
        {
        case GRAPHIC_LINE:
            return true;
        }
        return false;
    }
    //�Ƿ��ǵ�բ/��·��/�ӵص�բ
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
    //�Ƿ��Ǳ�ѹ��
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
    //�Ƿ���2���
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
    //�Ƿ���3���
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
    //��ȡѡ��״̬
    const bool& getSelect() const
    {
        return _bSelected;
    }
    //����ѡ��״̬
    virtual void setSelect(const bool& select)
    {
        if(_bSelected != select)
        {
            _bSelected = select;
            updateShape();
        }
    }
    //��ȡ��ѹ�ȼ�
    ulong64 getVolLevel()
    {
        return _volLevelId;
    }
    //���õ�ѹ�ȼ�
    void setVolLevel(const ulong64 volLevelId)
    {
        _volLevelId = volLevelId;
    }
    //������ɫ
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
    //��ȡ��ɫ
    const QColor& getColor() const
    {
        return _color;
    }
        //��ȡ�豸����
    virtual const QString& getDevName() const = 0;
    //��ȡ����
    const QString& getName() const
    {
        return _name;
    }
    //��������
    void setName(const QString& strName)
    {
        _name = strName;
    }

    //���ñ�ǩ
    virtual void setCaption(const QString& caption)
    {
        UNUSED(caption);
    }

    //���ñ��
    void setID(const ulong64& id)
    {
        _id = id;
    }
    //��ȡ���
    const ulong64& getID() const
    {
        return _id;
    }
    //��ȡ����
    const int& getDirect() const
    {
        return _direct;
    }
    //���÷���
    void setDirect(int direct)
    {
        _direct = direct;
    }
    //��ȡ����״̬
    bool getIsMirror()
    {
        return _bMirror;
    }
    //���þ���״̬
    virtual  void setIsMirror(const bool bMirror)
    {
        _bMirror = bMirror;
    }
    //�Ƿ���Ծ���
    virtual bool hasMirror()
    {
        return false;
    }

    void setShrink(ShrinkTick* shrink);

protected:
    int _direct;//����
    int _type;//����
    bool _bSelected;//�ǲ���ѡ��״̬
    ulong64 _volLevelId;//��ѹ�ȼ�
    QColor _color;//���ڱ�����ɫ
    QString _name;//����
    ulong64 _id;//���
    bool _bMirror;//�ǲ��Ǿ���״̬
    QVector<GraphicPortPoint> _portPoints;//���ڴ����ӵ㼰������
    ShrinkTick* _shrink;
};
#endif // GRAPHIC_H
