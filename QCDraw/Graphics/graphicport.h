#ifndef GRAPHICPORT_H
#define GRAPHICPORT_H

#include <QPoint>
#include <QString>
typedef unsigned long long ulong64;


struct TopoJoin
{
    TopoJoin(const ulong64& id,const int& pos)
    {
        _id = id;
        _pos = pos;
    }
    TopoJoin()
    {
        _id = 0;
        _pos = 0;
    }

    bool operator<(const TopoJoin& other) const
    {
        if(_id < other._id)
        {
            return true;
        }
        else if(_id == other._id)
        {
            if(_pos < other._pos)
            {
                return true;
            }
        }
        return false;
    }
    bool operator !=(const TopoJoin& other) const
    {
        return (_id != other._id) || (_pos != other._pos);
    }

    ulong64 _id;
    QString _name;
    int _pos;
};

class Graphic;
class GraphicPort
{
public:
    enum
    {
        PORT_BEGIN,
        PORT_END,
        PORT_MID
    };
    GraphicPort();

    friend QDataStream &	operator<< ( QDataStream & out, const GraphicPort& vector );
    friend QDataStream &	operator>> ( QDataStream & in, GraphicPort& vector );
//    void restoreJoin(QDataStream& dataStream);
//    void saveJoin(QDataStream& dataStream) const;
    //获取链接位置
    const int& getLinkPos() const
    {
        return _linkPos;
    }
    //设置链接位置
    void setLinkPos(const int& direct)
    {
        _linkPos = direct;
    }
    //获取端点位置
    const int& getSelPos() const
    {
        return _selPos;
    }
    //设置端点位置
    void setSelPos(const int& direct)
    {
        _selPos = direct;
    }
    //获取元件
    const Graphic* getGraphic() const
    {
        return _graphic;
    }
    Graphic* getGraphic()
    {
        return _graphic;
    }
    //设置元件
    void setGraphic(Graphic* graphic);
    //获取编号
    const ulong64& getID()const
    {
        return _id;
    }
    //设置编号
    void setID(const ulong64& id)
    {
        _id = id;
    }
    //获取端点位置文本
    QString getPosText(int pos,bool isTrans) const;
    QString getSelText() const;
    QString getLinkText() const;

private:
    int _selPos;//选择元件的端点位置
    int _linkPos;//端点的链接位置
    ulong64 _id;//编号
    Graphic* _graphic;//元件
};

extern QDataStream &	operator<< ( QDataStream & out, const GraphicPort& vector );
extern QDataStream &	operator>> ( QDataStream & in, GraphicPort& vector );

#endif // GRAPHICPORT_H
