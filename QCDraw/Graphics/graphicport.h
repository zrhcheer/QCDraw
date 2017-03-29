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
    //��ȡ����λ��
    const int& getLinkPos() const
    {
        return _linkPos;
    }
    //��������λ��
    void setLinkPos(const int& direct)
    {
        _linkPos = direct;
    }
    //��ȡ�˵�λ��
    const int& getSelPos() const
    {
        return _selPos;
    }
    //���ö˵�λ��
    void setSelPos(const int& direct)
    {
        _selPos = direct;
    }
    //��ȡԪ��
    const Graphic* getGraphic() const
    {
        return _graphic;
    }
    Graphic* getGraphic()
    {
        return _graphic;
    }
    //����Ԫ��
    void setGraphic(Graphic* graphic);
    //��ȡ���
    const ulong64& getID()const
    {
        return _id;
    }
    //���ñ��
    void setID(const ulong64& id)
    {
        _id = id;
    }
    //��ȡ�˵�λ���ı�
    QString getPosText(int pos,bool isTrans) const;
    QString getSelText() const;
    QString getLinkText() const;

private:
    int _selPos;//ѡ��Ԫ���Ķ˵�λ��
    int _linkPos;//�˵������λ��
    ulong64 _id;//���
    Graphic* _graphic;//Ԫ��
};

extern QDataStream &	operator<< ( QDataStream & out, const GraphicPort& vector );
extern QDataStream &	operator>> ( QDataStream & in, GraphicPort& vector );

#endif // GRAPHICPORT_H
