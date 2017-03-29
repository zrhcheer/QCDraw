#include "timeval.h"

TimeVal::TimeVal()
{
    gettimeofday(&_timer,0);
}

void TimeVal::getCurrentTime()
{
    gettimeofday(&_timer,0);
}

TimeVal TimeVal::addMSecs(const long& msec) const
{
    TimeVal tmpTimer;
    long tmpmsec =  _timer.tv_usec / 1000 + msec;
    tmpTimer._timer.tv_usec = (tmpmsec % 1000) * 1000;
    tmpTimer._timer.tv_sec = _timer.tv_sec + tmpmsec / 1000;
    return tmpTimer;
}

long  TimeVal::msecsTo(const TimeVal& other) const
{
    if(*this < other)
    {
        long sec = 0;
        long msec = 0;
        long msecup = 0;
        if(other._timer.tv_usec > this->_timer.tv_usec)
        {
            msec = (other._timer.tv_usec - this->_timer.tv_usec) / 1000;
        }
        else
        {
            msecup = 1;
            msec = 1000  + (other._timer.tv_usec - this->_timer.tv_usec) / 1000;
        }
        sec = other._timer.tv_sec - this->_timer.tv_sec - msecup;
        return sec * 1000 + msec;
    }
    else
    {
        long sec = 0;
        long msec = 0;
        long msecup = 0;
        if(this->_timer.tv_usec > other._timer.tv_usec)
        {
            msec = (this->_timer.tv_usec - other._timer.tv_usec) / 1000;
        }
        else
        {
            msecup = 1;
            msec = 1000  + (this->_timer.tv_usec - other._timer.tv_usec) / 1000;
        }
        sec = this->_timer.tv_sec - other._timer.tv_sec - msecup;
        return -(sec * 1000 + msec);
    }
}

bool TimeVal::operator<(const TimeVal& other) const
{
    if(this->_timer.tv_sec < other._timer.tv_sec)
    {
        return true;
    }
    else if(this->_timer.tv_sec == other._timer.tv_sec)
    {
        if(this->_timer.tv_usec < other._timer.tv_usec)
        {
            return true;
        }
    }
    return false;
}
