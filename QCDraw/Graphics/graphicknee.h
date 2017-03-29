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
    //清空
    void clear()
    {
        _kneeType = KNEE_UNKNOW;
        _kneeIndex = -1;
        _beginLine = NULL;
        _endLine = NULL;
    }
    //获取拐点类型
    const int& getKneeType()
    {
        return _kneeType;
    }
    //设置拐点类型
    void setKneeType(const int& kneeType)
    {
        _kneeType = kneeType;
    }
    //获取拐点索引
    const int& getKneeIndex()
    {
        return _kneeIndex;
    }
    //设置拐点索引
    void setKneeIndex(const int& kneeIndex)
    {
        _kneeIndex = kneeIndex;
    }
    //获取线路开始链接
    WidthGraphicLineItem* getBeginLine()
    {
        return _beginLine;
    }
    //设置线路开始链接
    void setBeginLine(WidthGraphicLineItem* beginLine)
    {
        _beginLine = beginLine;
    }
    //获取线路结束链接
    WidthGraphicLineItem* getEndLine()
    {
        return _endLine;
    }
    //设置线路结束链接
    void setEndLine(WidthGraphicLineItem* endLine)
    {
        _endLine = endLine;
    }
    //拐点是否在链接线路上
    bool isJointed(int& selPos);
private:
    int _kneeType;//拐点类型
    int _kneeIndex;//拐点索引

    //判断拐点是线路开始链接的还是线路结束链接的
    WidthGraphicLineItem* _beginLine;
    WidthGraphicLineItem* _endLine;
};

#endif // GRAPHICKNEE_H
