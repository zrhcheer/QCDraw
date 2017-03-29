#ifndef LINEFLOW_H
#define LINEFLOW_H
#include "widthgraphiclineitem.h"

class WidthGraphicLineItem;
class LineFlow
{
public:
    LineFlow(QList<WidthGraphicLineItem*>& listLine);

    void initMove(const int& beginPer,const int& endPer,float step,const QColor& clr);
    void moveFlow();
    void stopMove();
    void flushMove();

    bool isBegin(WidthGraphicLineItem* line)
    {
        return line == _curLoopLine.front();
    }
    bool isEnd(WidthGraphicLineItem* line)
    {
        return line == _curLoopLine.back();
    }
    bool isCur(WidthGraphicLineItem* line)
    {
        return _curLine == line;
    }

    bool isOrder()
    {
        return _beginPercent < _endPercent;
    }

    const float& getBeginPos()const
    {
        return _beginPos;
    }
    const float& getEndPos()const
    {
        return _endPos;
    }

    const QColor& getMoveClr() const
    {
        return _moveClr;
    }
    const float& getCurPos() const
    {
        return _curPos;
    }
private:
    QList<WidthGraphicLineItem*>& _listLine;

    int _beginPercent;//始端百分比
    int _endPercent;//结束百分比

    float _curPos;//
    float _curFullPos;//

    float _beginPos;
    float _endPos;

    float _stepMove;//步长
    QColor _moveClr;//颜色

    //QList<WidthGraphicLineItem*>::Iterator _curIterLine;
    QList<WidthGraphicLineItem*> _curLoopLine;
    WidthGraphicLineItem* _curLine;
    bool _bEnd;
};

#endif // LINEFLOW_H
