#ifndef GRAPHICKNEE_H
#define GRAPHICKNEE_H

#include "widthgraphiclineitem.h"

class GraphicKnee
{
public:
    enum
    {
        KNEE_JOIN,
        KNEE_MID,
        KNEE_UNKNOW
    };
    GraphicKnee();
    //���
    void clear()
    {
        _kneeType = KNEE_UNKNOW;
        _kneeIndex = -1;
        _beginLine = NULL;
        _endLine = NULL;
    }
    //��ȡ�յ�����
    const int& getKneeType()
    {
        return _kneeType;
    }
    //���ùյ�����
    void setKneeType(const int& kneeType)
    {
        _kneeType = kneeType;
    }
    //��ȡ�յ�����
    const int& getKneeIndex()
    {
        return _kneeIndex;
    }
    //���ùյ�����
    void setKneeIndex(const int& kneeIndex)
    {
        _kneeIndex = kneeIndex;
    }
    //��ȡ��·��ʼ����
    WidthGraphicLineItem* getBeginLine()
    {
        return _beginLine;
    }
    //������·��ʼ����
    void setBeginLine(WidthGraphicLineItem* beginLine)
    {
        _beginLine = beginLine;
    }
    //��ȡ��·��������
    WidthGraphicLineItem* getEndLine()
    {
        return _endLine;
    }
    //������·��������
    void setEndLine(WidthGraphicLineItem* endLine)
    {
        _endLine = endLine;
    }
    //�յ��Ƿ���������·��
    bool isJointed(int& selPos);
private:
    int _kneeType;//�յ�����
    int _kneeIndex;//�յ�����

    //�жϹյ�����·��ʼ���ӵĻ�����·�������ӵ�
    WidthGraphicLineItem* _beginLine;
    WidthGraphicLineItem* _endLine;
};

#endif // GRAPHICKNEE_H
