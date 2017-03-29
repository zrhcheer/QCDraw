#ifndef GRAPHICACTIVETIMER_H
#define GRAPHICACTIVETIMER_H
#include <QTimer>
#include <QTime>
#include <set>

#include "Graphics/graphic.h"
#include "timeoperator.h"
#include "timeval.h"

#define TIMER_INTER 1000

class GraphicActiveTimer : QObject
{
    Q_OBJECT
public:
    GraphicActiveTimer(QObject* parent = 0);
    virtual ~GraphicActiveTimer();
    void clearTimer();
    void startTimer();

    void addOperation(const TimeVal& time,TimeOperator* oper);
    void delOperation(TimeOperator* oper);
    void delOperation(set<TimeOperator*> operVec);

private slots:
    void loopTimer();
private:


    QMap<TimeVal,QList<TimeOperator*> >  _flushOperation;
    QTimer* _timer;
    bool _bRun;
};

#endif // GRAPHICACTIVETIMER_H
