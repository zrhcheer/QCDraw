#include "lineflow.h"

LineFlow::LineFlow(QList<WidthGraphicLineItem*>& listLine) :
    _listLine(listLine)
{
    _beginPercent = 0;
    _endPercent = 100;
    _curPos = 0;
    _curLine = NULL;
    _stepMove = 1;
}

void LineFlow::initMove(const int& beginPer,const int& endPer,float step,const QColor& clr)
{
    _beginPercent = beginPer;
    _endPercent =  endPer;
    _curLine = NULL;

    _curPos = 0;

    _moveClr = clr;
    _stepMove = step;
}

void LineFlow::stopMove()
{
//    _isMove = false;
//    _moveLine = NULL;
    for(QList<WidthGraphicLineItem*>::const_iterator iterLine = _listLine.begin();
        iterLine != _listLine.end(); ++iterLine)
    {
        WidthGraphicLineItem* tmpLine = *iterLine;
        tmpLine->delMove(this);
    }
}
void LineFlow::flushMove()
{
    _curLine = NULL;
    _curLoopLine.clear();
    moveFlow();
}

void LineFlow::moveFlow()
{
//    if(!_isMove)
//    {
//        return;
//    }
    if(_beginPercent < _endPercent)
    {
        if(!_curLine)
        {
            _curLoopLine.clear();
            float maxLen = 0;
            for(QList<WidthGraphicLineItem*>::const_iterator iterLine = _listLine.begin();
                iterLine != _listLine.end(); ++iterLine)
            {
                WidthGraphicLineItem* tmpLine = *iterLine;
                maxLen += tmpLine->line().length();
            }

            float moveBegin = maxLen * _beginPercent / 100;
            float moveEnd = maxLen * _endPercent / 100;

            _curLoopLine.clear();
            maxLen = 0;
            float lineLine = 0;
            bool bFirst = true;
            bool bEnd = true;
            for(QList<WidthGraphicLineItem*>::const_iterator iterLine = _listLine.begin();
                iterLine != _listLine.end(); ++iterLine)
            {
                WidthGraphicLineItem* tmpLine = *iterLine;
                lineLine = tmpLine->line().length();
                maxLen += lineLine;
                bool bAdd = false;

                if(maxLen >= moveBegin)
                {
                    if(bFirst)
                    {
                        bFirst = false;
                        _beginPos = moveBegin - (maxLen - lineLine);
                    }
                    if(maxLen < moveEnd)
                    {
                        _curLoopLine.push_back(tmpLine);
                        tmpLine->addMode(this);
                        bAdd = true;
                    }
                    else
                    {
                        if(bEnd)
                        {
                            bEnd = false;
                            _endPos = moveEnd - (maxLen - lineLine);
                            _curLoopLine.push_back(tmpLine);
                            tmpLine->addMode(this);
                            bAdd = true;
                        }
                        else
                        {
                            tmpLine->delMove(this);
                        }
                    }
                    if(maxLen >= _curFullPos && bAdd)
                    {
                        if(!_curLine)
                        {
                            _curLine = tmpLine;
                            _curPos = _curFullPos - (maxLen - lineLine);
                            //_curLine->beginMove(_moveLen - maxLen + lineLine);
                        }
                    }
                }
                else
                {
                    tmpLine->delMove(this);
                }
            }
            if(!_curLine)
            {
                _curLine = _curLoopLine.front();
                _curPos = _beginPos;
            }
            else
            {
                if(_curLine == _curLoopLine.front())
                {
                    if(_curPos < _beginPos)
                    {
                        _curPos = _beginPos;
                    }
                }
            }
            if(_curLine == _curLoopLine.back())
            {
                _bEnd = true;
            }
            _curLine->update();
        }
        else
        {
            float lineLen = _curLine->line().length();
            if(_bEnd)
            {
                lineLen = _endPos;
            }
            _curPos += _stepMove;
            if(_curPos >= lineLen)
            {
                _curPos = 0;
                WidthGraphicLineItem* tmpLine = _curLine;
                for(QList<WidthGraphicLineItem*>::Iterator iterLine = _curLoopLine.begin();
                    iterLine != _curLoopLine.end(); ++iterLine)
                {
                    WidthGraphicLineItem* tmpLineItem = *iterLine;
                    if(tmpLineItem == _curLine)
                    {
                        ++iterLine;
                        if(iterLine != _curLoopLine.end())
                        {
                            _curLine = *iterLine;
                            _curPos = 0;
                        }
                        else
                        {
                            _curLine = _curLoopLine.front();
                            _curPos = _beginPos;
                        }
                        break;
                    }
                }
                if(_curLine == _curLoopLine.back())
                {
                    _bEnd = true;
                }
                else
                {
                    _bEnd = false;
                }

                tmpLine->update();
            }
            _curLine->update();
        }
    }
    else
    {
        if(!_curLine)
        {
            _curLoopLine.clear();
            float maxLen = 0;
            for(QList<WidthGraphicLineItem*>::const_iterator iterLine = _listLine.begin();
                iterLine != _listLine.end(); ++iterLine)
            {
                WidthGraphicLineItem* tmpLine = *iterLine;
                maxLen += tmpLine->line().length();
            }

            float moveBegin = maxLen * _beginPercent / 100;
            float moveEnd = maxLen * _endPercent / 100;

            _curLoopLine.clear();
            maxLen = 0;
            float lineLine = 0;
            bool bFirst = true;
            bool bEnd = true;
            for(QList<WidthGraphicLineItem*>::const_iterator iterLine = _listLine.begin();
                iterLine != _listLine.end(); ++iterLine)
            {
                WidthGraphicLineItem* tmpLine = *iterLine;
                lineLine = tmpLine->line().length();
                maxLen += lineLine;
                bool bAdd = false;

                if(maxLen >= moveEnd)
                {
                    if(bFirst)
                    {
                        bFirst = false;
                        _endPos =  lineLine + moveEnd - maxLen;
                    }
                    if(maxLen < moveBegin)
                    {
                        _curLoopLine.push_front(tmpLine);
                        tmpLine->addMode(this);
                        bAdd = true;
                    }
                    else
                    {
                        if(bEnd)
                        {
                            bEnd = false;
                            _beginPos = moveBegin - (maxLen - lineLine);
                            _curLoopLine.push_front(tmpLine);
                            tmpLine->addMode(this);
                            bAdd = true;
                        }
                        else
                        {
                            tmpLine->delMove(this);
                        }
                    }
                    if(maxLen >= _curFullPos && bAdd)
                    {
                        if(!_curLine)
                        {
                            _curLine = tmpLine;
                            _curPos = _curFullPos - (maxLen - lineLine);
                            //_curLine->beginMove(_moveLen - maxLen + lineLine);
                        }
                    }
                }
                else
                {
                    tmpLine->delMove(this);
                }
            }
            if(!_curLine)
            {
                _curLine = _curLoopLine.front();
                _curPos = _beginPos;
            }
            else
            {
                if(_curLine == _curLoopLine.front())
                {
                    if(_curPos > _beginPos)
                    {
                        _curPos = _beginPos;
                    }
                }
                else
                {
                    _curPos = _curLine->line().length();
                }
            }
            if(_curLine == _curLoopLine.back())
            {
                _bEnd = true;
            }

            _curLine->update();
        }
        else
        {
            float lineEnd = 0;
            if(_bEnd)
            {
                lineEnd = _endPos;
            }
            _curPos -= _stepMove;
            if(_curPos <= lineEnd)
            {
                WidthGraphicLineItem* tmpLine = _curLine;

                for(QList<WidthGraphicLineItem*>::Iterator iterLine = _curLoopLine.begin();
                    iterLine != _curLoopLine.end(); ++iterLine)
                {
                    WidthGraphicLineItem* tmpLineItem = *iterLine;
                    if(tmpLineItem == _curLine)
                    {
                        ++iterLine;
                        if(iterLine != _curLoopLine.end())
                        {
                            _curLine = *iterLine;
                            _curPos = _curLine->line().length();
                        }
                        else
                        {
                            _curLine = _curLoopLine.front();
                            _curPos = _beginPos;
                        }
                        break;
                    }
                }
                if(_curLine == _curLoopLine.back())
                {
                    _bEnd = true;
                }
                else
                {
                    _bEnd = false;
                }
                tmpLine->update();
            }
            _curLine->update();
        }
    }
}
