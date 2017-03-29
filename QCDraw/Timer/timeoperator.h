#ifndef TIMEOPERATOR_H
#define TIMEOPERATOR_H

class TimeOperator
{
public:
    TimeOperator();
    virtual void doTimer() = 0;
    virtual bool isStop() = 0;
    virtual bool isEmpty() = 0;

    void setStartTime(float start)
    {
        _timeStart = start;
    }
    void setInterTime(float inter)
    {
        _timeInter = inter;
    }
    float getStartTime()
    {
        return _timeStart;
    }

    float getInterTime() const
    {
        return _timeInter;
    }
private:
    float _timeStart;
    float _timeInter;
};

#endif // TIMEOPERATOR_H
