#include "graphicactivetimer.h"

#include <assert.h>
#include <QTimer>
#include <QDebug>
#include <sys/time.h>

GraphicActiveTimer::GraphicActiveTimer(QObject* parent) :
    QObject(parent)
{
    _timer = NULL;
    _bRun = false;
    _flushOperation.clear();
}

GraphicActiveTimer::~GraphicActiveTimer()
{
    for(QMap<TimeVal,QList<TimeOperator*> >::Iterator iterFlush =  _flushOperation.begin();
        iterFlush != _flushOperation.end(); ++iterFlush)
    {
        QList<TimeOperator*>& tmpOperList = iterFlush.value();
        for(QList<TimeOperator*>::Iterator iterOper = tmpOperList.begin();
            iterOper != tmpOperList.end(); ++iterOper)
        {
            TimeOperator* tmpOper = *iterOper;
            delete tmpOper;
        }
    }
    _flushOperation.clear();
}

void GraphicActiveTimer::clearTimer()
{
    for(QMap<TimeVal,QList<TimeOperator*> >::Iterator iterFlush =  _flushOperation.begin();
        iterFlush != _flushOperation.end(); ++iterFlush)
    {
        QList<TimeOperator*>& tmpOperList = iterFlush.value();
        for(QList<TimeOperator*>::Iterator iterOper = tmpOperList.begin();
            iterOper != tmpOperList.end(); ++iterOper)
        {
            TimeOperator* tmpOper = *iterOper;
            delete tmpOper;
        }
    }
    _flushOperation.clear();
    _bRun = false;
}

void GraphicActiveTimer::delOperation(set<TimeOperator*> operVec)
{
    for(QMap<TimeVal,QList<TimeOperator*> >::Iterator iterFlush = _flushOperation.begin();
        iterFlush != _flushOperation.end(); ++iterFlush)
    {
        QList<TimeOperator*>& listOper = iterFlush.value();
        for(QList<TimeOperator*>::Iterator iterOper = listOper.begin();
            iterOper != listOper.end(); ++iterOper)
        {
            TimeOperator* tmpOper = *iterOper;
            if(operVec.end() != operVec.find(tmpOper))
            {
                delete tmpOper;
                listOper.erase(iterOper);
            }
        }
        if(listOper.isEmpty())
        {
            _flushOperation.erase(iterFlush);
        }
    }
}

void GraphicActiveTimer::delOperation(TimeOperator* oper)
{
    bool bFind = false;
    for(QMap<TimeVal,QList<TimeOperator*> >::Iterator iterFlush = _flushOperation.begin();
        iterFlush != _flushOperation.end(); ++iterFlush)
    {
        QList<TimeOperator*>& listOper = iterFlush.value();
        for(QList<TimeOperator*>::Iterator iterOper = listOper.begin();
            iterOper != listOper.end(); ++iterOper)
        {
            TimeOperator* tmpOper = *iterOper;
            if(tmpOper == oper)
            {
                listOper.erase(iterOper);
                delete tmpOper;
                bFind = true;
                break;
            }
        }
        if(listOper.isEmpty())
        {
            _flushOperation.erase(iterFlush);
        }
        if(bFind)
        {
            break;
        }
    }
}

void GraphicActiveTimer::addOperation(const TimeVal& time,TimeOperator* oper)
{
    for(QMap<TimeVal,QList<TimeOperator*> >::Iterator iterFlush = _flushOperation.begin();
        iterFlush != _flushOperation.end(); ++iterFlush)
    {
        const QList<TimeOperator*>& listOper = iterFlush.value();
        if(listOper.contains(oper))
        {
            return;
        }
    }
    QMap<TimeVal,QList<TimeOperator*> >::Iterator iterFlush =  _flushOperation.find(time);
    if(iterFlush != _flushOperation.end())
    {
        QList<TimeOperator*>& timeOperList = iterFlush.value();
        timeOperList.push_back(oper);
    }
    else
    {
        _flushOperation[time].push_back(oper);
    }
}

void GraphicActiveTimer::startTimer()
{
    if(_bRun)
    {
        return;
    }
    if(!_timer)
    {
        _timer = new QTimer(this);
        connect(_timer, SIGNAL(timeout()), this, SLOT(loopTimer()));
    }
    if(_flushOperation.empty())
    {
        _timer->stop();
        return;
    }
    _bRun = true;
    TimeVal curDate;
    QMap<TimeVal,QList<TimeOperator*> >::Iterator iterBeginFlush = _flushOperation.begin();
    TimeVal oprDate = iterBeginFlush.key();

    qint64 msec = curDate.msecsTo(oprDate);
    qDebug() <<  "start loop:" << msec;
    if(msec < 0)
    {
        msec = 0;
    }
    _timer->start((int)msec);
}

void GraphicActiveTimer::loopTimer()
{
    TimeVal curDate;
    TimeVal myDate;
    for(QMap<TimeVal,QList<TimeOperator*> >::Iterator iterFlush =  _flushOperation.begin();
        iterFlush != _flushOperation.end(); ++iterFlush)
    {
        //const QDateTime& tmpDate = iterFlush.key();
        QList<TimeOperator*>  tmpOperList = iterFlush.value();
        _flushOperation.erase(iterFlush);
        for(QList<TimeOperator*>::Iterator iterOperList = tmpOperList.begin();
            iterOperList != tmpOperList.end(); ++iterOperList)
        {
            TimeOperator* tmpOper = *iterOperList;
            tmpOper->doTimer();
            if(!tmpOper->isStop())
            {
                if(tmpOper->getInterTime() > 0.001)
                {
                    myDate = curDate.addMSecs(tmpOper->getInterTime() * TIMER_INTER);
                    _flushOperation[myDate].push_back(tmpOper);
                }
                else
                {
                    myDate = curDate.addMSecs(0.001 * TIMER_INTER);
                    _flushOperation[myDate].push_back(tmpOper);
                }
            }
            else
            {
                delete tmpOper;
            }
        }
        break;
    }

    if(_flushOperation.empty())
    {
        _timer->stop();
        _bRun = false;
    }
    else
    {
        //QDateTime curDate = QDateTime::currentDateTime();
        QMap<TimeVal,QList<TimeOperator*> >::Iterator iterBeginFlush = _flushOperation.begin();
        const TimeVal& oprDate = iterBeginFlush.key();
        qint64 msec = curDate.msecsTo(oprDate);

        qDebug() <<  "loop:" << msec;
        if(msec < 0)
        {
            msec = 0;
        }
        _timer->setInterval(msec);
    }
}

